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
#include "PackageAllowedChildren.h"
#include <ToXercesStringConverter.h>
#include <FromXercesStringConverter.h>
#include <XmlUtils.h>

std::vector<Result> PackageAllowedChildren::ValidateXml( const xc::DOMDocument &document )
{
    std::vector< std::string > allowed_children;

    allowed_children.push_back( "manifest" );
    allowed_children.push_back( "metadata" );
    allowed_children.push_back( "spine"    );
    allowed_children.push_back( "tours"    );
    allowed_children.push_back( "guide"    );

    return ValidateAllowedChildren( "package", allowed_children, document );
}

