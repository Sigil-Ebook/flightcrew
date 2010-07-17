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

#include <stdafx.h>
#include "ErrorMessages.h"

boost::mutex ErrorMessages::s_AccessMutex;
ErrorMessages* ErrorMessages::s_Instance = NULL;

ErrorMessages& ErrorMessages::Instance()
{
    // We use a static local variable
    // to hold our singleton instance; using a pointer member
    // variable creates problems with object destruction;

    boost::lock_guard< boost::mutex > locker( s_AccessMutex );

    if ( !s_Instance )
    {
        static ErrorMessages messages;
        s_Instance = &messages;
    }

    return *s_Instance;
}


const std::string ErrorMessages::MessageForId( ErrorId error_id )
{
    return std::string();
}


ErrorMessages::ErrorMessages()
{

}
