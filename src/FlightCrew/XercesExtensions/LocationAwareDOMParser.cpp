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
#include <xercesc/internal/XMLScanner.hpp>
#include "LocationAwareDOMParser.h"

static const char *LOCATION_INFO_KEY = "LocationInfoKey";

LocationAwareDOMParser::LocationAwareDOMParser( xc::XMLValidator   *const valToAdopt,
                                                xc::MemoryManager  *const manager,
                                                xc::XMLGrammarPool *const gramPool )
    :
    xc::XercesDOMParser( valToAdopt, manager, gramPool )
{
     m_LocationInfoKey = xc::XMLString::transcode( LOCATION_INFO_KEY );
}


LocationAwareDOMParser::~LocationAwareDOMParser()
{
    xc::XMLString::release( &m_LocationInfoKey );
}


void LocationAwareDOMParser::startElement( const xc::XMLElementDecl &elemDecl,
                                           const unsigned int uriId,
                                           const XMLCh *const prefixName,
                                           const xc::RefVectorOf< xc::XMLAttr > &attrList,
                                           const unsigned int attrCount,
                                           const bool isEmpty,
                                           const bool isRoot )
{
    xc::XercesDOMParser::startElement(
            elemDecl, uriId, prefixName, attrList, attrCount, isEmpty, isRoot );

    const xc::Locator* locator = getScanner()->getLocator();
    int line_number   = (int) locator->getLineNumber();
    int column_number = (int) locator->getColumnNumber();

    xc::XercesDOMParser::fCurrentNode->setUserData( m_LocationInfoKey,
                                                    new LocationInfo( line_number, column_number ),
                                                    &m_LocationDataHandler );

}


const LocationInfo& LocationAwareDOMParser::GetLocationInfo( const xc::DOMNode &node )
{
    return *static_cast< LocationInfo* >( node.getUserData( m_LocationInfoKey ) );
}
