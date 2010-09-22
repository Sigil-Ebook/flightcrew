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
#ifndef FLIGHTCREW_H
#define FLIGHTCREW_H

#include <vector>
#include <string>
#include "DllExporting.h"
#include "Result.h"

namespace FlightCrew
{

FC_WIN_DLL_API std::vector< Result > ValidateEpub(  const std::string &absolute_path );

FC_WIN_DLL_API std::vector< Result > ValidateOpf(   const std::string &absolute_path );

FC_WIN_DLL_API std::vector< Result > ValidateNcx(   const std::string &absolute_path );

FC_WIN_DLL_API std::vector< Result > ValidateXhtml( const std::string &absolute_path );

FC_WIN_DLL_API std::vector< Result > ValidateCss(   const std::string &absolute_path );

} // namespace FlightCrew

#endif // FLIGHTCREW_H
