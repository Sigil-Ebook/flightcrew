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
#include "ElementPresentValidator.h"
#include <ToXercesStringConverter.h>

std::vector<Result> ElementPresentValidator::VerifyElementPresent( 
    const std::string &element_name, 
    const std::vector< std::string > &possible_parents,
    const xc::DOMDocument &document )
{
    xc::DOMNodeList *matching_elements = document.getElementsByTagNameNS(
                                        toX( "*" ),  toX( element_name.c_str() ) );

    std::vector<Result> results;

    if ( matching_elements->getLength() < 1 )
    {
        xc::DOMNode* parent = GetFirstAvailableElement( possible_parents, document );

        Result result = parent != NULL                                                   ?
                        ResultWithNodeLocation( ERROR_XML_ELEMENT_NOT_PRESENT, *parent ) :
                        Result( ERROR_XML_ELEMENT_NOT_PRESENT );
                        
        result.AddMessageArgument( element_name );
        results.push_back( result );
    }

    else
    {
        results.push_back( Result() );    
    }

    return results;
}


xc::DOMNode* ElementPresentValidator::GetFirstAvailableElement( 
    const std::vector< std::string > &element_names,
    const xc::DOMDocument &document )
{
    foreach( std::string element_name, element_names )
    {
        xc::DOMNodeList *matching_nodes = document.getElementsByTagNameNS(
                                               toX( "*" ),  toX( element_name.c_str() ) );

        if ( matching_nodes->getLength() > 0 )

            return matching_nodes->item( 0 );
    }

    return NULL;
}