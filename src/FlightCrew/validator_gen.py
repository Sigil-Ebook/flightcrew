#!/usr/bin/env python

VALIDATOR_NAME = "SpinePresent"
NEW_ERROR      = "ERROR_OPF_NO_SPINE"
NEW_MESSAGE    = "kukulele"

SOURCE_PREFIX    = "Validators/Opf/"
TEST_PREFIX      = "tests/opf_tests/"
TEST_DATA_PREFIX = "tests/test_data/opf_tests/"

license = \
"""/************************************************************************
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
"""

test_content = \
"""
#include <gtest/gtest.h>
#include "Validators/Opf/VALIDATOR_NAME.h"
#include "Result.h"

TEST( VALIDATOR_NAMETest, X_Error )
{
    VALIDATOR_NAME validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/VALIDATOR_NAME_X.xml" );

    EXPECT_EQ( results[ 0 ].GetErrorId(), NEW_ERROR );
}

TEST( VALIDATOR_NAMETest, X_OK )
{
    VALIDATOR_NAME validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/VALIDATOR_NAME_X.xml" );

    EXPECT_EQ( results[ 0 ].GetErrorId(), ALL_OK );
}

"""

validator_cpp = \
"""
#include <stdafx.h>
#include "VALIDATOR_NAME.h"
#include "Result.h"
#include "Misc/ToXercesStringConverter.h"

std::vector<Result> VALIDATOR_NAME::ValidateXml( const DOMDocument &document )
{
    DOMElement *root_element = document.getDocumentElement();
    DOMNodeList *title_elements = root_element->getElementsByTagNameNS(
                                    X( "*" ),  X( "title" ) );

    std::vector<Result> results;

    if ( title_elements->getLength() < 1 )

        results.push_back( Result( NEW_ERROR ) );

    else

        results.push_back( Result() );

    return results;
}

"""

validator_h = \
"""
#pragma once
#ifndef VALIDATOR_UPNAME_H
#define VALIDATOR_UPNAME_H

#include "../XmlValidator.h"

class VALIDATOR_NAME : public XmlValidator
{
public:

    virtual std::vector<Result> ValidateXml( const DOMDocument &document );
};

#endif // VALIDATOR_UPNAME_H
"""

xml_file = \
"""<?xml version="1.0" encoding="UTF-8"?>
<package version="2.0" xmlns="http://www.idpf.org/2007/opf" unique-identifier="BookId">
</package>
"""

filename = VALIDATOR_NAME + ".cpp"
content = ( license + validator_cpp ).replace( "VALIDATOR_NAME", VALIDATOR_NAME ).replace( "NEW_ERROR", NEW_ERROR )

import os
import sys
if os.path.exists( filename ):
    print "File exists!"
    sys.exit( 1 )

open( SOURCE_PREFIX + filename, "w" ).writelines( content )

filename = VALIDATOR_NAME + ".h"
content = ( license + validator_h ).replace( "VALIDATOR_NAME", VALIDATOR_NAME ).replace( 
                                                      "VALIDATOR_UPNAME", VALIDATOR_NAME.upper() )

open( SOURCE_PREFIX + filename, "w" ).writelines( content )

filename = VALIDATOR_NAME + "_test.cpp"
content = ( license + test_content ).replace( "VALIDATOR_NAME", VALIDATOR_NAME ).replace( "NEW_ERROR", NEW_ERROR )

open( TEST_PREFIX + filename, "w" ).writelines( content )

filename = VALIDATOR_NAME + "_X.xml"
content = xml_file

open( TEST_DATA_PREFIX + filename, "w" ).writelines( content )
    
    
    
    
