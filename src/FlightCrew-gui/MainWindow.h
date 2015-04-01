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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// We set the MSVC warning level down to 3
// for code that we have no control over
#if defined(_MSC_VER)
#   pragma warning( push, 3 )
#endif

#include <QMainWindow>
#include "ui_Form.h"

// ... and then we reset the warning level
// back to normal (warning level 4)
#if defined(_MSC_VER)
#   pragma warning( pop )
#endif

#include <vector>
#include <flightcrew.h>
namespace fc = FlightCrew;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * Constructor. 
     *
     * @param parent The window's parent object.
     * @param flags The flags used to modify window behavior.
     */
    MainWindow( QWidget *parent = 0, Qt::WindowFlags flags = 0 );

    /**
     * Destructor.
     */
    ~MainWindow();

protected:

    /**
     * Handles drag events. In our case, this func only 
     * allows file drags.
     * @note Overridden from QMainWindow.
     *
     * @param event The drag event.
     */
    void dragEnterEvent( QDragEnterEvent *event );

    /**
     * Handles drop events. In our case, file drop events.
     * The file is then validated.
     * @note Overridden from QMainWindow.
     *
     * @param event The drop event.
     */
    void dropEvent( QDropEvent *event );

private slots:

    /**
     * Validates the epub file listed in the combo box. 
     */
    void StartValidation();

    /**
     * Opens a file browsing dialog so that the user
     * can select a file to validate.
     */
    void BrowseForEpub();

private:

    /**
     * Displays the validation results in the table.
     *
     * @param results The validation results we got from FlightCrew.
     */
    void DisplayResults( const std::vector< fc::Result > &results );

     /**
      * Informs the user that no problems were found.
      */
    void DisplayNoProblemsMessage();

    /**
     * Adds a filename to the combo box and makes in the 
     * currently selected item.
     *
     * @param filename The file to add to the combo.
     */
    void AddFilenameToComboBox( const QString &filename );

     /**
     * Reads all the stored application settings like 
     * window position, geometry etc.
     */
    void ReadSettings();

    /**
     * Writes all the stored application settings like 
     * window position, geometry etc.
     */
    void WriteSettings();

     /**
      * Confirgures the table for presenting validation results.
      */
    void ConfigureTableForResults();

    /**
     * Connects all the required signals to their slots.
     */
    void ConnectSignalsToSlots();
    

    ///////////////////////////////
    // PRIVATE MEMBER VARIABLES
    ///////////////////////////////


    /**
     * The last folder from which the user opened a file.
     */
    QString m_LastFolderOpen;

    /**
     * Holds all the widgets Qt Designer created for us.
     */
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
