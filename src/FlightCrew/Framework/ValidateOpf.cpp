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
#include <vector>
#include "Result.h"
#include "Validators/Xml/WellFormedXml.h"
#include "Validators/Xml/UsesUnicode.h"
#include "OpfValidatorsList.h"
#include "Misc/Utilities.h"


namespace FlightCrew
{
   
std::vector< Result > ValidateOpf( const fs::path &filepath )
{
    // TODO: throw exception
    if ( !fs::exists( filepath ) )

        return std::vector< Result >();

    std::vector< Result > results;

    WellFormedXml wf_validator;
    Util::Extend( results, wf_validator.ValidateFile( filepath ) );

    // There is no point in running the other validators 
    // if the document is not well-formed.
    if ( !results.empty() )
  
        return Util::SortedInPlace( results );
  
    std::vector< boost::shared_ptr< XmlValidator > > xmlvalidators =
        GetOpfXmlValidators();

    xc::DOMDocument& document = wf_validator.GetDocument();

    foreach( boost::shared_ptr< XmlValidator > validator, xmlvalidators )
    {
        Util::Extend( results, validator->ValidateXml( document ) );
    }

    Util::Extend( results, UsesUnicode().ValidateFile( filepath ) );
    return Util::SortedInPlace( results );
}

} // namespace FlightCrew