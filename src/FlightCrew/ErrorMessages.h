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
#ifndef ERRORMESSAGES_H
#define ERRORMESSAGES_H

#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/unordered_map.hpp>
#include "ErrorIDs.h"

class ErrorMessages
{
public:

    static ErrorMessages& Instance();

    const std::string MessageForId( ErrorId error_id );

private:

    ErrorMessages();

    void LoadMessages();

    ///////////////////////////////
    // PRIVATE MEMBER VARIABLES
    ///////////////////////////////

    static boost::mutex s_AccessMutex;

    static ErrorMessages *s_Instance;

    boost::unordered_map< ErrorId, std::string > m_Messages;
};

#endif // ERRORMESSAGES_H
