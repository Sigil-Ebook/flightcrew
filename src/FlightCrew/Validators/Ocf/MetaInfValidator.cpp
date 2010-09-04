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
#include "MetaInfValidator.h"
#include "Misc/ErrorResultCollector.h"
#include <ToXercesStringConverter.h>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

namespace FlightCrew
{
    
MetaInfValidator::MetaInfValidator()
    :
    m_EncryptionSchema( ENCRYPTION_XSD,
                        ENCRYPTION_XSD_LEN,
                        toX( ENCRYPTION_XSD_ID ) ),
    m_ContainerSchema( CONTAINER_XSD,
                       CONTAINER_XSD_LEN,
                       toX( CONTAINER_XSD_ID ) ),
    m_SignaturesSchema( SIGNATURES_XSD,
                        SIGNATURES_XSD_LEN,
                        toX( SIGNATURES_XSD_ID ) ),
    m_XencSchema( XENC_SCHEMA_XSD,
                  XENC_SCHEMA_XSD_LEN,
                  toX( XENC_SCHEMA_XSD_ID ) ),
    m_XmldsigSchema( XMLDSIG_CORE_SCHEMA_XSD,
                     XMLDSIG_CORE_SCHEMA_XSD_LEN,
                     toX( XMLDSIG_CORE_SCHEMA_XSD_ID ) )
{

}


std::vector<Result> MetaInfValidator::ValidateMetaInfFile(
    const fs::path &filepath,
    const std::string &xsd_id_to_use )
{
    boost::scoped_ptr< xc::SAX2XMLReader > parser( xc::XMLReaderFactory::createXMLReader() );

    parser->setFeature( xc::XMLUni::fgSAX2CoreValidation,            true  );
    parser->setFeature( xc::XMLUni::fgXercesLoadSchema,              false );
    parser->setFeature( xc::XMLUni::fgXercesUseCachedGrammarInParse, true  );
    parser->setFeature( xc::XMLUni::fgXercesSkipDTDValidation,       true  );

    // We don't need DTD validation
    parser->setProperty( xc::XMLUni::fgXercesScannerName, 
                         (void*) xc::XMLUni::fgSGXMLScanner );    

    LoadSchemas( *parser, xsd_id_to_use );

    ErrorResultCollector collector;
    parser->setErrorHandler( &collector );

    try
    {
        parser->parse( filepath.string().c_str() );
    }

    catch ( xc::SAXException& exception )
    {
    	collector.AddNewExceptionAsResult( exception );
    }

    catch ( xc::XMLException& exception )
    {
        collector.AddNewExceptionAsResult( exception );
    }    

    return collector.GetResults();
}


void MetaInfValidator::LoadSchemas( xc::SAX2XMLReader &parser, const std::string &xsd_id_to_use )
{
    if ( xsd_id_to_use.empty() )

        return;
    
    // Normally we would just load all the schemas 
    // and have Xerces pick the one to use by the id,
    // but for some reason Xerces borks out when we 
    // load schemas that we then don't use.
    if ( xsd_id_to_use == CONTAINER_XSD_ID )
    {
        parser.loadGrammar( m_ContainerSchema,  xc::Grammar::SchemaGrammarType, true );
    }

    else if ( xsd_id_to_use == ENCRYPTION_XSD_ID )
    {
        parser.loadGrammar( m_XmldsigSchema,    xc::Grammar::SchemaGrammarType, true );  
        parser.loadGrammar( m_XencSchema,       xc::Grammar::SchemaGrammarType, true );
        parser.loadGrammar( m_EncryptionSchema, xc::Grammar::SchemaGrammarType, true );
    }

    else if ( xsd_id_to_use == SIGNATURES_XSD_ID )
    {
        parser.loadGrammar( m_XmldsigSchema,    xc::Grammar::SchemaGrammarType, true );  
        parser.loadGrammar( m_SignaturesSchema, xc::Grammar::SchemaGrammarType, true );  
    }

    parser.setProperty( xc::XMLUni::fgXercesSchemaExternalSchemaLocation, 
                        (void*) toX( std::string( CONTAINER_XSD_NS )
                                        .append( " " )
                                        .append( xsd_id_to_use ) 
                                    ) 
                       );
}

} //namespace FlightCrew
