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
#include "Validators/Opf/PackageAttributesPresent.h"
#include "Result.h"

using namespace FlightCrew;

TEST( PackageAttributesPresentTest, NotAllowedAttributes )
{
    PackageAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/PackageAttributesPresent_NotAllowedAttributes.xml" );
            
    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_ATTRIBUTE_NOT_RECOGNIZED );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 2 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 114 );

    std::vector< std::string > message_arguments1 = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments1[ 0 ], "breakme" );
    EXPECT_EQ( message_arguments1[ 1 ], "package" );
}

TEST( PackageAttributesPresentTest, MissingAttributes )
{
    PackageAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/opf_tests/PackageAttributesPresent_MissingAttributes.xml" );

    ASSERT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_REQUIRED_ATTRIBUTE_MISSING );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 2 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 58 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "version" );
    EXPECT_EQ( message_arguments[ 1 ], "package" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_XML_REQUIRED_ATTRIBUTE_MISSING );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 2 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 58 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "unique-identifier" );
    EXPECT_EQ( message_arguments[ 1 ], "package" );
}

TEST( PackageAttributesPresentTest, AllowedAttributes )
{
    PackageAttributesPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/PackageAttributesPresent_AllowedAttributes.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

