/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2024 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "ArduinoOutput.h"
#include "ArduinoOutputEditor.h"

#include <stdio.h>

ArduinoOutput::ArduinoOutput()
    : GenericProcessor ("Arduino Output"), gateIsOpen (true), deviceSelected (false)
{
    addCategoricalParameter (Parameter::PROCESSOR_SCOPE, "device", "Device", "The Arduino device to use", getDevices(), 0, true);
    addIntParameter (Parameter::PROCESSOR_SCOPE, "output_pin", "Output pin", "The Arduino pin to use", 13, 0, 13);
    addIntParameter (Parameter::STREAM_SCOPE, "input_line", "Input line", "The TTL line for triggering output", 1, 1, 16);
    addIntParameter (Parameter::STREAM_SCOPE, "gate_line", "Gate line", "The TTL line for gating the output", 0, 0, 16);
}

ArduinoOutput::~ArduinoOutput()
{
    if (arduino.isInitialized())
        arduino.disconnect();
}

AudioProcessorEditor* ArduinoOutput::createEditor()
{
    editor = std::make_unique<ArduinoOutputEditor> (this);
    return editor.get();
}

Array<String> ArduinoOutput::getDevices()
{
    Array<String> out;

    vector<ofSerialDeviceInfo> devices = serial.getDeviceList();

    for (int i = 0; i < devices.size(); i++)
    {
        out.add (devices[i].getDevicePath());
    }

    return out;
}

void ArduinoOutput::setDevice (String devName)
{
    LOGC ("Selecting device ", devName);

    if (devName.length() == 0)
        return;

    Time timer;

    /* Avoid connecting to the same device twice */
    if (devName != deviceString)
    {
        if (arduino.isArduinoReady())
            arduino.disconnect();

        arduino.connect (devName.toStdString());
    }

    if (arduino.isArduinoReady())
    {
        uint32 currentTime = timer.getMillisecondCounter();

        LOGC ("Sending protocol version request");
        arduino.sendProtocolVersionRequest();

        timer.waitForMillisecondCounter (currentTime + 200);

        LOGC ("Updating...");
        arduino.update();

        LOGC ("Sending firmware version request...");
        arduino.sendFirmwareVersionRequest();

        timer.waitForMillisecondCounter (currentTime + 500);

        LOGC ("Updating...");
        arduino.update();

        LOGC ("firmata v", arduino.getMajorFirmwareVersion(), ".", arduino.getMinorFirmwareVersion());
    }

    deviceString = devName;

    if (arduino.isInitialized())
    {
        LOGC ("Arduino is initialized.");
        arduino.sendDigitalPinMode ((int) getParameter ("output_pin")->getValue(), ARD_OUTPUT);
        CoreServices::sendStatusMessage (("Arduino initialized at " + devName));
        deviceSelected = true;
    }
    else
    {
        arduino.disconnect();
        LOGC ("Arduino is NOT initialized.");
        CoreServices::sendStatusMessage (("Arduino could not be initialized at " + devName));
        deviceSelected = false;
    }
    CoreServices::updateSignalChain (this);
}

void ArduinoOutput::updateSettings()
{
    isEnabled = deviceSelected;
}

bool ArduinoOutput::stopAcquisition()
{
    arduino.sendDigital ((int) getParameter ("output_pin")->getValue(), ARD_LOW);

    return true;
}

void ArduinoOutput::parameterValueChanged (Parameter* param)
{
    if (param->getName().equalsIgnoreCase ("device"))
    {
        setDevice (getDevices()[param->getValue()]);
    }
    else if (param->getName().equalsIgnoreCase ("gate_line"))
    {
        if (int (param->getValue()) == 0)
            gateIsOpen = true;
        else
            gateIsOpen = false;
    }
}

void ArduinoOutput::process (AudioBuffer<float>& buffer)
{
    checkForEvents();
}

void ArduinoOutput::handleTTLEvent (TTLEventPtr event)
{
    const int eventBit = event->getLine() + 1;
    DataStream* stream = getDataStream (event->getStreamId());

    if (eventBit == int ((*stream)["gate_line"]))
    {
        if (event->getState())
            gateIsOpen = true;
        else
            gateIsOpen = false;
    }

    if (gateIsOpen)
    {
        if (eventBit == int ((*stream)["input_line"]))
        {
            if (event->getState())
            {
                arduino.sendDigital (
                    getParameter ("output_pin")->getValue(),
                    ARD_LOW);
            }
            else
            {
                arduino.sendDigital (
                    getParameter ("output_pin")->getValue(),
                    ARD_HIGH);
            }
        }
    }
}