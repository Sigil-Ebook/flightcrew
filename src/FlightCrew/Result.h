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

struct Result
{
    enum ErrorIds
    {
        ALL_OK = 100,
        ERROR_GENERIC,
        ERROR_XML,
        ERROR_OPF_NO_TITLE
    };

    Result() : ErrorId( ALL_OK ), ErrorLine( -1 ), ErrorColumn( -1 )  {}

    Result( int error_id ) : ErrorId( error_id ), ErrorLine( -1 ), ErrorColumn( -1 )  {}

    int ErrorId;
    int ErrorLine;
    int ErrorColumn;
};
