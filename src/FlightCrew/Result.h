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

#pragma once
#ifndef RESULT_H
#define RESULT_H

#include <NodeLocationInfo.h>
#include "ErrorIDs.h"


class Result
{
public:

    Result( ErrorId error_id = ALL_OK,
            XercesExt::NodeLocationInfo node_location = XercesExt::NodeLocationInfo() );

    ErrorId GetErrorId();

    void SetErrorId( ErrorId error_id );

    int GetErrorLine();

    void SetErrorLine( int error_line );

    int GetErrorColumn();

    void SetErrorColumn( int error_column );

private:

    ///////////////////////////////
    // PRIVATE MEMBER VARIABLES
    ///////////////////////////////

    ErrorId m_ErrorId;
    int m_ErrorLine;
    int m_ErrorColumn;
};

#endif // RESULT_H
