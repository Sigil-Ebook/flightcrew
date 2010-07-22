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

#include <xercesc/util/XMLString.hpp>
#include "FromXercesStringConverter.h"

namespace XercesExt
{
    FromXercesStringConverter::FromXercesStringConverter( const XMLCh* const xerces_string )
    {
        m_LocalString = xc::XMLString::transcode( xerces_string );
    }


    FromXercesStringConverter::~FromXercesStringConverter()
    {
        xc::XMLString::release( &m_LocalString );
    }


    const char* FromXercesStringConverter::LocalString() const
    {
        return m_LocalString;
    }
}
