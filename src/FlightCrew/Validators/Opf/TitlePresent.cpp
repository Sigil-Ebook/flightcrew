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

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "TitlePresent.h"
#include "Result.h"
#include "Misc/ToXercesStringConverter.h"

Result TitlePresent::ValidateXml( const DOMDocument &document )
{
    DOMElement *root_element = document.getDocumentElement();
    DOMNodeList *title_elements = root_element->getElementsByTagNameNS(
                                    X( "*" ),  X( "title" ) );

    if ( title_elements->getLength() < 1 )

        return Result( Result::ERROR_OPF_NO_TITLE );

    return Result();
}