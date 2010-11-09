/************************************************************************
**
**  Copyright (C) 2009, 2010  Strahinja Markovic
**
**  This file is part of FlightCrew.
**
**  FlightCrew is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  FlightCrew is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <QRegExp>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDateTime>
#include <QMessageBox>
#include <QDesktopServices>
#include <QXmlStreamReader>
#include <QTextStream>
#include "UpdateChecker.h"

static const QString DOWNLOAD_PAGE_LOCATION  = "http://code.google.com/p/flightcrew/downloads/list";
static const QString UPDATE_XML_LOCATION     = "http://flightcrew.googlecode.com/hg/version.xml";
static const QString XML_VERSION_ELEMENT     = "current-version";
static const QString LAST_ONLINE_VERSION_KEY = "last_online_version";
static const QString LAST_CHECK_TIME_KEY     = "last_check_time";
static const QString SETTINGS_GROUP          = "updatechecker";
static const QString VERSION_NUMBERS         = "(\\d+)\\.(\\d+)\\.(\\d+)";
static const QString FLIGHTCREW_VERSION      = QString( FLIGHTCREW_FULL_VERSION );

// Delta is six hours
static const int SECONDS_BETWEEN_CHECKS      = 60 * 60 * 6 ;


// Constructor;
// The argument is the object's parent
UpdateChecker::UpdateChecker( QObject *parent )
    : 
    QObject( parent ),
    m_NetworkManager( new QNetworkAccessManager( this ) )
{
    connect(    m_NetworkManager,  SIGNAL( finished( QNetworkReply* ) ),
                this,              SLOT( ReplyRecieved( QNetworkReply* ) )
           );
}


// Sends a request for the online version
// if the last check was performed
// a SECONDS_BETWEEN_CHECKS amount of time ago
void UpdateChecker::CheckForUpdate()
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    // The default time is one always longer than the check interval
    QDateTime default_time    = QDateTime::currentDateTime().addSecs( - SECONDS_BETWEEN_CHECKS - 1 );
    QDateTime last_check_time = settings.value( LAST_CHECK_TIME_KEY, default_time ).toDateTime();

    // We want to check for a new version
    // no sooner than every six hours
    if ( last_check_time.secsTo( QDateTime::currentDateTime() ) > SECONDS_BETWEEN_CHECKS )
    {
        settings.setValue( LAST_CHECK_TIME_KEY, QDateTime::currentDateTime() );

        m_NetworkManager->get( QNetworkRequest( QUrl( UPDATE_XML_LOCATION ) ) );        
    }
}


// Gets called when the request posted by CheckForUpdate()
// gets to the server and it replies with "reply"
void UpdateChecker::ReplyRecieved( QNetworkReply* reply )
{
    QSettings settings;
    settings.beginGroup( SETTINGS_GROUP );

    QString last_online_version    = settings.value( LAST_ONLINE_VERSION_KEY, QString() ).toString();
    QString current_online_version = ReadOnlineVersion( TextInReply( reply ) );

    bool is_newer = IsOnlineVersionNewer( FLIGHTCREW_VERSION, current_online_version );

    // The message box is displayed only if the online version is newer
    // and only if the user hasn't been informed about this release before
    if ( is_newer && ( current_online_version != last_online_version ) )
    {
        QMessageBox::StandardButton button_clicked;

        button_clicked = QMessageBox::question(  0,
                     QObject::tr( "FlightCrew" ),
                     QObject::tr( "<p>A newer version of FlightCrew is available, version <b>%1</b>.<br/>"
                         "The ChangeLog can be seen <a href='http://flightcrew.googlecode.com/hg/ChangeLog.txt'>here</a>.</p>"
                         "<p>Would you like to go to the download page?</p>" )
                     .arg( current_online_version ),
                     QMessageBox::Yes | QMessageBox::No,
                     QMessageBox::Yes );

        if ( button_clicked == QMessageBox::Yes )
        {
            QDesktopServices::openUrl( QUrl( DOWNLOAD_PAGE_LOCATION ) );
        }
    }

    // Store the current online version as the last one checked
    settings.setValue( LAST_ONLINE_VERSION_KEY, current_online_version );

    // Schedule this object for deletion.
    // There is no point for its existence
    // after it has received and processed the net reply. 
    deleteLater();
}


// Returns the full text present in the network reply
QString UpdateChecker::TextInReply( QNetworkReply* reply ) const
{
    // Check if we can open the reply
    if ( !reply->open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return "";
    }

    QTextStream in( reply );

    // Input should be UTF-8
    in.setCodec( "UTF-8" );

    // This will automatically switch reading from
    // UTF-8 to UTF-16 if a BOM is detected
    in.setAutoDetectUnicode( true );

    return in.readAll();
}


// Returns the version string present
// in the specified XML file, or an empty QString
// if the required element is not present.
QString UpdateChecker::ReadOnlineVersion( QString online_version_xml ) const
{
    if ( online_version_xml.isEmpty() )

        return QString();

    QXmlStreamReader version_reader( online_version_xml );

    while ( !version_reader.atEnd() ) 
    {
        // Get the next token from the stream
        if ( ( version_reader.readNext() == QXmlStreamReader::StartElement ) &&
             ( version_reader.name() == XML_VERSION_ELEMENT )
           ) 
        {
           return version_reader.readElementText();
        }
    }

    return QString();
}


// Compares the two provided version strings
// and returns true if the online string specifies
// that the online version is newer.
bool UpdateChecker::IsOnlineVersionNewer( QString current_version_string, QString online_version_string ) const
{
    if ( current_version_string.isEmpty() || online_version_string.isEmpty() )

        return false;

    QRegExp current_version_numbers( VERSION_NUMBERS );
    QString( current_version_string ).indexOf( current_version_numbers );

    QRegExp online_version_numbers( VERSION_NUMBERS );
    QString( online_version_string ).indexOf( online_version_numbers );

    // This code assumes three digits per field,
    // which should be way more than enough
    int current_version = current_version_numbers.cap( 1 ).toInt() * 1000000 +
                          current_version_numbers.cap( 2 ).toInt() * 1000 +
                          current_version_numbers.cap( 3 ).toInt();

    int online_version = online_version_numbers.cap( 1 ).toInt() * 1000000 +
                         online_version_numbers.cap( 2 ).toInt() * 1000 +
                         online_version_numbers.cap( 3 ).toInt();

    return online_version > current_version;
}

