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
#include "AllowedChildrenValidator.h"
#include <FromXercesStringConverter.h>
#include <ToXercesStringConverter.h>
#include <XmlUtils.h>
#include <algorithm>

std::vector<Result> AllowedChildrenValidator::ValidateAllowedChildren( 
    const std::string &parent_name, 
    const std::vector< std::string > &allowed_children, 
    const xc::DOMDocument &document )
{
    xc::DOMNodeList *parents_matching = document.getElementsByTagNameNS(
        toX( "*" ),  toX( parent_name.c_str() ) );

    std::vector<Result> results;

    if ( parents_matching->getLength() < 1 )
    {
        results.push_back( Result( UNABLE_TO_PERFORM_VALIDATION ) );
        return results;
    }

    xc::DOMElement* parent = static_cast< xc::DOMElement* >( parents_matching->item( 0 ) );
    std::vector< xc::DOMElement* > children = xe::GetElementChildren( *parent );

    for ( uint i = 0; i < children.size(); ++i )
    {
        std::string tag_name = fromX( children[ i ]->getTagName() );

        std::vector< std::string >::const_iterator result;
        result = std::find( allowed_children.begin(), allowed_children.end(), tag_name );

        // Not found in allowed children
        if ( result == allowed_children.end() )

            results.push_back( NotAllowedChildResult( *children[ i ] ) );
    } 

    if ( results.empty() )

        results.push_back( Result() );

    return results;
}


Result AllowedChildrenValidator::NotAllowedChildResult( const xc::DOMNode &child )
{
    Result result = ResultWithNodeLocation( 
        ERROR_XML_CHILD_NOT_RECOGNIZED, child );

    const xc::DOMElement* element = static_cast< const xc::DOMElement* >( &child );
    const xc::DOMElement* parent  = static_cast< const xc::DOMElement* >( child.getParentNode() );

    result.AddMessageArgument( fromX( element->getTagName() ) );
    result.AddMessageArgument( fromX( parent->getTagName() ) );

    return result;
}

