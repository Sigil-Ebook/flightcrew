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
#include "Validators/Opf/OneSpine.h"
#include "Result.h"

using namespace FlightCrew;

TEST( OneSpineTest, NoSpine_Error )
{
    OneSpine validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneSpine_NoSpine.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_WRONG_ELEMENT_COUNT );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 2 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 88 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "spine" );
}

TEST( OneSpineTest, TwoSpines_Error )
{
    OneSpine validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneSpine_TwoSpines.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_WRONG_ELEMENT_COUNT );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 8 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "spine" );
}

TEST( OneSpineTest, OneSpine_OK )
{
    OneSpine validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneSpine_OneSpine.xml" );

    ASSERT_EQ( results.size(), 0U );
}

