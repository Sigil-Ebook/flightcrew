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
#include "Validators/Xhtml/SatisfiesXhtmlSchema.h"
#include "Result.h"

using namespace FlightCrew;

TEST( SatisfiesXhtmlSchemaTest, DoesntSatisfySchema )
{
    SatisfiesXhtmlSchema validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xhtml_tests/SatisfiesXhtmlSchema_DoesntSatisfySchema.xhtml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_SCHEMA_NOT_SATISFIED );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 12 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 62 ); 
}

TEST( SatisfiesXhtmlSchemaTest, DoesntSatisfySchemaNoDtd )
{
    SatisfiesXhtmlSchema validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xhtml_tests/SatisfiesXhtmlSchema_DoesntSatisfySchemaNoDtd.xhtml" );

    ASSERT_EQ( results.size(), 4U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_SCHEMA_NOT_SATISFIED );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 10 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 32 ); 

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_SCHEMA_NOT_SATISFIED );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 11 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 61 ); 

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_SCHEMA_NOT_SATISFIED );
    EXPECT_EQ( results[ 2 ].GetErrorLine(), 12 );
    EXPECT_EQ( results[ 2 ].GetErrorColumn(), 49 ); 

    EXPECT_EQ( results[ 3 ].GetResultId(), ERROR_SCHEMA_NOT_SATISFIED );
    EXPECT_EQ( results[ 3 ].GetErrorLine(), 64 );
    EXPECT_EQ( results[ 3 ].GetErrorColumn(), 22 ); 
}


TEST( SatisfiesXhtmlSchemaTest, XmlError )
{
    SatisfiesXhtmlSchema validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xhtml_tests/SatisfiesXhtmlSchema_XmlError.xhtml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_NOT_WELL_FORMED );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 8 ); 
}

TEST( SatisfiesXhtmlSchemaTest, SatisfiesSchemaNoDtd )
{
    SatisfiesXhtmlSchema validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xhtml_tests/SatisfiesXhtmlSchema_SatisfiesSchemaNoDtd.xhtml" );

    ASSERT_EQ( results.size(), 0U );
}

TEST( SatisfiesXhtmlSchemaTest, SatisfiesSchema )
{
    SatisfiesXhtmlSchema validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xhtml_tests/SatisfiesXhtmlSchema_SatisfiesSchema.xhtml" );

    ASSERT_EQ( results.size(), 0U );
}
