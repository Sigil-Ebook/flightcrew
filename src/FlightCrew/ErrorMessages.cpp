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

#include <stdafx.h>
#include "ErrorMessages.h"

boost::mutex ErrorMessages::s_AccessMutex;
ErrorMessages* ErrorMessages::s_Instance = NULL;

ErrorMessages& ErrorMessages::Instance()
{
    // We use a static local variable
    // to hold our singleton instance; using a pointer member
    // variable creates problems with object destruction;

    boost::lock_guard< boost::mutex > locker( s_AccessMutex );

    if ( !s_Instance )
    {
        static ErrorMessages messages;
        s_Instance = &messages;
    }

    return *s_Instance;
}


const std::string ErrorMessages::MessageForId( ErrorId error_id )
{
    return m_Messages[ error_id ];
}


ErrorMessages::ErrorMessages()
{
    LoadMessages();
}


void ErrorMessages::LoadMessages()
{
    // It would be great if these could be read from an external file,
    // but we don't want a runtime dependency. So we hard-code them.
    // This would be bad for translations, but since we can't translate the
    // error messages coming from the schema checkers, wo won't be translating
    // these either. So it's not a problem.

    m_Messages[ ALL_OK ] =
        "All OK";
    m_Messages[ ERROR_GENERIC ] =
        "Error";
    m_Messages[ ERROR_XML_SYNTAX ] =
        "XML syntax error";
    m_Messages[ ERROR_OPF_PACKAGE_NOT_ROOT ] =
        "The <package> element is not the root element of the OPF";
    m_Messages[ ERROR_OPF_NO_TITLE ] =
        "There is no <title> element in the OPF";
    m_Messages[ ERROR_OPF_WRONG_MANIFEST_COUNT ] =
        "There needs to be one and only one <manifest> element in the OPF";
    m_Messages[ ERROR_OPF_WRONG_METADATA_COUNT ] =
        "There needs to be one and only one <metadata> element in the OPF";
    m_Messages[ ERROR_OPF_WRONG_SPINE_COUNT ] =
        "There needs to be one and only one <spine> element in the OPF";
}
