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
#include "WellFormedXml.h"
#include "Misc/ErrorResultCollector.h"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

namespace FlightCrew
{
    
std::vector<Result> WellFormedXml::ValidateFile( const fs::path &filepath )
{
    boost::scoped_ptr< xc::SAX2XMLReader > parser( xc::XMLReaderFactory::createXMLReader() );

    // We need only the most basic parser
    parser->setProperty( xc::XMLUni::fgXercesScannerName, 
                         (void*) xc::XMLUni::fgWFXMLScanner );    

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

} //namespace FlightCrew
