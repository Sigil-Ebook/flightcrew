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
#ifndef RESULTID_H
#define RESULTID_H

enum ResultId
{
    ALL_OK = 100,
    UNABLE_TO_PERFORM_VALIDATION,

    ERROR_GENERIC,

    ERROR_XML_SYNTAX,
    ERROR_XML_ELEMENT_NOT_PRESENT,
    ERROR_XML_WRONG_ELEMENT_COUNT,
    ERROR_XML_CHILD_NOT_RECOGNIZED,

    ERROR_OPF_PACKAGE_NOT_ROOT,
};

#endif // RESULTID_H