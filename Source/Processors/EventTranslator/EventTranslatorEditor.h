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

#ifndef __EVENTTRANSLATOREDITOR_H_D6EC8B48__
#define __EVENTTRANSLATOREDITOR_H_D6EC8B48__

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Utils/Utils.h"
#include "../Editors/GenericEditor.h"

#include "../RecordNode/RecordNodeEditor.h"

class EventTranslator;

class EventTranslatorEditor : public GenericEditor
{
public:
    /** Constructor */
    EventTranslatorEditor (GenericProcessor* parentNode);

    /** Destructor */
    virtual ~EventTranslatorEditor();

    /** Updates settings when signal chain is updated */
    void updateSettings() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EventTranslatorEditor);
};

#endif // __EVENTTRANSLATOREDITOR_H_D6EC8B48__
