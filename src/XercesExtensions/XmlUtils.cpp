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

}
