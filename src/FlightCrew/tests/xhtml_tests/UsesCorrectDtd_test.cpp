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
#include "Validators/Xhtml/UsesCorrectDtd.h"
#include "Result.h"

using namespace FlightCrew;

TEST( UsesCorrectDtdTest, DtdIncorrect )
{
    UsesCorrectDtd validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/xhtml_tests/UsesCorrectDtdTest_DtdIncorrect.xhtml" );
            
    EXPECT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XHTML_BAD_DTD );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 2 );
}

TEST( UsesCorrectDtdTest, DtdIncorrectFarLine )
{
    UsesCorrectDtd validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/xhtml_tests/UsesCorrectDtdTest_DtdIncorrectFarLine.xhtml" );
            
    EXPECT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XHTML_BAD_DTD );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 9 );
}

TEST( UsesCorrectDtdTest, DtdCorrectWithInternal )
{
    UsesCorrectDtd validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/xhtml_tests/UsesCorrectDtdTest_DtdCorrectWithInternal.xhtml" );
    
    EXPECT_EQ( results.size(), 0U );
}

TEST( UsesCorrectDtdTest, DtdCorrect )
{
    UsesCorrectDtd validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/xhtml_tests/UsesCorrectDtdTest_DtdCorrect.xhtml" );
    
    EXPECT_EQ( results.size(), 0U );
}

