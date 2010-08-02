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
#include "TitlePresent.h"

namespace FlightCrew
{

std::vector<Result> TitlePresent::ValidateXml( const xc::DOMDocument &document )
{
    std::vector< QName > possible_parents;
    possible_parents.push_back( QName( "metadata",    OPF_XML_NAMESPACE ) );
    possible_parents.push_back( QName( "dc-metadata", OPF_XML_NAMESPACE ) );

    return VerifyElementPresent( 
        QName( "title", DC_XML_NAMESPACE ), possible_parents, document );
}

} //namespace FlightCrew
