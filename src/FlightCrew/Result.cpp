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
#include "Result.h"
#include "ErrorMessages.h"

namespace FlightCrew
{

Result::Result( ResultId result_id, xe::NodeLocationInfo node_location )
    :
    m_ResultId( result_id ),
    m_ErrorLine( node_location.LineNumber ),
    m_ErrorColumn( node_location.ColumnNumber )
{

}


ResultId Result::GetResultId()
{
    return m_ResultId;
}


Result& Result::SetResultId( ResultId result_id )
{
    m_ResultId = result_id;
    return *this;
}


int Result::GetErrorLine()
{
    return m_ErrorLine;
}


Result& Result::SetErrorLine( int error_line )
{
    m_ErrorLine = error_line;
    return *this;
}


int Result::GetErrorColumn()
{
    return m_ErrorColumn;
}


Result& Result::SetErrorColumn( int error_line )
{
    m_ErrorColumn = error_line;
    return *this;
}


Result& Result::AddMessageArgument( const std::string &message_argument )
{
    m_MessageArguments.push_back( message_argument );
    return *this;
}


Result& Result::SetMessageArguments( const std::vector< std::string > &message_arguments )
{
    m_MessageArguments = message_arguments;
    return *this;
}


const std::vector< std::string > & Result::GetMessageArguments()
{
    return m_MessageArguments;
}


std::string Result::GetErrorMessage()
{
    if ( !m_CustomMessage.empty() )

        return m_CustomMessage;

    boost::format formatter( ErrorMessages::Instance().MessageForId( m_ResultId ) );

    foreach( std::string argument, m_MessageArguments )
    {
        formatter % argument;
    }

    return formatter.str();
}


Result& Result::SetCustomMessage( const std::string &custom_message )
{
    m_CustomMessage = custom_message;
    return *this;
}

} // namespace FlightCrew


