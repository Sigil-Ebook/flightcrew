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

#include "XmlUtils.h"
#include "ToXercesStringConverter.h"
#include "FromXercesStringConverter.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <boost/foreach.hpp> 
#define foreach BOOST_FOREACH

extern const char *LOCATION_INFO_KEY;

typedef unsigned int uint;

namespace XercesExt
{

NodeLocationInfo GetNodeLocationInfo( const xc::DOMNode &node )
{
    return *static_cast< NodeLocationInfo* >( node.getUserData( toX( LOCATION_INFO_KEY ) ) );
}


std::vector< xc::DOMElement* > GetElementChildren( const xc::DOMElement &element )
{
    xc::DOMElement *child = element.getFirstElementChild();

    std::vector< xc::DOMElement* > children;

    if ( !child )

        return children;

    children.push_back( child );

    while (true)
    {
         child = child->getNextElementSibling();

         if ( !child )

             return children;
         
         children.push_back( child );
    }

    return children;
}


bool ElementListContains( std::vector< xc::DOMElement* > element_list,
                          const std::string &tag_name )
{
    for ( uint i = 0; i < element_list.size(); ++i )
    {
        std::string current_tag = fromX( element_list[ i ]->getTagName() );

        if ( current_tag == tag_name )
        
            return true;
    } 

    return false;
}

xc::DOMNode* GetFirstAvailableElement( const std::vector< std::string > &element_names,
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

xc::DOMNode* GetFirstAvailableElement( const std::string &element_name, 
                                       const xc::DOMDocument &document )
{
    std::vector< std::string > element_names;
    element_names.push_back( element_name );

    return GetFirstAvailableElement( element_names, document );
}

} // namespace XercesExt
