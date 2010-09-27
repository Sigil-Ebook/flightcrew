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

#include <stdafx_tests.h>
#include "Misc/DetermineMimetype.h"

namespace FlightCrew
{

extern const std::string OEBPS_MIME;  
extern const std::string XHTML_MIME; 
extern const std::string NCX_MIME;    
extern const std::string PNG_MIME;    
extern const std::string GIF_MIME;  
extern const std::string JPEG_MIME;   
extern const std::string SVG_MIME;    
extern const std::string DTBOOK_MIME; 
extern const std::string CSS_MIME;    
extern const std::string XML_MIME;    
extern const std::string XPGT_MIME;   
extern const std::string OTF_MIME;    
extern const std::string TTF_MIME;    
extern const std::string OEB_DOC_MIME;
extern const std::string OEB_CSS_MIME;

extern const std::string UNKNOWN_MIME;

}

using namespace FlightCrew;

TEST( DetermineMimetypeTest, ExtensionChecks )
{
    EXPECT_EQ( DetermineMimetype( "test.xhtml" ), XHTML_MIME );
    EXPECT_EQ( DetermineMimetype( "test.html"  ), XHTML_MIME );
    EXPECT_EQ( DetermineMimetype( "test.htm"   ), XHTML_MIME );
    EXPECT_EQ( DetermineMimetype( "test.png"   ), PNG_MIME   );
    EXPECT_EQ( DetermineMimetype( "test.gif"   ), GIF_MIME   );
    EXPECT_EQ( DetermineMimetype( "test.jpg"   ), JPEG_MIME  );
    EXPECT_EQ( DetermineMimetype( "test.jpeg"  ), JPEG_MIME  );
    EXPECT_EQ( DetermineMimetype( "test.css"   ), CSS_MIME   );
    EXPECT_EQ( DetermineMimetype( "test.ncx"   ), NCX_MIME   );
    EXPECT_EQ( DetermineMimetype( "test.svg"   ), SVG_MIME   ); 
    EXPECT_EQ( DetermineMimetype( "test.otf"   ), OTF_MIME   );
    EXPECT_EQ( DetermineMimetype( "test.ttf"   ), TTF_MIME   );
}

TEST( DetermineMimetypeTest, ContentChecks )
{
    // TODO
}
