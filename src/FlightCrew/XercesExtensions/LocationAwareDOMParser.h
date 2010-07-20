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

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include "LocationInfoDataHandler.h"
#include "NodeLocationInfo.h"

class LocationAwareDOMParser : public xc::XercesDOMParser
{
public:

    LocationAwareDOMParser( xc::XMLValidator   *const valToAdopt = 0,
                            xc::MemoryManager  *const manager = xc::XMLPlatformUtils::fgMemoryManager,
                            xc::XMLGrammarPool *const gramPool = 0 );

    /**
      * Destructor.
      */
    ~LocationAwareDOMParser();

    // override
    virtual void startElement( const xc::XMLElementDecl &elemDecl,
                               const unsigned int uriId,
                               const XMLCh *const prefixName,
                               const xc::RefVectorOf< xc::XMLAttr > &attrList,
                               const unsigned int attrCount,
                               const bool isEmpty,
                               const bool isRoot );

    const NodeLocationInfo& GetLocationInfo( const xc::DOMNode &node );

private:
    LocationInfoDataHandler m_LocationDataHandler;
    XMLCh *m_LocationInfoKey;
};
