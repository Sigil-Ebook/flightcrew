/************************************************************************
**
**  Copyright (C) 2011  John Schember
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

TEST( NormalizePath, PathIsCorrect )
{
    ASSERT_EQ( NormalizePath( "/var/folders/l3/image.html" ), Utf8PathToBoostPath( "/var/folders/l3/image.html" ) );
    ASSERT_EQ( NormalizePath( "/var/folders/T/image.html" ), Utf8PathToBoostPath( "/var/folders/T/image.html" ) );
    ASSERT_EQ( NormalizePath( "/var/folders/./image.html" ), Utf8PathToBoostPath( "/var/folders/image.html" ) );
    ASSERT_EQ( NormalizePath( "/var/folders/../image.html" ), Utf8PathToBoostPath( "/var/image.html" ) );
    ASSERT_EQ( NormalizePath( "/var/folders/../test/123/456/789/../.././abc/image.html" ), Utf8PathToBoostPath( "/var/test/123/abc/image.html" ) );
    ASSERT_EQ( NormalizePath( "/var/folders/l3/_x3zf0jn3pz22r7_ktjtt0hw0000gn/T/Sigil/./scratchpad/2230a344-5ccb-42fa-99ab-29135345e11f/../../OEBPS/Text/../Images/ie5e3bpitabqoeb.png" ), Utf8PathToBoostPath( "/var/folders/l3/_x3zf0jn3pz22r7_ktjtt0hw0000gn/T/Sigil/OEBPS/Images/ie5e3bpitabqoeb.png" ) );
}
