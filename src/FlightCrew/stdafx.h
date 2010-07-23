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

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/bind/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>
#include <boost/format.hpp> 
#include <boost/foreach.hpp> 
//#include "constants.h"
//#include "exception.h"

// We're most definitely not going to use
// it as BOOST_FOREACH.
#define foreach BOOST_FOREACH

// We will be using these everywhere,
// so let's make life a bit easier.
using boost::tuple;
using boost::make_tuple;
using boost::tie;
namespace fs = boost::filesystem;

namespace xc = XERCES_CPP_NAMESPACE;
namespace XercesExt {};
namespace xe = XercesExt;
