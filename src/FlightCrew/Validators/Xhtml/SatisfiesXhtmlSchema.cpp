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
#include "SatisfiesXhtmlSchema.h"
#include "Misc/ErrorResultCollector.h"
#include <ToXercesStringConverter.h>
#include <XmlUtils.h>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <LocationAwareDOMParser.h>

namespace FlightCrew
{

std::vector<Result> FlightCrew::SatisfiesXhtmlSchema::ValidateFile( const fs::path &filepath )
{
    xe::LocationAwareDOMParser parser;

    // We strictly use DTDs
    parser.setDoSchema( false );
    parser.setLoadSchema( false );

    // This scanner only uses DTDs and ignores schemas
    parser.useScanner( xc::XMLUni::fgDGXMLScanner );

    parser.setDoNamespaces( true );
    parser.setValidationScheme( xc::AbstractDOMParser::Val_Always );
    parser.useCachedGrammarInParse( true );    

    xc::MemBufInputSource dtd( XHTML11_FLAT_DTD,
                               XHTML11_FLAT_DTD_LEN,
                               toX( XHTML11_FLAT_DTD_ID ) );        

    parser.loadGrammar( dtd, xc::Grammar::DTDGrammarType, true );

    ErrorResultCollector collector;
    parser.setErrorHandler( &collector );

    parser.parse( filepath.string().c_str() );

    return collector.GetResults();
}

} //namespace FlightCrew
