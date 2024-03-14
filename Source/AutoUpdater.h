/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2023 Open Ephys

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

    Reference : https://github.com/juce-framework/JUCE/blob/6.0.8/extras/Projucer/Source/Application/jucer_AutoUpdater.h

*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainWindow;
class DownloadThread;

/** 
	Helper class to check for new versions of the application and download them.
*/
class LatestVersionCheckerAndUpdater   : public DeletedAtShutdown,
                                         private Thread
{
public:

    /** Constructor */
    LatestVersionCheckerAndUpdater();
    
    /** Destructor */
    ~LatestVersionCheckerAndUpdater() override;

    /** Holds information about a file to download */
    struct Asset
    {
        const String name;
        const String url;
        const int size;
    };

    /** Checks for a newer version of the GUI */
    void checkForNewVersion (bool isBackgroundCheck, MainWindow* mw);

    JUCE_DECLARE_SINGLETON_SINGLETHREADED_MINIMAL (LatestVersionCheckerAndUpdater)

private:
    
    /** Download new version in background thread */
    void run() override;

    void askUserAboutNewVersion (const String&, const String&, const Asset& asset);
    void askUserForLocationToDownload (const Asset& asset);
    void downloadAndInstall (const Asset& asset, const File& targetFile);

    //==============================================================================
    bool backgroundCheck = false;
    MainWindow* mainWindow;

    std::unique_ptr<DownloadThread> downloader;
    std::unique_ptr<Component> dialogWindow;
};
