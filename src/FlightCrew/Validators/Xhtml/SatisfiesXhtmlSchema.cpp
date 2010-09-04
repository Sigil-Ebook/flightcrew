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
#include <LocationAwareDOMParser.h>
#include <xercesc/sax/SAXException.hpp>

namespace FlightCrew
{

SatisfiesXhtmlSchema::SatisfiesXhtmlSchema()
    :
    m_Dtd( XHTML11_FLAT_DTD,
           XHTML11_FLAT_DTD_LEN,
           toX( XHTML11_FLAT_DTD_ID ) ),
    m_OpsSchema( OPS201_XSD,
                 OPS201_XSD_LEN,
                 toX( OPS201_XSD_ID ) ),
    m_OpsSwitchSchema( OPS_SWITCH_XSD, 
                       OPS_SWITCH_XSD_LEN,
                       toX( OPS_SWITCH_XSD_ID ) ),
    m_SvgSchema( SVG11_XSD, 
                 SVG11_XSD_LEN,  
                 toX( SVG11_XSD_ID ) ),
    m_XlinkSchema( XLINK_XSD, 
                   XLINK_XSD_LEN,
                   toX( XLINK_XSD_ID ) ),
    m_XmlSchema( XML_XSD, 
                 XML_XSD_LEN,
                 toX( XML_XSD_ID ) )
{

}


std::vector<Result> SatisfiesXhtmlSchema::ValidateFile( const fs::path &filepath )
{
    xe::LocationAwareDOMParser parser;

    parser.setDoSchema(             true  );
    parser.setLoadSchema(           false );
    parser.setSkipDTDValidation(    true  );
    parser.setDoNamespaces(         true  );
    parser.useCachedGrammarInParse( true  );  

    parser.setValidationScheme( xc::AbstractDOMParser::Val_Always ); 

    parser.loadGrammar( m_Dtd,             xc::Grammar::DTDGrammarType,    true );
    parser.loadGrammar( m_XmlSchema,       xc::Grammar::SchemaGrammarType, true );
    parser.loadGrammar( m_XlinkSchema,     xc::Grammar::SchemaGrammarType, true );
    parser.loadGrammar( m_SvgSchema,       xc::Grammar::SchemaGrammarType, true );
    parser.loadGrammar( m_OpsSwitchSchema, xc::Grammar::SchemaGrammarType, true );
    parser.loadGrammar( m_OpsSchema,       xc::Grammar::SchemaGrammarType, true );     

    parser.setExternalSchemaLocation( "http://www.w3.org/1999/xhtml ops201.xsd" );

    ErrorResultCollector collector;
    parser.setErrorHandler( &collector );

    try
    {
        parser.parse( filepath.string().c_str() );
    }

    catch ( xc::SAXException& exception )
    {
    	collector.AddNewExceptionAsResult( exception );
    }

    catch ( xc::XMLException& exception )
    {
        collector.AddNewExceptionAsResult( exception );
    }  

    catch ( xc::DOMException& exception )
    {
        collector.AddNewExceptionAsResult( exception );
    }

    return collector.GetResults();
}

} //namespace FlightCrew
