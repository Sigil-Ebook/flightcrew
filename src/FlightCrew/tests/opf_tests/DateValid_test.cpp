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
#include "Validators/Opf/DateValid.h"
#include "Result.h"

using namespace FlightCrew;

TEST( DateValidTest, BadValue )
{
    DateValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/DateValid_BadValue.xml" );
            
    ASSERT_EQ( results.size(), 8U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 18 );
    
    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "19997" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 18 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "197" );

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 2 ].GetErrorLine(), 6 );
    EXPECT_EQ( results[ 2 ].GetErrorColumn(), 18 );

    message_arguments = results[ 2 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1997-007" );

    EXPECT_EQ( results[ 3 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 3 ].GetErrorLine(), 7 );
    EXPECT_EQ( results[ 3 ].GetErrorColumn(), 18 );

    message_arguments = results[ 3 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "19970716" );

    EXPECT_EQ( results[ 4 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 4 ].GetErrorLine(), 8 );
    EXPECT_EQ( results[ 4 ].GetErrorColumn(), 18 );

    message_arguments = results[ 4 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1997-07-16T19-20+01:00" );

    EXPECT_EQ( results[ 5 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 5 ].GetErrorLine(), 9 );
    EXPECT_EQ( results[ 5 ].GetErrorColumn(), 18 );

    message_arguments = results[ 5 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1997-07-1619:20-01:00" );

    EXPECT_EQ( results[ 6 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 6 ].GetErrorLine(), 10 );
    EXPECT_EQ( results[ 6 ].GetErrorColumn(), 18 );

    message_arguments = results[ 6 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1997-07-16T19:2001:00" );

    EXPECT_EQ( results[ 7 ].GetResultId(), ERROR_OPF_BAD_DATE_VALUE );
    EXPECT_EQ( results[ 7 ].GetErrorLine(), 11 );
    EXPECT_EQ( results[ 7 ].GetErrorColumn(), 18 );

    message_arguments = results[ 7 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "1997-07-16T19:20:30,45+01:00" );
}

TEST( DateValidTest, GoodValue )
{
    DateValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/DateValid_GoodValue.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

