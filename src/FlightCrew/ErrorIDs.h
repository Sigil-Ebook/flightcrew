/************************************************************************
**
**  Copyright (C) 2010  Strahinja Markovic
**
**  This file is part of FlightCrew.
**
**  FlightCrew is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  FlightCrew is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef ERRORID_H
#define ERRORID_H

enum ErrorId
{
    ALL_OK = 100,
    ERROR_GENERIC,
    ERROR_XML_SYNTAX,
    ERROR_OPF_PACKAGE_NOT_ROOT,
    ERROR_OPF_NO_TITLE,
    ERROR_OPF_WRONG_MANIFEST_COUNT,
    ERROR_OPF_WRONG_METADATA_COUNT,
    ERROR_OPF_WRONG_SPINE_COUNT,
    ERROR_OPF_NO_IDENTIFIER,
    ERROR_XML_CHILD_NOT_RECOGNIZED,
};

#endif // ERRORID_H