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
#ifndef RESULT_H
#define RESULT_H

#include <string>
#include <vector>
#include <NodeLocationInfo.h>
#include "ResultId.h"
#include "DllExporting.h"

#if defined(_MSC_VER)
// This warning complains that the private members 
// of this class that use the STL are not being exported
// for use by clients.
// Since the clients can't even access the private members 
// of this class, it's not a problem.
#   pragma warning( disable : 4251 )
#endif

namespace FlightCrew
{

class FC_WIN_DLL_API Result
{
public:

    Result( ResultId result_id = ALL_OK,
            XercesExt::NodeLocationInfo node_location = XercesExt::NodeLocationInfo() );

    ResultId GetResultId();

    Result& SetResultId( ResultId result_id );

    int GetErrorLine();

    Result& SetErrorLine( int error_line );

    int GetErrorColumn();

    Result& SetErrorColumn( int error_column );

    std::string GetFilepath();

    Result& SetFilepath( const std::string &filepath );

    Result& AddMessageArgument( const std::string &message_argument );

    Result& SetMessageArguments( const std::vector< std::string > &message_arguments );

    const std::vector< std::string > &GetMessageArguments();

    std::string GetErrorMessage();

    Result& SetCustomMessage( const std::string &custom_message );
    
    bool operator< ( const Result& other ) const;

private:

    ///////////////////////////////
    // PRIVATE MEMBER VARIABLES
    ///////////////////////////////

    ResultId m_ResultId;

    int m_ErrorLine;

    int m_ErrorColumn;

    std::vector< std::string > m_MessageArguments;

    std::string m_CustomMessage;

    std::string m_Filepath;
};

} // namespace FlightCrew

#endif // RESULT_H
