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
#ifndef CONSTANTS_H
#define CONSTANTS_H

struct QName;

extern const std::string OPF_XML_NAMESPACE;
extern const std::string DC_XML_NAMESPACE;

extern const QName DC_METADATA_QNAME;
extern const QName X_METADATA_QNAME; 
extern const QName TITLE_QNAME;      
extern const QName LANGUAGE_QNAME;   
extern const QName IDENTIFIER_QNAME; 
extern const QName CREATOR_QNAME;    
extern const QName SUBJECT_QNAME;    
extern const QName DESCRIPTION_QNAME;
extern const QName PUBLISHER_QNAME;  
extern const QName CONTRIBUTOR_QNAME;
extern const QName DATE_QNAME;       
extern const QName TYPE_QNAME;       
extern const QName FORMAT_QNAME;     
extern const QName SOURCE_QNAME;     
extern const QName RELATION_QNAME;   
extern const QName COVERAGE_QNAME;   
extern const QName RIGHTS_QNAME;   
extern const QName META_QNAME;   

#endif // CONSTANTS_H