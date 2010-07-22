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
#include "PackageAllowedChildren.h"
#include <ToXercesStringConverter.h>
#include <FromXercesStringConverter.h>
#include <XmlUtils.h>

std::vector<Result> PackageAllowedChildren::ValidateXml( const xc::DOMDocument &document )
{
    xc::DOMElement *package_element = document.getDocumentElement();
    std::vector< xc::DOMElement* > children = xe::GetElementChildren( *package_element );

    std::vector<Result> results;

    for ( int i = 0; i < children.size(); ++i )
    {
        std::string tag_name = fromX( children[ i ]->getTagName() );

        if ( tag_name != "manifest" &&
             tag_name != "metadata" &&
             tag_name != "spine"    &&
             tag_name != "tours"    &&
             tag_name != "guide"
            )
        {
            // TODO: add replacement text for message to Result
            results.push_back( ResultWithNodeLocation( 
                ERROR_XML_CHILD_NOT_RECOGNIZED, *children[ i ] ) );
        }
    } 

    if ( results.empty() )

        results.push_back( Result() );

    return results;
}

