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

void replace_all(std::string &s, const char * s1, const char * s2)
{
  std::string t1(s1);
  size_t len = t1.length();
  size_t pos = s.find(t1);
  while (pos != std::string::npos) {
    s.replace(pos, len, s2);
    pos = s.find(t1, pos + len);
  }
}

std::string substitute_xml_entities(const std::string &text)
{
  std::string result = text;
  // replacing & must come first 
  replace_all(result, "&", "&amp;");
  replace_all(result, "<", "&lt;");
  replace_all(result, ">", "&gt;");
  return result;
}

static const std::string FLIGHTCREW_VERSION = FLIGHTCREW_FULL_VERSION;

bool ValidateFiles( const std::string  &folder_path )
{
    bool seen_problems = false;
    std::vector< fc::Result > results;

    try
    {
        results = fc::ValidateEpubRootFolder( folder_path );
    }

    catch ( fc::FileDoesNotExistEx& )
    {
        std::cerr << "Folder " << folder_path << " does not exist.\n\n";
        return true;
    }

    foreach( const fc::Result &result, results )
    {
        seen_problems = true;

        std::cerr << "<problem>\n";

        if ( result.GetResultType() == fc::ResultType_ERROR )
            std::cerr << "  <type>error</type>\n";
        else 
            std::cerr << "  <type>warning</type>\n";

        std::string fp = result.GetFilepath();
        fp = substitute_xml_entities(fp);
        std::cerr << "  <filepath>" << fp << "</filepath>\n";

        if ( result.GetErrorLine() > 0 ) {
            std::cerr << "  <line>" << result.GetErrorLine() << "</line>\n";
        } else {
            std::cerr << "  <line></line>\n";
        }

        if ( result.GetErrorColumn() > 0 ) {
            std::cerr << "  <column>" << result.GetErrorColumn() << "</column>\n";
        } else {
            std::cerr << "  <column></column>\n";
        }

        std::cerr << "  <resultid>" << result.GetResultId() << "</resultid>\n";

        std::string msg = result.GetMessage();
        msg = substitute_xml_entities(msg);
        std::cerr << "  <msg>" << msg << "</msg>\n";   

        std::cerr << "</problem>\n";
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
            ( "root-path", po::value< std::string >(), "root-path" );

        po::positional_options_description positionals;
        // -1 for count means unlimited
        positionals.add( "root-path", 1 );

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

        if ( var_map.count( "root-path" ) ) 
        {
            std::string root_path_to_validate =
                var_map[ "root-path" ].as< std::string >();

            bool problems_found = ValidateFiles( root_path_to_validate );
            if ( !problems_found )

                std::cout << "No problems found.\n";

            return problems_found;
        } 
        
        else
        {
            std::cout << "No path to unzipped epub root specified. Use --help for usage information.\n";
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
