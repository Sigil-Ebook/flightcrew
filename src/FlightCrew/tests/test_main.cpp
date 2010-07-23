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
#include <iostream>
#include <gmock/gmock.h>
#include <xercesc/util/PlatformUtils.hpp>

namespace xc = XERCES_CPP_NAMESPACE;

// MS C++ compiler/linker has a bug on Windows (not on Windows CE), which
// causes a link error when _tmain is defined in a static library and UNICODE
// is enabled. For this reason instead of _tmain, main function is used on
// Windows. See the following link to track the current status of this bug:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=394464 
#if GTEST_OS_WINDOWS_MOBILE
#include <tchar.h> 

int _tmain(int argc, TCHAR** argv)
{
#else
int main(int argc, char** argv) 
{
#endif  // GTEST_OS_WINDOWS_MOBILE
    std::cout << "Running main() from test_main.cpp\n";

    xc::XMLPlatformUtils::Initialize();
    
    testing::InitGoogleMock(&argc, argv);    
    int test_run_result = RUN_ALL_TESTS();
    
    xc::XMLPlatformUtils::Terminate();
    
    return test_run_result;
}
