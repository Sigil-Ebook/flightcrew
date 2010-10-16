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
#include "flightcrew.h"
#include "Result.h"

using namespace FlightCrew;

// This is basically a sanity check 
TEST( EpubValidatesTest, MissingCreator )
{
    std::vector<Result> results = ValidateEpub(
        "test_data/framework_tests/EpubValidates_MissingTitle.epub" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_ELEMENT_NOT_PRESENT );

    std::vector< std::string > message_arguments = results[ 0 ].GetMessageArguments();
    EXPECT_EQ( message_arguments[ 0 ], "title" );
}

TEST( EpubValidatesTest, ResultsWithBasePath )
{
    std::vector<Result> results = ValidateEpub(
        "test_data/framework_tests/EpubValidates_MissingTitle.epub" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetFilepath(), "EpubValidates_MissingTitle.epub/OEBPS/content.opf" );
}

TEST( EpubValidatesTest, NotAZip )
{
    std::vector<Result> results = ValidateEpub(
        "test_data/framework_tests/EpubValidates_NotAZip.epub" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_EPUB_NOT_VALID_ZIP_ARCHIVE );
}

TEST( EpubValidatesTest, NoContainerXml )
{
    std::vector<Result> results = ValidateEpub(
        "test_data/framework_tests/EpubValidates_NoContainerXml.epub" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_EPUB_NO_CONTAINER_XML );
}

TEST( EpubValidatesTest, MissingXhtmlFiles )
{
    ASSERT_NO_THROW( ValidateEpub(
        "test_data/framework_tests/EpubValidates_MissingXhtmlFiles.epub" ) );
}

TEST( EpubValidatesTest, Valid )
{
    std::vector<Result> results = ValidateEpub(
        "test_data/framework_tests/EpubValidates_Valid.epub" );

    ASSERT_EQ( results.size(), 0U );    
}
