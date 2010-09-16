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
#include "Validators/Opf/CreatorOrContributorRoleValid.h"
#include "Result.h"

using namespace FlightCrew;

TEST( CreatorOrContributorRoleValidTest, BadValue )
{
    CreatorOrContributorRoleValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/CreatorOrContributorRoleValid_BadValue.xml" );
            
    ASSERT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_BAD_CREATOR_OR_CONTRIBUTOR_ROLE_VALUE );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 38 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "XXX" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_BAD_CREATOR_OR_CONTRIBUTOR_ROLE_VALUE );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 42 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "YYY" );
}

TEST( CreatorOrContributorRoleValidTest, GoodValue )
{
    CreatorOrContributorRoleValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/CreatorOrContributorRoleValid_GoodValue.xml" );
    
    ASSERT_EQ( results.size(), 0U );
}

