/************************************************************************
**
**  Copyright (C) 2009, 2010  Strahinja Markovic
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef XERCEHSUSE_H
#define XERCEHSUSE_H

#include <xercesc/util/XercesDefs.hpp>
namespace XERCES_CPP_NAMESPACE 
{
    class DOMNode;
    class DOMAttr;
    class DOMDocument;
    class DOMDocumentFragment;
    class DOMElement;
    class DOMNodeList;    
};
namespace xc = XERCES_CPP_NAMESPACE;

#endif // XERCEHSUSE_H