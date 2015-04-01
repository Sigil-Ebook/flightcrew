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

// We set the MSVC warning level down to 3
// for code that we have no control over
#if defined(_MSC_VER)
#   pragma warning( push, 3 )
#endif

#include <QCoreApplication>
#include <QtWidgets/QApplication>
#include <QMessageBox>

// Needs to go here because of Qt includes for some reason
#include "MainWindow.h"
#include "UpdateChecker.h"

// ... and then we reset the warning level
// back to normal (warning level 4)
#if defined(_MSC_VER)
#   pragma warning( pop )
#endif


// Application entry point
int main( int argc, char *argv[] )
{
    QT_REQUIRE_VERSION( argc, argv, "4.6.0" );
    
    QApplication app( argc, argv ); 

    // Set application information for
    // easier use of QSettings classes
    QCoreApplication::setOrganizationName( "Sigil" );
    QCoreApplication::setApplicationName( "FlightCrew-gui" );

    // Needs to be created on the heap so that
    // the reply has time to return.
    UpdateChecker *checker = new UpdateChecker( &app );
    checker->CheckForUpdate();

    MainWindow *widget = new MainWindow();    
    widget->show();
    return app.exec();
}





