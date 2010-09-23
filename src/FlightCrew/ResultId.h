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

#include "ResultType.h"

namespace FlightCrew
{

enum ResultId
{
    ALL_OK = 100,
    UNABLE_TO_PERFORM_VALIDATION,

    ERROR_GENERIC = 300,
    ERROR_SCHEMA_NOT_SATISFIED,

    ERROR_EPUB_NOT_VALID_ZIP_ARCHIVE = 500,
    ERROR_EPUB_NO_CONTAINER_XML,

    ERROR_XML_NOT_WELL_FORMED = 700,
    ERROR_XML_ELEMENT_NOT_PRESENT,
    ERROR_XML_WRONG_ELEMENT_COUNT,
    ERROR_XML_CHILD_NOT_RECOGNIZED,
    ERROR_XML_ATTRIBUTE_NOT_RECOGNIZED,
    ERROR_XML_REQUIRED_ATTRIBUTE_MISSING,
    ERROR_XML_ID_NOT_UNIQUE,
    ERROR_XML_BAD_ID_VALUE,
    ERROR_XML_SPECIFIES_NEITHER_UTF8_NOR_UTF16,
    ERROR_XML_BYTESTREAM_NEITHER_UTF8_NOR_UTF16,

    ERROR_OPF_PACKAGE_NOT_ROOT = 900,
    ERROR_OPF_IDREF_ID_DOES_NOT_EXIST,
    ERROR_OPF_PACKAGE_UNIQUE_IDENTIFIER_DOES_NOT_EXIST,
    ERROR_OPF_BAD_PACKAGE_VERSION,
    ERROR_OPF_BAD_ITEM_LINEAR_VALUE,
    ERROR_OPF_BAD_CREATOR_OR_CONTRIBUTOR_ROLE_VALUE,
    ERROR_OPF_BAD_REFERENCE_TYPE_VALUE,
    ERROR_OPF_BAD_DATE_VALUE,
    ERROR_OPF_ITEM_HREF_INVALID_URI,
    ERROR_OPF_ITEM_HREF_HAS_FRAGMENT,
    ERROR_OPF_ITEM_HREF_NOT_UNIQUE,
    ERROR_OPF_ITEM_REQMOD_WITHOUT_REQNS,
    ERROR_OPF_NCX_NOT_PRESENT,

    WARNING_GENERIC = ResultType_WARNING
};

} // namespace FlightCrew

#endif // RESULTID_H
