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
#include "PackageAttributesPresent.h"
#include "Misc/Utilities.h"

std::vector<Result> PackageAttributesPresent::ValidateXml( const xc::DOMDocument &document )
{
    std::vector< std::string > allowed_attributes;
    allowed_attributes.push_back( "version" );
    allowed_attributes.push_back( "unique-identifier" );
    allowed_attributes.push_back( "id" );

    std::vector< std::string > mandatory_attributes;
    mandatory_attributes.push_back( "version" );
    mandatory_attributes.push_back( "unique-identifier" );

    return Util::Extend( 
        HasOnlyAllowedAttributes( "package", allowed_attributes, document ), 
        HasMandatoryAttributes( "package", mandatory_attributes, document ) );
}

