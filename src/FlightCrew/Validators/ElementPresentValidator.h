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
#ifndef ELEMENTPRESENTVALIDATOR_H
#define ELEMENTPRESENTVALIDATOR_H

#include "XmlValidator.h"
#include <QName.h>

class ElementPresentValidator : public XmlValidator
{

protected:
    
    /**
     * Verifies the presence of the element in the document.
     * We try to report the location of the error as the location
     * of a parent element that is supposed to contain the required element.
     * Since it's possible that the element can be a child of several
     * different parent types, a list is provided. The first parent 
     * present is reported as the location of the error.
     *
     * @param element_qname The name of the element whose presence we want to check.
     * @param possible_parents A list of possible parent names.
     * @param document The document being validated.
     * @return A list of validation results.
     */
    std::vector<Result> VerifyElementPresent( const QName &element_qname,
                                              const std::vector< QName > &possible_parents,
                                              const xc::DOMDocument &document );
};

#endif // ELEMENTPRESENTVALIDATOR_H