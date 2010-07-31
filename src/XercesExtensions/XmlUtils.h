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
#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <vector>
#include <string>
#include <xercesc/dom/DOMNode.hpp>
#include "NodeLocationInfo.h"

namespace XERCES_CPP_NAMESPACE { class DOMElement; class DOMDocument; }
namespace xc = XERCES_CPP_NAMESPACE;

namespace XercesExt
{
    NodeLocationInfo GetNodeLocationInfo( const xc::DOMNode &node );

    std::vector< xc::DOMElement* > GetElementChildren( const xc::DOMElement &element );

    bool ElementListContains( std::vector< xc::DOMElement* > element_list,
                              const std::string &tag_name );

   /**
     * From the provided list of element names, returns the first element
     * present in the document.
     *
     * @param element_names The list of element names to search for.
     * @param document The parent DOM document.
     * @return The first element matching one of the provided names
     *         or NULL if none were found.
     */
    xc::DOMNode* GetFirstAvailableElement( const std::vector< std::string > &element_names,
                                           const xc::DOMDocument &document );

   /**
     * Returns the first element present in the document that matches
     * the provided name.
     *
     * @param element_name The element name to search for.
     * @param document The parent DOM document.
     * @return The first element matching the provided name
     *         or NULL if none were found.
     */
    xc::DOMNode* GetFirstAvailableElement( const std::string &element_name,
                                           const xc::DOMDocument &document );
}

#endif // XMLUTILS_H
