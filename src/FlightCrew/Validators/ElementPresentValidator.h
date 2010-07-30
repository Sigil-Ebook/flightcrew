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
#ifndef ELEMENTPRESENTNVALIDATOR_H
#define ELEMENTPRESENTNVALIDATOR_H

#include "XmlValidator.h"

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
     * @param element_name The name of the element whose presence we want to check.
     * @param possible_parents A list of possible parent names.
     * @param document The document being validated.
     * @return A list of validation results.
     */
    std::vector<Result> VerifyElementPresent( const std::string &element_name,
                                              const std::vector< std::string > &possible_parents,
                                              const xc::DOMDocument &document );

private:

    /**
     * From the provided list of element names, returns the first element
     * present in the document.
     *
     * @param node_names The list of element names to search for.
     * @param document The parent DOM document.
     * @return The first element matching one of the provided names
     *         or NULL if none were found.
     */
    xc::DOMNode* GetFirstAvailableElement( const std::vector< std::string > &element_names,
                                           const xc::DOMDocument &document );
};

#endif // ELEMENTPRESENTNVALIDATOR_H