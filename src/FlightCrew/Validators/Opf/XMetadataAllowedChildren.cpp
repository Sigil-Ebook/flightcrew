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
#include "XMetadataAllowedChildren.h"
#include <ToXercesStringConverter.h>
#include <FromXercesStringConverter.h>
#include <XmlUtils.h>

std::vector<Result> XMetadataAllowedChildren::ValidateXml( const xc::DOMDocument &document )
{
    xc::DOMNodeList *xmetadatas = document.getElementsByTagNameNS(
                                    toX( "*" ),  toX( "x-metadata" ) );

    std::vector<Result> results;

    if ( xmetadatas->getLength() < 1 )
    {
        results.push_back( Result( UNABLE_TO_PERFORM_VALIDATION ) );
        return results;
    }

    xc::DOMElement* xmetadata = static_cast< xc::DOMElement* >( xmetadatas->item( 0 ) );
    std::vector< xc::DOMElement* > children = xe::GetElementChildren( *xmetadata );

    for ( uint i = 0; i < children.size(); ++i )
    {
        std::string local_name = fromX( children[ i ]->getLocalName() );

        if ( local_name != "meta" )
        {
            std::string namespace_name = fromX( children[ i ]->getNamespaceURI() );

            if ( namespace_name == "http://www.idpf.org/2007/opf" ||
                 namespace_name == "http://purl.org/dc/elements/1.1/"
                )
            {
                results.push_back( NotAllowedChildResult( *children[ i ] ) );
            }
        }
    }

    if ( results.empty() )

        results.push_back( Result() );

    return results;
}

