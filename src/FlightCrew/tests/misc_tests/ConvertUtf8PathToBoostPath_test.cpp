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

#include <stdafx_tests.h>
#include "Misc/Utilities.h"
#include "exception.h"

using namespace FlightCrew;
using namespace FlightCrew::Util;

TEST( ConvertUtf8PathToBoostPathTest, PathIsNotInUtf8 )
{
    char utf8_path[] = "test_data/something/\xe6\x97\xa5\xd1\x88\xf0\x9d\x84";

    ASSERT_THROW( Utf8PathToBoostPath( utf8_path ), PathNotInUtf8 );
}

TEST( ConvertUtf8PathToBoostPathTest, PathIsInUtf8 )
{
    char utf8_path[] = "test_data/something/\xe6\x97\xa5\xd1\x88\xf0\x9d\x84\x9e";

    ASSERT_NO_THROW( Utf8PathToBoostPath( utf8_path ) );
}
