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

#include "zipios++/zipios-config.h"

#include "zipios++/meta-iostreams.h"
#include <memory>
#include <stdlib.h>
#include <boost/scoped_ptr.hpp>

#include "zipios++/zipfile.h"
#include "zipios++/zipinputstream.h"

#include "zipios++/zipextraction.h"
#include "zipios++/fcollexceptions.h"

namespace zipios 
{


void WriteEntryToFile( const std::istream &stream, const fs::path &filepath )
{
    fs::ofstream ofs( filepath, ios::out | ios::binary );
    ofs << stream.rdbuf();
    ofs.close();
}


void CreateFilepath( const fs::path &filepath )
{
    if ( filepath.empty() )

        throw IOException();

    if ( !fs::exists( filepath.parent_path() ) )

        fs::create_directories( filepath.parent_path() );

    if ( fs::is_regular_file( filepath ) )
    
        fs::ofstream( filepath );

    else if ( fs::is_directory( filepath ) )

        fs::create_directory( filepath );
}


void ExtractZipToFolder( const fs::path &path_to_zip, const fs::path &path_to_folder )
{
    ZipFile zip( path_to_zip );

    ConstEntries entries = zip.entries();
    for ( ConstEntries::iterator it = entries.begin(); it != entries.end(); ++it )
    {
        boost::scoped_ptr< std::istream > stream( zip.getInputStream( *it ) );

        // for security against maliciously crafted epubs
	// we need to force all files extracted from the epub/zip to be safely inside
        // the destination folder and not anyplace else.

        // First remove all illegal backslash characters (escapes) - see Zip spec
        // Next remove any and all upward relative path segments "/../"
        // Finally remove any leading "/" characters to create a safer relative path

	// epubs zips are not general zip archives so symlinks and upward
        // relative path segments need not be supported.

	string azipfilepath = (*it)->getName();
        size_t n = azipfilepath.length();

        // stripping out any backslashes during copy
        bool evil_or_corrupt_epub = false;
	string securefilepath = "/";
	securefilepath.reserve(n+1);
        for (size_t i=0; i < n; i++) {
	  if (azipfilepath[i] != '\\') {
	      securefilepath.append(1, azipfilepath[i]);
	  } else {
	      evil_or_corrupt_epub = true;
	  }
	}
        // now replace all upward path segments "/../" with "/"
        size_t index = securefilepath.find("/../", 0);
        if (index != std::string::npos) evil_or_corrupt_epub = true;
        while(index != std::string::npos) {
	    securefilepath.replace(index, 4,"/");
	    index = securefilepath.find("/../", index);
	}
        // finally remove any leading "/"
        securefilepath.erase(0,securefilepath.find_first_not_of("/"));

	if (evil_or_corrupt_epub) {
	    throw InvalidStateException( "evil or corrupt epub detected with local file path: " + azipfilepath ) ;
	}

        fs::path new_file_path = path_to_folder / securefilepath;

        CreateFilepath( new_file_path );
        WriteEntryToFile( *stream, new_file_path );
    }
}


} // namespace zipios
