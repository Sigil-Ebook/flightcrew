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
#include "Validators/Opf/IdsValid.h"
#include "Result.h"

using namespace FlightCrew;

TEST( IdsValidTest, BadValue )
{
    IdsValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/IdsValid_BadValue.xml" );
            
    ASSERT_EQ( results.size(), 4U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_BAD_ID_VALUE );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 31 );
    
    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1aaa" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_XML_BAD_ID_VALUE );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 31 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], ":a932541" );

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_XML_BAD_ID_VALUE );
    EXPECT_EQ( results[ 2 ].GetErrorLine(), 6 );
    EXPECT_EQ( results[ 2 ].GetErrorColumn(), 31 );

    message_arguments = results[ 2 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "-aa-aa" );

    EXPECT_EQ( results[ 3 ].GetResultId(), ERROR_XML_BAD_ID_VALUE );
    EXPECT_EQ( results[ 3 ].GetErrorLine(), 7 );
    EXPECT_EQ( results[ 3 ].GetErrorColumn(), 31 );

    message_arguments = results[ 3 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], ".aa.aa" );
}

TEST( IdsValidTest, GoodValue )
{
    IdsValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/IdsValid_GoodValue.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

