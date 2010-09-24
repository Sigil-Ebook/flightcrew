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
#include "ItemLinearValid.h"
#include <ToXercesStringConverter.h>
#include <FromXercesStringConverter.h>
#include <XmlUtils.h>

namespace FlightCrew
{

std::vector<Result> ItemLinearValid::ValidateXml(
    const xc::DOMDocument &document,
    const fs::path& )
{
    std::vector< xc::DOMElement* > items = xe::GetElementsByQName( 
        document, QName( "item", OPF_XML_NAMESPACE ) );

    std::vector<Result> results;

    foreach( xc::DOMElement* item, items )
    {
        std::string linear = fromX( item->getAttribute( toX( "linear" ) ) );

        if ( !linear.empty() && linear != "yes" && linear != "no" )
        {
            results.push_back( 
                ResultWithNodeLocation( ERROR_OPF_BAD_ITEM_LINEAR_VALUE, *item )
                .AddMessageArgument( linear )  );
        }       
    }

    return results;
}

} // namespace FlightCrew

