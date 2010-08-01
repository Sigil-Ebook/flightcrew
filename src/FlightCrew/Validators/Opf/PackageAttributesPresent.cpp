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
    std::vector< QName > allowed_attributes;
    allowed_attributes.push_back( QName( "version",           "" ) );
    allowed_attributes.push_back( QName( "unique-identifier", "" ) );
    allowed_attributes.push_back( QName( "id",                "" ) );

    std::vector< Result > allowed_results = HasOnlyAllowedAttributes( 
        QName( "package", OPF_XML_NAMESPACE ), allowed_attributes, document );

    std::vector< QName > mandatory_attributes;
    mandatory_attributes.push_back( QName( "version",           "" ) );
    mandatory_attributes.push_back( QName( "unique-identifier", "" ) );

    std::vector< Result > mandatory_results = HasMandatoryAttributes(   
        QName( "package", OPF_XML_NAMESPACE ), mandatory_attributes, document );

    return Util::Extend( allowed_results, mandatory_results );
}

