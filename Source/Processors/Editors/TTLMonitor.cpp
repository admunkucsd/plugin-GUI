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

#include "TTLMonitor.h"
#include "../Settings/EventChannel.h"
#include "GenericEditor.h"

TTLBitDisplay::TTLBitDisplay (Colour colour_, String tooltipString_)
    : colour (colour_),
      tooltipString (tooltipString_),
      state (false),
      changedSinceLastRedraw (true)
{
}

String TTLBitDisplay::getTooltip()
{
    return tooltipString;
}

void TTLBitDisplay::setState (bool state_)
{
    state = state_;

    changedSinceLastRedraw = true;
}

void TTLBitDisplay::paint (Graphics& g)
{
    g.setColour (findColour (ThemeColors::outline));
    g.fillRect (0, 0, getWidth(), getHeight());

    if (state)
        g.setColour (colour);
    else
        g.setColour (findColour (ThemeColors::widgetBackground));

    g.fillRect (1, 1, getWidth() - 2, getHeight() - 2);

    changedSinceLastRedraw = false;
}

TTLMonitor::TTLMonitor (int bitSize_, int maxBits_) : maxBits (maxBits_), bitSize (bitSize_)
{
    colours.add (Colour (224, 185, 36));
    colours.add (Colour (243, 119, 33));
    colours.add (Colour (237, 37, 36));
    colours.add (Colour (217, 46, 171));
    colours.add (Colour (101, 31, 255));
    colours.add (Colour (48, 117, 255));
    colours.add (Colour (116, 227, 156));
    colours.add (Colour (82, 173, 0));

    displays.clear();

    for (int bit = 0; bit < maxBits; bit++)
    {
        displays.add (new TTLBitDisplay (colours[bit % colours.size()],
                                         "Bit " + String (bit + 1)));
        addAndMakeVisible (displays.getLast());
    }
}

void TTLMonitor::resized()
{
    int xloc = 0;

    int yloc = getHeight() / 2 - bitSize / 2;

    for (int bit = 0; bit < maxBits; bit++)
    {
        displays[bit]->setBounds (xloc, yloc, bitSize, bitSize);
        xloc += bitSize - 1;
    }
}

int TTLMonitor::updateSettings (Array<EventChannel*> eventChannels)
{
    return 0;
}

void TTLMonitor::setState (int line, bool state)
{
    if (line < maxBits)
        displays[line]->setState (state);
}

void TTLMonitor::timerCallback()
{
    for (auto display : displays)
    {
        if (display->changedSinceLastRedraw)
            display->repaint();
    }
}

void TTLMonitor::startAcquisition()
{
    startTimer (50);
}

void TTLMonitor::stopAcquisition()
{
    stopTimer();
}

void TTLMonitor::handleCommandMessage (int commandId)
{
    repaint();
}