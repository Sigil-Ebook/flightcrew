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
#include "Validators/Opf/TitlePresent.h"
#include "Result.h"

TEST( TitlePresentTest, FailsWithNoTitle )
{
    TitlePresent validator;
    Result result = validator.ValidateFile( "test_data/TitlePresent_NoTitle.xml" );

    EXPECT_EQ( result.ErrorId, Result::ERROR_OPF_NO_TITLE );
}

TEST( TitlePresentTest, SucceedsWithTitle )
{
    TitlePresent validator;
    Result result = validator.ValidateFile( "test_data/TitlePresent_HasTitle.xml" );

    EXPECT_EQ( result.ErrorId, Result::ALL_OK );
}