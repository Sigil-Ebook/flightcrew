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
#include "DCMetadataAllowedChildren.h"

std::vector<Result> DCMetadataAllowedChildren::ValidateXml( const xc::DOMDocument &document )
{
    std::vector< std::string > allowed_children;

    allowed_children.push_back( "title"       );
    allowed_children.push_back( "language"    );
    allowed_children.push_back( "identifier"  );
    allowed_children.push_back( "creator"     );
    allowed_children.push_back( "subject"     );
    allowed_children.push_back( "description" );
    allowed_children.push_back( "publisher"   );
    allowed_children.push_back( "contributor" );
    allowed_children.push_back( "date"        );
    allowed_children.push_back( "type"        );
    allowed_children.push_back( "format"      );
    allowed_children.push_back( "source"      );
    allowed_children.push_back( "relation"    );
    allowed_children.push_back( "coverage"    );
    allowed_children.push_back( "rights"      );

    return ValidateAllowedChildren( "dc-metadata", allowed_children, document );
}

