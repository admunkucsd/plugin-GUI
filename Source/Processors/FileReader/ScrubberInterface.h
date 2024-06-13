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

#ifndef __SCRUBBERINTERFACE_H_D6EC8B48__
#define __SCRUBBERINTERFACE_H_D6EC8B48__

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../Editors/GenericEditor.h"

#include "FileReader.h"
#include "FileReaderEditor.h"
class PlaybackButton : public Button
{
public:
    PlaybackButton (FileReader* reader)
        : juce::Button ("PlaybackButton"), fileReader (reader), isActive (true) {}
    ~PlaybackButton() {};

    bool getState();
    void setState (bool isActive);

private:
    FileReader* fileReader;
    bool isActive;

    void paintButton (Graphics& g, bool isMouseOver, bool isButtonDown) override;
};

class Timeline : public Component, public Timer
{
public:
    Timeline (FileReader* reader) : fileReader (reader) {}
    virtual ~Timeline() {}

    virtual int getStartInterval() = 0;
    virtual int getIntervalWidth() = 0;
    virtual int getIntervalDurationInSeconds() = 0;

    virtual void timerCallback() = 0;

    void setStartStopTimes (int start, int stop)
    {
        startMs = start;
        stopMs = stop;
    }

protected:
    FileReader* fileReader;

    int startMs = 0;
    int stopMs = 0;

    void paint (Graphics& g) override = 0;
    void mouseDown (const MouseEvent& event) override = 0;
    void mouseDrag (const MouseEvent& event) override = 0;
    void mouseUp (const MouseEvent& event) override = 0;
};

class FullTimeline : public Timeline
{
public:
    FullTimeline (FileReader* fr)
        : Timeline (fr), intervalStartPosition (0)
    {
        startTimer (50);
    }
    ~FullTimeline() override {};

    int getStartInterval() { return intervalStartPosition; }
    int getIntervalWidth() { return intervalWidth; }
    int getIntervalDurationInSeconds();

    void setIntervalPosition (int pos);

    void timerCallback() override { repaint(); };

private:
    int intervalStartPosition;
    int intervalWidth;
    bool intervalIsSelected;

    void paint (Graphics& g) override;
    void mouseDown (const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    void mouseUp (const MouseEvent& event) override;

    bool leftSliderIsSelected;
};

class ZoomTimeline : public Timeline
{
public:
    ZoomTimeline (FileReader* fr)
        : Timeline (fr),
          sliderWidth (8),
          widthInSeconds (30),
          leftSliderPosition (0),
          rightSliderPosition (110)
    {
        startTimer (50);
    }
    ~ZoomTimeline() override {};

    int getStartInterval() { return leftSliderPosition; }
    int getIntervalWidth() { return rightSliderPosition - leftSliderPosition; }
    int getIntervalDurationInSeconds();

    void timerCallback() override { repaint(); };

private:
    int sliderWidth;
    int widthInSeconds;
    float leftSliderPosition;
    float rightSliderPosition;
    float lastDragXPosition;

    void paint (Graphics& g) override;
    void mouseDown (const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    void mouseUp (const MouseEvent& event) override;

    bool leftSliderIsSelected;
    bool rightSliderIsSelected;
    bool playbackRegionIsSelected;
};

class ScrubberInterface : public Component, public Button::Listener
{
public:
    ScrubberInterface (FileReader* reader);
    ~ScrubberInterface() override {};

    std::unique_ptr<Label> zoomStartTimeLabel;
    std::unique_ptr<Label> zoomMiddleTimeLabel;
    std::unique_ptr<Label> zoomEndTimeLabel;
    std::unique_ptr<Label> fullStartTimeLabel;
    std::unique_ptr<Label> fullEndTimeLabel;

    std::unique_ptr<Timeline> fullTimeline;
    std::unique_ptr<Timeline> zoomTimeline;

    //std::unique_ptr<PlaybackButton> playbackButton; //deprecated

    void buttonClicked (Button* button) override;
    void paintOverChildren (Graphics& g) override;
    void updatePlaybackTimes();
    void updateZoomTimeLabels();
    int getFullTimelineStartPosition();
    int getZoomTimelineStartPosition();
    void update();

private:
    FileReader* fileReader;
};

#endif // __SCRUBBERINTERFACE_H_D6EC8B48__