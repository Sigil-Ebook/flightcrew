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
#include "XmlValidator.h"
#include <ToXercesStringConverter.h>
#include <LocationAwareDOMParser.h>
#include <XmlUtils.h>

const std::string OPF_XML_NAMESPACE = "http://www.idpf.org/2007/opf"; 
const std::string DC_XML_NAMESPACE  = "http://purl.org/dc/elements/1.1/";


std::vector<Result> XmlValidator::ValidateFile( const fs::path &filepath )
{
    xe::LocationAwareDOMParser parser;
    parser.setDoNamespaces( true );
    parser.parse( filepath.string().c_str() );

    return ValidateXml( *parser.getDocument() );
}


Result XmlValidator::ResultWithNodeLocation( ResultId error_id, 
                                             const std::string &element_name,
                                             const xc::DOMDocument &document )
{
    xc::DOMNodeList *matching_elements = document.getDocumentElement()->
        getElementsByTagNameNS( toX( "*" ),  toX( element_name ) );

    if ( matching_elements->getLength() == 1 )
    
        return ResultWithNodeLocation( error_id, *matching_elements->item( 0 ) );

    return Result( error_id );
}


Result XmlValidator::ResultWithNodeLocation( ResultId error_id, 
                                             const xc::DOMNode &node )
{
    return Result( error_id, xe::GetNodeLocationInfo( node ) );
}