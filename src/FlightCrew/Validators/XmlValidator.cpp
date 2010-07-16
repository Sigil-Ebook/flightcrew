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
//#include <xercesc/parsers/AbstractDOMParser.hpp>
//#include <xercesc/dom/DOMImplementation.hpp>
//#include <xercesc/dom/DOMImplementationLS.hpp>
//#include <xercesc/dom/DOMImplementationRegistry.hpp>
//#include <xercesc/dom/DOMLSParser.hpp>
//#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>

#include "XmlValidator.h"
#include "Result.h"

//#include <boost/filesystem.hpp>
//using namespace boost::filesystem;


Result XmlValidator::ValidateFile( const path &filepath )
{
    // Instantiate the DOM parser.
//    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
//    DOMImplementation *dom_implementation = DOMImplementationRegistry::getDOMImplementation( gLS );
//    DOMLSParser       *parser = ( ( DOMImplementationLS * ) dom_implementation )
//                                ->createLSParser( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
    //DOMConfiguration  *config = parser->getDomConfig();

    XercesDOMParser parser;
    parser.setDoNamespaces( true );
    parser.parse( filepath.string().c_str() );

    return ValidateXml( *parser.getDocument() );
}
