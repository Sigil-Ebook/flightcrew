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
#include "AttributesPresentValidator.h"
#include "ToXercesStringConverter.h"
#include "FromXercesStringConverter.h"
#include "Misc/Utilities.h"


std::vector<Result> AttributesPresentValidator::HasOnlyAllowedAttributes( 
    const std::string &element_name,
    const std::vector< std::string > &attribute_names, 
    const xc::DOMDocument &document )
{
    xc::DOMNodeList *elements = document.getElementsByTagNameNS(
                                    toX( "*" ),  toX( element_name.c_str() ) );

    std::vector<Result> results;

    for ( int i = 0; i < elements->getLength(); ++i )
    {
        xc::DOMElement* element         = static_cast< xc::DOMElement* >( elements->item( i ) );
        xc::DOMNamedNodeMap *attributes = element->getAttributes();

        for ( int j = 0; j < attributes->getLength(); ++j )
        {
            xc::DOMAttr* attribute = static_cast< xc::DOMAttr* >( attributes->item( j ) );

            if ( !IsAllowedAttribute( *attribute, attribute_names ) )
            {
                Result result = ResultWithNodeLocation( 
                    ERROR_XML_ATTRIBUTE_NOT_RECOGNIZED, *element );

                std::string attribute_name = fromX( attribute->getName() );
                result.AddMessageArgument( attribute_name );
                result.AddMessageArgument( element_name );
                results.push_back( result );
            }
        }
    }    

    return results;
}


std::vector<Result> AttributesPresentValidator::HasMandatoryAttributes( 
    const std::string &element_name, 
    const std::vector< std::string > &attribute_names, 
    const xc::DOMDocument &document )
{
    xc::DOMNodeList *elements = document.getElementsByTagNameNS(
                                    toX( "*" ),  toX( element_name.c_str() ) );

    std::vector<Result> results;

    for ( int i = 0; i < elements->getLength(); ++i )
    {
        xc::DOMElement* element = static_cast< xc::DOMElement* >( elements->item( i ) );

        foreach( std::string attribute_name, attribute_names )
        {
            if ( !element->hasAttribute( toX( attribute_name.c_str() ) ) )
            {
                Result result = ResultWithNodeLocation( 
                    ERROR_XML_REQUIRED_ATTRIBUTE_MISSING, *element );

                result.AddMessageArgument( attribute_name );
                result.AddMessageArgument( element_name );
                results.push_back( result );
            }
        }
    }

    return results;
}

bool AttributesPresentValidator::IsAllowedAttribute( 
    const xc::DOMAttr &attribute, 
    const std::vector< std::string > &allowed_attribute_names )
{
    std::string attribute_name = fromX( attribute.getName() );

    bool allowed_name = Util::Contains< std::string >( 
                            allowed_attribute_names, attribute_name );
    bool is_xmlns = attribute_name == "xmlns";

    return allowed_name || is_xmlns;
}