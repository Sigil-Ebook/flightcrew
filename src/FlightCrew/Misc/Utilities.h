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
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <algorithm>
#include "Misc/BoostFilesystemUse.h"

namespace FlightCrew
{

namespace Util
{
    std::string ReadUnicodFile( const fs::path &filepath );

    std::string GetFirstNumChars( const std::string &string, unsigned int num_chars );

    template <typename T>
    bool Contains( const std::vector<T> &vector, const T &value )
    {
        return std::find( vector.begin(), vector.end(), value ) != vector.end(); 
    }

    template <typename T>
    std::vector<T>& Extend( std::vector<T> &base_vector, const std::vector <T> &extension_vector ) 
    {
            base_vector.insert( base_vector.end(), extension_vector.begin(), extension_vector.end() );
            return base_vector;
    }

    template <typename T>
    std::vector<T>& SortedInPlace( std::vector<T> &vector ) 
    {
        std::sort( vector.begin(), vector.end() );
        return vector;
    }

} // namespace Util

} // namespace FlightCrew

#endif // UTILITIES_H
