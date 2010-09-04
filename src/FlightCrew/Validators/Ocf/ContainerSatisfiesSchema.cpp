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
#include "ContainerSatisfiesSchema.h"
#include "Misc/ErrorResultCollector.h"
#include <ToXercesStringConverter.h>
#include <XmlUtils.h>
#include <LocationAwareDOMParser.h>

namespace FlightCrew
{

ContainerSatisfiesSchema::ContainerSatisfiesSchema()
    :
    m_ContainerSchema( CONTAINER_XSD,
                       CONTAINER_XSD_LEN,
                       toX( CONTAINER_XSD_ID ) )
{

}


std::vector<Result> ContainerSatisfiesSchema::ValidateFile( const fs::path &filepath )
{
    xe::LocationAwareDOMParser parser;

    parser.setDoSchema( true );
    parser.setLoadSchema( false );
    parser.setSkipDTDValidation( true );

    parser.setDoNamespaces( true );
    parser.setValidationScheme( xc::AbstractDOMParser::Val_Always );
    parser.useCachedGrammarInParse( true );    

    parser.loadGrammar( m_ContainerSchema, xc::Grammar::SchemaGrammarType, true );  

    parser.setExternalSchemaLocation( "urn:oasis:names:tc:opendocument:xmlns:container container.xsd" );
                                      
    ErrorResultCollector collector;
    parser.setErrorHandler( &collector );

    parser.parse( filepath.string().c_str() );

    return collector.GetResults();
}

} //namespace FlightCrew
