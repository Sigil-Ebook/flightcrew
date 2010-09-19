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
#include "Validators/Xml/UsesUnicode.h"
#include "Result.h"

using namespace FlightCrew;

TEST( UsesUnicodeTest, FileDoesntExist )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/ohutoeuoeueudtneodutont.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), UNABLE_TO_PERFORM_VALIDATION );
}

TEST( UsesUnicodeTest, DeclaresOtherUsesOther )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_DeclaresOtherUsesOther.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_SPECIFIES_NEITHER_UTF8_NOR_UTF16 );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 1 );
}

TEST( UsesUnicodeTest, DeclaresUtf8UsesOther )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_DeclaresUtf8UsesOther.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_BYTESTREAM_NEITHER_UTF8_NOR_UTF16 );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 1 );
}

TEST( UsesUnicodeTest, DeclaresUtf16UsesOther )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_DeclaresUtf16UsesOther.xml" );

    ASSERT_EQ( results.size(), 1U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_XML_BYTESTREAM_NEITHER_UTF8_NOR_UTF16 );
    EXPECT_EQ( results[ 0 ].GetErrorLine(), 1 );
}

TEST( UsesUnicodeTest, ValidUtf8 )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_ValidUtf8.xml" );

    ASSERT_EQ( results.size(), 0U );
}

TEST( UsesUnicodeTest, ValidUtf8lowercase )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_ValidUtf8lowercase.xml" );

    ASSERT_EQ( results.size(), 0U );
}

TEST( UsesUnicodeTest, ValidUtf8implicit )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_ValidUtf8implicit.xml" );

    ASSERT_EQ( results.size(), 0U );
}

TEST( UsesUnicodeTest, ValidUtf16LE )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_ValidUtf16LE.xml" );

    ASSERT_EQ( results.size(), 0U );
}

TEST( UsesUnicodeTest, ValidUtf16BE )
{
    UsesUnicode validator;
    std::vector<Result> results = validator.ValidateFile(
        "test_data/xml_tests/UsesUnicode_ValidUtf16BE.xml" );

    ASSERT_EQ( results.size(), 0U );
}
