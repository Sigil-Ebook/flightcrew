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
#include "Validators/Opf/ItemMediaTypeValid.h"
#include "Result.h"

namespace FlightCrew
{

extern const std::string XHTML_MIME; 
extern const std::string OTF_MIME;    

}

using namespace FlightCrew;

TEST( ItemMediaTypeValidTest, BadValue )
{
    ItemMediaTypeValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemMediaTypeValid_BadValue.xml" );
            
    EXPECT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_BAD_ITEM_MEDIA_TYPE_VALUE );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 9 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 86 );
    
    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "break1"   );
    EXPECT_EQ( message_arguments[ 1 ], XHTML_MIME );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_BAD_ITEM_MEDIA_TYPE_VALUE );
    EXPECT_EQ( results[ 1 ].GetErrorLine(), 14 );
    EXPECT_EQ( results[ 1 ].GetErrorColumn(), 87 );

    message_arguments = results[ 1 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "break2" );
    EXPECT_EQ( message_arguments[ 1 ], OTF_MIME );
}

TEST( ItemMediaTypeValidTest, GoodValue )
{
    ItemMediaTypeValid validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ItemMediaTypeValid_GoodValue.xml" );
    
    EXPECT_EQ( results.size(), 0U );
}

