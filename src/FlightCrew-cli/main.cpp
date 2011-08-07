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

#include <iostream>
#include <flightcrew.h>
namespace fc = FlightCrew;

// We set the MSVC warning level down to 3
// for code that we have no control over
#if defined(_MSC_VER)
#   pragma warning( push, 3 )
#endif

#include <boost/foreach.hpp> 
// We're most definitely not going to use
// it as BOOST_FOREACH.
#define foreach BOOST_FOREACH

#include <boost/program_options.hpp>
namespace po = boost::program_options;

// ... and then we reset the warning level
// back to normal (warning level 4)
#if defined(_MSC_VER)
#   pragma warning( pop )
#endif

static const std::string FLIGHTCREW_VERSION = FLIGHTCREW_FULL_VERSION;

bool ValidateFiles( const std::vector< std::string > &files_to_validate )
{
    bool seen_problems = false;

    foreach( const std::string &file, files_to_validate )
    {
        std::vector< fc::Result > results;

        try
        {
            results = fc::ValidateEpub( file );
        }

        catch ( fc::FileDoesNotExistEx& )
        {
            std::cerr << "File " << file << " does not exist.\n\n";
            continue;
        }

        foreach( const fc::Result &result, results )
        {
            seen_problems = true;            
            std::cerr << result.GetFilepath();

            if ( result.GetErrorLine() > 0 )
                
                std::cerr << "(" << result.GetErrorLine() << ")";

            std::cerr << ": ";

            if ( result.GetResultType() == fc::ResultType_ERROR )

                std::cerr << "error ";

            else 

                std::cerr << "warning ";

            std::cerr << result.GetResultId() << ": ";
            std::cerr << result.GetMessage() << "\n";   
        }

        if ( !results.empty() )
        
            std::cerr << "\n";
    }

    return seen_problems;
}


int main( int argc, char *argv[] )
{
    try 
    {
        po::options_description options( "Allowed options" );
        options.add_options()
            ( "help", "produce help message" )
            ( "version", "show the program version")
            ( "input-file", po::value< std::vector< std::string > >(), "input file" );

        po::positional_options_description positionals;
        // -1 for count means unlimited
        positionals.add( "input-file", -1 );

        po::variables_map var_map;       
        store( po::command_line_parser( argc, argv ).
               options( options ).positional( positionals ).run(), var_map );
        po::notify( var_map );    

        if ( var_map.count( "help" ) )
        {
            std::cout << "Usage: flightcrew-cli [options] file...\n";
            std::cout << options << "\n";
            return 1;
        }

        if ( var_map.count( "version" ) )
        {
            std::cout << "flightcrew-cli version: " << FLIGHTCREW_VERSION <<  " " << "\n";
            return 1;
        }

        if ( var_map.count( "input-file" ) ) 
        {
            std::vector< std::string > files_to_validate =
                var_map[ "input-file" ].as< std::vector< std::string > >();

            bool problems_found = ValidateFiles( files_to_validate );
            if ( !problems_found )

                std::cout << "No problems found.\n";

            return problems_found;
        } 
        
        else
        {
            std::cout << "No input file specified. Use --help for usage information.\n";
        }
    }

    catch ( std::exception& exception )
    {
        std::cerr << "Error during run: " << exception.what() << "\n";
        return 1;
    }

    catch ( ... ) 
    {
        std::cerr << "Unknown exception!\n";
        return 1;
    }

    return 0;
}
