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

#include "Result.h"

Result::Result()
    :
    m_ErrorId( ALL_OK ),
    m_ErrorLine( -1 ),
    m_ErrorColumn( -1 )
{

}

Result::Result( ErrorId error_id )
    :
    m_ErrorId( error_id ),
    m_ErrorLine( -1 ),
    m_ErrorColumn( -1 )
{

}


ErrorId Result::GetErrorId()
{
    return m_ErrorId;
}


void Result::SetErrorId( ErrorId error_id )
{
    m_ErrorId = error_id;
}


int Result::GetErrorLine()
{
    return m_ErrorLine;
}


void Result::SetErrorLine( int error_line )
{
    m_ErrorLine = error_line;
}


int Result::GetErrorColumn()
{
    return m_ErrorColumn;
}


void Result::SetErrorColumn( int error_line )
{
    m_ErrorColumn = error_line;
}
