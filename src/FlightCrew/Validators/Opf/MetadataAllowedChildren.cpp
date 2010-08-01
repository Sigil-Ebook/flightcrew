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
#include "MetadataAllowedChildren.h"
#include <ToXercesStringConverter.h>
#include <FromXercesStringConverter.h>
#include <XmlUtils.h>

std::vector<Result> MetadataAllowedChildren::ValidateXml( const xc::DOMDocument &document )
{
    xc::DOMNodeList *metadatas = document.getElementsByTagNameNS(
                                    toX( "*" ),  toX( "metadata" ) );

    std::vector<Result> results;

    if ( metadatas->getLength() < 1 )
    {
        results.push_back( Result( UNABLE_TO_PERFORM_VALIDATION ) );
        return results;
    }

    xc::DOMElement* metadata = static_cast< xc::DOMElement* >( metadatas->item( 0 ) );
    std::vector< xc::DOMElement* > children = xe::GetElementChildren( *metadata );

    // A <metadata> element can have either a dc-metadata element and an option
    // x-metadata element, OR the standard children (title, creator, language etc.)
    // plus any other child not in the reserved namespaces.
    // See the OPF schema: 
    // http://www.idpf.org/doc_library/epub/OPF_2.0.1_draft.htm#AppendixA

    if ( xe::ElementListContains( children, "dc-metadata" ) ||
         xe::ElementListContains( children, "x-metadata" ) )
    {
        std::vector<Result> subresults = ValidateDCXChildrenSubset( metadata, children );
        results.insert( results.end(), subresults.begin(), subresults.end() );
    }

    else
    {
        std::vector<Result> subresults = ValidateStandardChildren( metadata, children );
        results.insert( results.end(), subresults.begin(), subresults.end() );
    }

    return results;
}


std::vector<Result> MetadataAllowedChildren::ValidateDCXChildrenSubset( xc::DOMElement* metadata,
                                                                        std::vector< xc::DOMElement* > children )
{
    std::vector<Result> results;

    for ( uint i = 0; i < children.size(); ++i )
    {
        std::string tag_name = fromX( children[ i ]->getLocalName() );

        if ( tag_name != "dc-metadata" &&
             tag_name != "x-metadata" 
            )
        {
            results.push_back( NotAllowedChildResult( *children[ i ] ) );
        }
    } 

    return results;
}


std::vector<Result> MetadataAllowedChildren::ValidateStandardChildren( xc::DOMElement* metadata,
                                                                       std::vector< xc::DOMElement* > children )
{
    std::vector<Result> results;

    for ( uint i = 0; i < children.size(); ++i )
    {
        std::string local_name = fromX( children[ i ]->getLocalName() );

        if ( local_name != "title"       &&
             local_name != "language"    &&
             local_name != "identifier"  &&
             local_name != "creator"     &&
             local_name != "subject"     &&
             local_name != "description" &&
             local_name != "publisher"   &&
             local_name != "contributor" &&
             local_name != "date"        &&
             local_name != "type"        &&
             local_name != "format"      &&
             local_name != "source"      &&
             local_name != "relation"    &&
             local_name != "coverage"    &&
             local_name != "rights"      &&
             local_name != "meta" 
            )
        {
            std::string namespace_name = fromX( children[ i ]->getNamespaceURI() );

            if ( namespace_name == OPF_XML_NAMESPACE ||
                 namespace_name == DC_XML_NAMESPACE
                )
            {
                results.push_back( NotAllowedChildResult( *children[ i ] ) );
            }
        }
    } 

    return results;
}