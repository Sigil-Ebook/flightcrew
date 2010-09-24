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
#include "Validators/Ocf/ContainerListedOpfPresent.h"
#include "Result.h"

using namespace FlightCrew;

TEST( ContainerListedOpfPresentTest, DoesntHaveOpf )
{
    ContainerListedOpfPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/ocf_tests/ContainerListedOpfPresent_DoesntHaveOpf/META-INF/container.xml" );
            
    EXPECT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OCF_CONTAINER_SPECIFIED_OPF_DOESNT_EXIST );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 4 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 89 );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "OEBPS/breakme.opf" );
}

TEST( ContainerListedOpfPresentTest, HasOpf )
{
    ContainerListedOpfPresent validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/ocf_tests/ContainerListedOpfPresent_HasOpf/META-INF/container.xml"  );
    
    EXPECT_EQ( results.size(), 0U );
}

