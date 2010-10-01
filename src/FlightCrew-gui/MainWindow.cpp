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

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QComboBox>
#include <QTableWidgetItem>
#include <QBrush>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include "MainWindow.h"
#include <flightcrew.h>
namespace fc = FlightCrew;

static const QString SETTINGS_GROUP = "mainwindow";
static const QBrush WARNING_BRUSH = QBrush( QColor( 255, 255, 230 ) );
static const QBrush ERROR_BRUSH   = QBrush( QColor( 255, 230, 230 ) );

MainWindow::MainWindow( QWidget*, Qt::WFlags )
{
    ui.setupUi( this );
    
    // Telling Qt to delete this window
    // from memory when it is closed
    setAttribute( Qt::WA_DeleteOnClose );
    setAcceptDrops( true );

    ui.FilepathsCombo->setInsertPolicy( QComboBox::InsertAtCurrent );
    ui.ResultTable->setColumnCount( 3 );
    ui.ResultTable->setHorizontalHeaderLabels( 
        QStringList() << tr( "File" ) << tr( "Line" ) << tr( "Message" ) );
    ui.ResultTable->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );

    // Needs to come before signals connect
    // (avoiding side-effects)
    ReadSettings();
    ConnectSignalsToSlots();
}


MainWindow::~MainWindow()
{
    WriteSettings();
}


void MainWindow::dragEnterEvent( QDragEnterEvent *event )
{
    if ( event->mimeData()->hasFormat( "text/uri-list" ) )

        event->acceptProposedAction();
}


void MainWindow::dropEvent( QDropEvent *event )
{
    if ( !event->mimeData()->hasUrls() )

        return;

    event->acceptProposedAction();

    QList< QUrl > urls = event->mimeData()->urls();

    if ( urls.empty() )

        return;

    AddFilenameToComboBox( urls[ 0 ].toLocalFile() );
    StartValidation();
}


void MainWindow::StartValidation()
{
    QString current_file = ui.FilepathsCombo->currentText();

    if ( QFileInfo( current_file ).suffix().toLower() != "epub" )
    {
        QMessageBox::critical( this,
                               tr( "FlightCrew-gui" ),
                               tr( "The specified file does not appear to be an epub." )
                              );
        return;
    }

    if ( !QFileInfo( current_file ).exists() )
    {
        QMessageBox::critical( this,
                               tr( "FlightCrew-gui" ),
                               tr( "The specified file does not exist." )
                              );
        return;
    }

    ClearTable();
    std::vector< fc::Result > results;

    QApplication::setOverrideCursor( Qt::WaitCursor );

    try
    {
        results = fc::ValidateEpub( current_file.toUtf8().constData() );
    }

    catch ( std::exception& exception )
    {
        QMessageBox::critical( this,
                               tr( "FlightCrew-gui" ),
                               tr( "An exception occurred: %1." )
                               .arg( QString::fromStdString( exception.what() ) )
                              );
        return;
    }

    QApplication::restoreOverrideCursor();

    DisplayResults( results );
}


void MainWindow::BrowseForEpub()
{
    QString filename = QFileDialog::getOpenFileName( this,
                                                     tr( "Open File" ),
                                                     m_LastFolderOpen,
                                                     tr( "Epub files (*.epub)" )
                                                   );

    if ( !filename.isEmpty() )
    {
        // Store the folder the user opened from
        m_LastFolderOpen = QFileInfo( filename ).absolutePath();

        AddFilenameToComboBox( filename );        
    }
}


void MainWindow::DisplayResults( const std::vector< fc::Result > &results )
{
    for ( unsigned int i = 0; i < results.size(); ++i )
    {
        fc::Result result = results[ i ];

        ui.ResultTable->insertRow( ui.ResultTable->rowCount() );

        QBrush row_brush;
        if ( result.GetResultType() == fc::ResultType_WARNING )
        
            row_brush = WARNING_BRUSH;
        else
      
            row_brush = ERROR_BRUSH;

        QTableWidgetItem *item = NULL;
        item = new QTableWidgetItem( QString::fromUtf8( result.GetFilepath().c_str() ) );
        item->setBackground( row_brush );
        ui.ResultTable->setItem( i, 0, item );

        int line = result.GetErrorLine();

        if ( line > 0 )

            item = new QTableWidgetItem( QString::number( result.GetErrorLine() ) );

        else

            item = new QTableWidgetItem( tr( "N/A" ) );

        item->setBackground( row_brush );
        ui.ResultTable->setItem( i, 1, item );

        item = new QTableWidgetItem( QString::fromUtf8( result.GetMessage().c_str() ) );
        item->setBackground( row_brush );
        ui.ResultTable->setItem( i, 2, item );
    }

    // We first force the line number column 
    // to the smallest needed size...
    ui.ResultTable->resizeColumnToContents( 0 );

    // ... and now the file column can be widened.
    ui.ResultTable->resizeColumnToContents( 1 );
}

// QTableWidge.clear() also removes the headers
void MainWindow::ClearTable()
{
    while ( ui.ResultTable->rowCount() )
    {
        ui.ResultTable->removeRow( 0 );
    }

    ui.ResultTable->update();

    // Needed so that the table is repainted
    qApp->processEvents();
}


void MainWindow::AddFilenameToComboBox( const QString &filename )
{
    int index = ui.FilepathsCombo->findText( filename );

    if ( index == -1 )            
    {
        ui.FilepathsCombo->insertItem( 0, filename );
        ui.FilepathsCombo->setCurrentIndex( 0 );
    }

    else
    {
        ui.FilepathsCombo->setCurrentIndex( index );
    }
}


void MainWindow::ReadSettings()
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    // The size of the window and it's full screen status
    QByteArray geometry = settings.value( "geometry" ).toByteArray();

    if ( !geometry.isNull() )

        restoreGeometry( geometry );

    ui.FilepathsCombo->addItems( settings.value( "path_strings" ).toStringList() );
    m_LastFolderOpen = settings.value( "lastfolderopen"  ).toString();
}


void MainWindow::WriteSettings()
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    // The size of the window and it's full screen status
    settings.setValue( "geometry", saveGeometry() );

    QStringList path_strings;

    for ( int i = 0; i < ui.FilepathsCombo->count(); ++i )
    {
        path_strings.append( ui.FilepathsCombo->itemText( i ) );
    }

    settings.setValue( "path_strings", path_strings );
    settings.setValue( "lastfolderopen", m_LastFolderOpen );
}


void MainWindow::ConnectSignalsToSlots()
{
    connect( ui.actionExit,   SIGNAL( triggered() ), qApp, SLOT( closeAllWindows() ) );
    connect( ui.GoButton,     SIGNAL( clicked()   ), this, SLOT( StartValidation() ) );
    connect( ui.BrowseButton, SIGNAL( clicked()   ), this, SLOT( BrowseForEpub()   ) );
}



