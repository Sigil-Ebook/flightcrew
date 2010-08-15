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
#include "Validators/Opf/ItemLinearValid.h"
#include "Result.h"

using namespace FlightCrew;

TEST( ItemLinearValidTest, BadValue )
{
    ItemLinearValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemLinearValid_BadValue.xml" );
            
    EXPECT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_BAD_ITEM_LINEAR_VALUE );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 6 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 32 );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_BAD_ITEM_LINEAR_VALUE );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 7 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 27 );
}

TEST( ItemLinearValidTest, GoodValue )
{
    ItemLinearValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemLinearValid_GoodValue.xml" );
    
    EXPECT_EQ( results.size(), 0U );
}

