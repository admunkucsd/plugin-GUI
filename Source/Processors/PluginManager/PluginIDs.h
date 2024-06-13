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

#ifndef __PLUGIN_IDS_H__
#define __PLUGIN_IDS_H__

namespace Ids
{
#define DECLARE_OPENEPHYS_ID(name) const Identifier name (#name)

DECLARE_OPENEPHYS_ID (OPENEPHYSPLUGIN);
DECLARE_OPENEPHYS_ID (OPENEPHYS_PLUGIN_TYPE);
DECLARE_OPENEPHYS_ID (OPENEPHYS_PROCESSOR_TYPE);

// Parameter Ids
namespace OpenEphysParameter
{
    DECLARE_OPENEPHYS_ID (ID);
    DECLARE_OPENEPHYS_ID (NAME);
    DECLARE_OPENEPHYS_ID (DESCRIPTION);
    DECLARE_OPENEPHYS_ID (TYPE);
    DECLARE_OPENEPHYS_ID (HAS_CUSTOM_BOUNDS);
    DECLARE_OPENEPHYS_ID (DESIRED_BOUNDS);
    DECLARE_OPENEPHYS_ID (DEFAULT_VALUE);
    DECLARE_OPENEPHYS_ID (POSSIBLE_VALUES);
} // namespace OpenEphysParameter

DECLARE_OPENEPHYS_ID (xcodeOpenEphysProjectLocation);
DECLARE_OPENEPHYS_ID (xcodeOpenEphysBinaryLocation);
DECLARE_OPENEPHYS_ID (msvcOpenEphysProjectLocation);
} // namespace Ids

#endif // __PLUGIN_IDS_H__