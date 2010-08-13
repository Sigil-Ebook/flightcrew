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

namespace FlightCrew
{

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


const std::string ErrorMessages::MessageForId( ResultId error_id )
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
        "All OK.";
    m_Messages[ ERROR_GENERIC ] =
        "Error.";

    m_Messages[ ERROR_XML_SYNTAX ] =
        "XML syntax error.";
    m_Messages[ ERROR_XML_ELEMENT_NOT_PRESENT ] =
        "The <%1%> element is missing.";
    m_Messages[ ERROR_XML_WRONG_ELEMENT_COUNT ] =
        "There needs to be one and only one <%1%> element.";
    m_Messages[ ERROR_XML_CHILD_NOT_RECOGNIZED ] =
        "The <%1%> element is not an allowed child of the <%2%> element.";
    m_Messages[ ERROR_XML_ATTRIBUTE_NOT_RECOGNIZED ] =
        "The \"%1%\" attribute is not an allowed attribute of the <%2%> element.";  
    m_Messages[ ERROR_XML_REQUIRED_ATTRIBUTE_MISSING ] =
        "The required attribute \"%1%\" is missing from the <%2%> element.";
    m_Messages[ ERROR_XML_ID_NOT_UNIQUE ] =
        "An element with ID value \"%1%\" already exists in the document.";    

    m_Messages[ ERROR_OPF_PACKAGE_NOT_ROOT ] =
        "The <package> element is not the root element.";
    m_Messages[ ERROR_OPF_IDREF_ID_DOES_NOT_EXIST ] =
        "The <itemref>'s idref is pointing to an <item> with id=\"%1%\" which "
        "does not exist in the <manifest>.";
    m_Messages[ ERROR_OPF_BAD_PACKAGE_VERSION ] =
        "The <package> element's \"version\" attribute value needs to be \"%1%\", and is \"%2%\".";
    m_Messages[ ERROR_OPF_BAD_ITEM_LINEAR_VALUE ] =
        "The \"linear\" attribute of the <item> element can only have a value of \"yes\" or \"no\".";
    m_Messages[ ERROR_OPF_BAD_CREATOR_OR_CONTRIBUTOR_ROLE_VALUE ] =
        "The \"role\" value \"%1%\" is not a registered MARC value. Either use a valid MARC "
        "relator or start your relator with \"oth.\"";
    m_Messages[ ERROR_OPF_BAD_REFERENCE_TYPE_VALUE ] =
        "The \"type\" value \"%1%\" is not an OPF-specified value. Either use a predefined "
        "type or start your type with \"other.\"";    
}

} // namespace FlightCrew