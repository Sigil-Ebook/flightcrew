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
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <vector>
#include <string>
#include "Result.h"

std::vector< Result > ValidateEpub(  const std::string &absolute_path );

std::vector< Result > ValidateEpub(  const char *absolute_path );

std::vector< Result > ValidateOpf(   const std::string &absolute_path );

std::vector< Result > ValidateOpf(   const char *absolute_path );

std::vector< Result > ValidateNcx(   const std::string &absolute_path );

std::vector< Result > ValidateNcx(   const char *absolute_path );

std::vector< Result > ValidateXhtml( const std::string &absolute_path );

std::vector< Result > ValidateXhtml( const char *absolute_path );

std::vector< Result > ValidateCss(   const std::string &absolute_path );

std::vector< Result > ValidateCss(   const char *absolute_path );
