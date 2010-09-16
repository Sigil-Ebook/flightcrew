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
#include "Validators/Opf/ItemHrefValid.h"
#include "Result.h"

using namespace FlightCrew;

TEST( ItemHrefValidTest, InvalidURI )
{
    ItemHrefValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemHrefValid_BadValue.xml" );
            
    ASSERT_EQ( results.size(), 4U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_ITEM_HREF_INVALID_URI );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 31 );

    // Encoding the message for the first example is a bit problematic.
    // The other examples will make sure to test that message arguments are set.

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_ITEM_HREF_INVALID_URI );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 28 );

    std::vector< std::string > message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "a a" );

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_OPF_ITEM_HREF_INVALID_URI );
    EXPECT_EQ( results[ 2 ].GetErrorLine(), 6 );
    EXPECT_EQ( results[ 2 ].GetErrorColumn(), 61 );

    message_arguments = results[ 2 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "file://hostname/path/to/the file.txt" );

    EXPECT_EQ( results[ 3 ].GetResultId(), ERROR_OPF_ITEM_HREF_HAS_FRAGMENT );
    EXPECT_EQ( results[ 3 ].GetErrorLine(), 7 );
    EXPECT_EQ( results[ 3 ].GetErrorColumn(), 54 );

    message_arguments = results[ 3 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "http://www.example.com/#ident" );
}

TEST( ItemHrefValidTest, GoodValue )
{
    ItemHrefValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemHrefValid_GoodValue.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

