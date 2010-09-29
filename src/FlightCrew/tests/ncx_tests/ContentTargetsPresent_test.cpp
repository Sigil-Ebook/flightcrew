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
#include "Validators/Ncx/ContentTargetsPresent.h"
#include "Result.h"

using namespace FlightCrew;

TEST( ContentTargetsPresentTest, NotPresent )
{
    ContentTargetsPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/ncx_tests/ContentTargetsPresent_NotPresent/toc.ncx" );
            
    EXPECT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_NCX_CONTENT_FILE_DOES_NOT_EXIST );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 9 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 36 );
    
    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "test1.xhtml" );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_NCX_CONTENT_FRAGMENT_DOES_NOT_EXIST );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 15 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 43 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "test2.xhtml#break1" );
}

TEST( ContentTargetsPresentTest, AllPresent )
{
    ContentTargetsPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/ncx_tests/ContentTargetsPresent_AllPresent/toc.ncx" );
    
    EXPECT_EQ( results.size(), 0U );
}

