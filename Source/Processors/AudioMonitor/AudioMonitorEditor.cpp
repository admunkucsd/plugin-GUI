/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

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

#include "AudioMonitorEditor.h"

static const Colour COLOUR_PRIMARY (Colours::black.withAlpha (0.87f));
static const Colour COLOUR_ACCENT  (Colour::fromRGB (3, 169, 244));

MonitorMuteButton::MonitorMuteButton(Parameter* param) : ParameterEditor(param)
{

    muteButton = std::make_unique<ImageButton>("Mute Button");

    offimage = ImageCache::getFromMemory  (BinaryData::muteoff_png, BinaryData::muteoff_pngSize);
    onimage  = ImageCache::getFromMemory  (BinaryData::muteon_png,  BinaryData::muteon_pngSize);

    muteButton->setImages (false, true, true,
               offimage, 1.0f, findColour(ThemeColors::defaultText),
               offimage, 0.5f, findColour(ThemeColors::defaultText).withAlpha(0.5f),
               onimage,  0.7f, findColour(ThemeColors::defaultText).withAlpha(0.7f));

    muteButton->setClickingTogglesState (true);

    muteButton->setTooltip ("Mute audio");

    muteButton->addListener(this);
    muteButton->setToggleState(false, dontSendNotification);

    addAndMakeVisible(muteButton.get());

    setBounds(0, 0, 20, 20);
}

void MonitorMuteButton::buttonClicked(Button*)
{
    param->setNextValue(muteButton->getToggleState());
}

void MonitorMuteButton::updateView()
{
    if (param != nullptr)
        muteButton->setToggleState(param->getValue(), dontSendNotification);
}

void MonitorMuteButton::paint(Graphics& g)
{
     muteButton->setImages (false, true, true,
               offimage, 1.0f, findColour(ThemeColors::defaultText),
               offimage, 0.5f, findColour(ThemeColors::defaultText).withAlpha(0.5f),
               onimage,  0.7f, findColour(ThemeColors::defaultText).withAlpha(0.7f));
}

void MonitorMuteButton::resized()
{

    muteButton->setBounds(0, 0, 20, 20);
}


AudioOutputSelector::AudioOutputSelector(Parameter* param) : ParameterEditor(param)
{

    leftButton = new TextButton("Left", "Output to left channel only");
    leftButton->setClickingTogglesState(true);
    leftButton->setToggleState(false, dontSendNotification);

    
    rightButton = new TextButton("Right", "Output to right channel only");
    rightButton->setClickingTogglesState(true);
    rightButton->setToggleState(false, dontSendNotification);

    
    bothButton = new TextButton("Both", "Output to both channels");
    bothButton->setClickingTogglesState(true);
    bothButton->setToggleState(false, dontSendNotification);


    outputChannelButtonManager = std::make_unique<LinearButtonGroupManager>();
    outputChannelButtonManager->addButton(leftButton);
    outputChannelButtonManager->addButton(bothButton);
    outputChannelButtonManager->addButton(rightButton);
    outputChannelButtonManager->setRadioButtonMode(true);
    outputChannelButtonManager->setButtonListener(this);
    outputChannelButtonManager->setSelectedButtonIndex(1);
    bothButton->setToggleState(true, dontSendNotification);
    addAndMakeVisible(outputChannelButtonManager.get());
 
    setBounds(0, 0, 120, 20);
    outputChannelButtonManager->setBounds(0, 0, 120, 20);
}


void AudioOutputSelector::buttonClicked(Button* buttonThatWasClicked)
{

    const String buttonName = buttonThatWasClicked->getName().toLowerCase();

    if (buttonName.startsWith("left"))
    {
        param->setNextValue(0);
        LOGD("Left channel only");
    }
    else if (buttonName.startsWith("both"))
    {
        param->setNextValue(1);
        LOGD("Both channels");
    }

    else if (buttonName.startsWith("right"))
    {
        param->setNextValue(2);
        LOGD("Right channel only");
    }
}

void AudioOutputSelector::updateView()
{
    if (param != nullptr)
    {

        if (int(param->getValue()) == 0)
        {
            leftButton->setToggleState(true, dontSendNotification);
            rightButton->setToggleState(false, dontSendNotification);
            bothButton->setToggleState(false, dontSendNotification);
            outputChannelButtonManager->setSelectedButtonIndex(0);
        }
        else if (int(param->getValue()) == 1)
        {
            bothButton->setToggleState(true, dontSendNotification);
            leftButton->setToggleState(false, dontSendNotification);
            rightButton->setToggleState(false, dontSendNotification);
            outputChannelButtonManager->setSelectedButtonIndex(1);
        }
        else {
            rightButton->setToggleState(true, dontSendNotification);
            leftButton->setToggleState(false, dontSendNotification);
            bothButton->setToggleState(false, dontSendNotification);
            outputChannelButtonManager->setSelectedButtonIndex(2);
        }
    }
       
}

void AudioOutputSelector::resized()
{
    outputChannelButtonManager->setBounds(0, 0, 140, 20);
}

AudioMonitorEditor::AudioMonitorEditor (GenericProcessor* parentNode)
    : GenericEditor (parentNode)
{
    audioMonitor = static_cast<AudioMonitor*>(parentNode);
    
    addSelectedChannelsParameterEditor(Parameter::STREAM_SCOPE, "channels", 15, 35);

    Parameter* outputParam = parentNode->getParameter("audio_output");
    addCustomParameterEditor(new AudioOutputSelector(outputParam), 15, 65);

    Parameter* muteParam = parentNode->getParameter("mute_audio");
    addCustomParameterEditor(new MonitorMuteButton(muteParam), 145, 65);

    addComboBoxParameterEditor(Parameter::STREAM_SCOPE, "spike_channel", 15, 100);
    parameterEditors.getLast()->setLayout(ParameterEditor::Layout::nameHidden);
    parameterEditors.getLast()->setSize(150, 20);

    desiredWidth = 180;
}

void AudioMonitorEditor::selectedStreamHasChanged()
{

    if (selectedStream == 0) return;
    
    audioMonitor->setSelectedStream(selectedStream);
}
