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

#include <gtest/gtest.h>
#include "Validators/Opf/OneMetadata.h"
#include "Result.h"

TEST( OneMetadataTest, NoMetadata_Error )
{
    OneMetadata validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneMetadata_NoMetadata.xml" );

    EXPECT_EQ( results[ 0 ].GetErrorId(), ERROR_OPF_WRONG_METADATA_COUNT );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 2 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 88 );
}

TEST( OneMetadataTest, TwoMetadatas_Error )
{
    OneMetadata validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneMetadata_TwoMetadatas.xml" );

    EXPECT_EQ( results[ 0 ].GetErrorId(), ERROR_OPF_WRONG_METADATA_COUNT );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 5 );
    EXPECT_EQ( results[ 0 ].GetErrorColumn(), 11 );
}

TEST( OneMetadataTest, OneMetadata_OK )
{
    OneMetadata validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/OneMetadata_OneMetadata.xml" );

    EXPECT_EQ( results[ 0 ].GetErrorId(), ALL_OK );
}

