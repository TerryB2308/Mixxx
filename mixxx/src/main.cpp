/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Mon Feb 18 09:48:17 CET 2002
    copyright            : (C) 2002 by Tue and Ken Haste Andersen
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qapplication.h>
#include <qfont.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qtranslator.h>
#include <qmessagebox.h> 
#include <qfile.h>
#include <qtextstream.h>
#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#include "mixxx.h"

void qInitImages_mixxx();
    
void MessageOutput( QtMsgType type, const char *msg )
{
        switch ( type ) {
            case QtDebugMsg:
                fprintf( stderr, "Debug: %s\n", msg );
                break;
            case QtWarningMsg:
                fprintf( stderr, "Warning: %s\n", msg );
                //QMessageBox::warning(0, "Mixxx", msg);
                break;
            case QtFatalMsg:
                fprintf( stderr, "Fatal: %s\n", msg );
                QMessageBox::warning(0, "Mixxx", msg);
                exit(-1);
                //abort();                        // dump core on purpose
    }
}

QFile Logfile; // global logfile variable

void MessageToLogfile( QtMsgType type, const char *msg )
{
	QTextStream Log( &Logfile );
	switch ( type ) {
	case QtDebugMsg:
		Log << "Debug: " << msg << "\n";
		break;
	case QtWarningMsg:
		Log << "Warning: " << msg << "\n";
		break;
	case QtFatalMsg:
		fprintf( stderr, "Fatal: %s\n", msg );
		QMessageBox::warning(0, "Mixxx", msg);
		exit(-1);
    }
    Logfile.flush();
}


int main(int argc, char *argv[])
{
#ifdef Q_WS_WIN
  // For windows write all debug messages to a logfile:
  Logfile.setName( "c:/mixxx.log" );
  Logfile.open( IO_WriteOnly );
  qInstallMsgHandler( MessageToLogfile );
#else
  // For others, write to the console:
  qInstallMsgHandler( MessageOutput );
#endif

  // Ensure image data is initialized
  //qInitImages_mixxx();
  
  QApplication a(argc, argv);
//  a.setFont(QFont("helvetica", 10));
  QTranslator tor( 0 );
  // set the location where your .qm files are in load() below as the last parameter instead of "."
  // for development, use "/" to use the english original as
  // .qm files are stored in the base project directory.
  tor.load( QString("mixxx.") + QTextCodec::locale(), "." );
  a.installTranslator( &tor ); 
  /* uncomment the following line, if you want a Windows 95 look*/
  // a.setStyle(WindowsStyle);
    
  MixxxApp *mixxx=new MixxxApp(&a);
  a.setMainWidget(mixxx);
  mixxx->resize( 726, 523);
  mixxx->setFixedWidth(726);
  mixxx->setFixedHeight(523);
  //mixxx->setIcon(QPixmap());

  mixxx->show();
  int result = a.exec();
  delete mixxx;
  return result;
}

