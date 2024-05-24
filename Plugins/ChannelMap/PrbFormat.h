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

#ifndef __PRBFORMAT_H_330E50E0__
#define __PRBFORMAT_H_330E50E0__

#include <ProcessorHeaders.h>

#include "ChannelMap.h"

/**

   JSON-based file format for storing channel map settings.
 
*/
class PrbFormat
{
public:

    /** Write file from settings */
    static void write (File filename, ChannelMapSettings* settings)
    {
        FileOutputStream outputStream (filename);
        outputStream.setPosition (0);
        outputStream.truncate();

        DynamicObject info;
        DynamicObject* nestedObj = new DynamicObject();

        Array<var> arr;
        Array<var> arr2;

        for (int i = 0; i < settings->channelOrder.size(); i++)
        {
            arr.add (var (settings->channelOrder[i]));
            arr2.add (var (settings->isEnabled[i]));
        }

        nestedObj->setProperty ("mapping", var (arr));
        nestedObj->setProperty ("enabled", var (arr2));

        info.setProperty ("0", nestedObj);

        info.writeAsJSON (outputStream, JSON::FormatOptions {}.withIndentLevel (2).withSpacing (JSON::Spacing::multiLine).withMaxDecimalPlaces (3));
    }

    /** Read settings from file */
    static void read (File filename, ChannelMapSettings* settings)
    {
        FileInputStream inputStream (filename);

        var json = JSON::parse (inputStream);

        var returnVal = -255;

        var channelGroup = json.getProperty (Identifier ("0"), returnVal);

        if (channelGroup.equalsWithSameType (returnVal))
        {
            return;
        }

        var mapping = channelGroup[Identifier ("mapping")];
        Array<var>* map = mapping.getArray();

        var enabled = channelGroup[Identifier ("enabled")];
        Array<var>* enbl = enabled.getArray();

        for (int i = 0; i < map->size(); i++)
        {
            int ch = map->getUnchecked (i);
            settings->channelOrder.set (i, ch);

            bool en = enbl->getUnchecked (i);
            settings->isEnabled.set (i, en);
        }
    }
};

#endif // __PRBFORMAT_H_330E50E0__
