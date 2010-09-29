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
#include "Validators/Opf/ReachabilityAnalysis.h"
#include "Result.h"

using namespace FlightCrew;

TEST( ReachabilityAnalysisTest, ReachableDocsNotInSpine )
{
    ReachabilityAnalysis validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ReachabilityAnalysis_ReachableDocsNotInSpine/content.opf" );

    // Needed for checking filepaths,
    // ReachabilityAnalysis uses hashes
    std::sort( results.begin(), results.end() );
            
    ASSERT_EQ( results.size(), 3U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_REACHABLE_OPS_DOC_NOT_IN_SPINE );
    EXPECT_TRUE( boost::contains( results[ 0 ].GetFilepath(), "test2.xhtml" ) );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_REACHABLE_OPS_DOC_NOT_IN_SPINE );
    EXPECT_TRUE( boost::contains( results[ 1 ].GetFilepath(), "test3.xhtml" ) );

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_OPF_REACHABLE_OPS_DOC_NOT_IN_SPINE );
    EXPECT_TRUE( boost::contains( results[ 2 ].GetFilepath(), "test4.xhtml" ) );
}

TEST( ReachabilityAnalysisTest, ManifestResourceNotReachable )
{
    ReachabilityAnalysis validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ReachabilityAnalysis_ManifestResourceNotReachable/content.opf" );

    // Needed for checking filepaths,
    // ReachabilityAnalysis uses hashes
    std::sort( results.begin(), results.end() );
            
    ASSERT_EQ( results.size(), 2U );
    EXPECT_EQ( results[ 0 ].GetResultId(), WARNING_OPF_RESOURCE_IN_MANIFEST_NOT_REACHABLE );
    EXPECT_TRUE( boost::contains( results[ 0 ].GetFilepath(), ".xhtml" ) );

    EXPECT_EQ( results[ 1 ].GetResultId(), WARNING_OPF_RESOURCE_IN_MANIFEST_NOT_REACHABLE );
    EXPECT_TRUE( boost::contains( results[ 1 ].GetFilepath(), "doesNotExist.jpg" ) );
}

TEST( ReachabilityAnalysisTest, ReachableResourceNotInManifest )
{
    ReachabilityAnalysis validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ReachabilityAnalysis_ReachableResourceNotInManifest/content.opf" );

    // Needed for checking filepaths,
    // ReachabilityAnalysis uses hashes
    std::sort( results.begin(), results.end() );
            
    ASSERT_EQ( results.size(), 4U );
    EXPECT_EQ( results[ 0 ].GetResultId(), ERROR_OPF_REACHABLE_RESOURCE_NOT_IN_MANIFEST );
    EXPECT_TRUE( boost::contains( results[ 0 ].GetFilepath(), "notInManifest.css" ) );

    EXPECT_EQ( results[ 1 ].GetResultId(), ERROR_OPF_REACHABLE_RESOURCE_NOT_IN_MANIFEST );
    EXPECT_TRUE( boost::contains( results[ 1 ].GetFilepath(), "notInManifest.gif" ) );

    EXPECT_EQ( results[ 2 ].GetResultId(), ERROR_OPF_REACHABLE_OPS_DOC_NOT_IN_SPINE );
    EXPECT_TRUE( boost::contains( results[ 2 ].GetFilepath(), "test4.xhtml" ) );

    EXPECT_EQ( results[ 3 ].GetResultId(), ERROR_OPF_REACHABLE_RESOURCE_NOT_IN_MANIFEST );
    EXPECT_TRUE( boost::contains( results[ 3 ].GetFilepath(), "test4.xhtml" ) );
}


TEST( ReachabilityAnalysisTest, AllOk )
{
    ReachabilityAnalysis validator;
    std::vector<Result> results = validator.ValidateFile(
            "test_data/opf_tests/ReachabilityAnalysis_AllOk/content.opf" );
    
    EXPECT_EQ( results.size(), 0U );
}

