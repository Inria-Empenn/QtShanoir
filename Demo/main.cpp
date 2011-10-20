/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <QApplication>
#include <iostream>
#include <QFileDialog>
#include <Demo.h>

int
main( int argc , char *argv[] )
  {
    QApplication app(argc, argv);
    Demo demo;
    demo.show();
    return app.exec();
  }

//#include <Arguments.hh>
//#include "qt_shanoir.h"
//
//
//#include <QTextStream>
//
//#ifdef WIN32
//void myMessageOutput(QtMsgType type, const char *msg)
//{
//    switch (type) {
//    case QtDebugMsg:
//        fprintf(stdout, "Debug: %s\n", msg);
//        break;
//    case QtWarningMsg:
//        fprintf(stdout, "Warning: %s\n", msg);
//        break;
//    case QtCriticalMsg:
//        fprintf(stdout, "Critical: %s\n", msg);
//        break;
//    case QtFatalMsg:
//        fprintf(stdout, "Fatal: %s\n", msg);
//        abort();
//    }
//}
//
//#endif
//
//int main(int ac,  char* av[])
//{
//#ifdef WIN32
//    qInstallMsgHandler(myMessageOutput);
//#endif
//    // DJDecoderRegistration::registerCodecs();
//    QCoreApplication::setOrganizationName("Neurinfo/CHU-Rennes");
//    QCoreApplication::setOrganizationDomain("neurinfo.org");
//    QCoreApplication::setApplicationName("MultiMRView");
//
//
//    QApplication*  app = new QApplication(ac, av);
//
//    {
//        QFile fsheet(":/StyleSheets/MRView.css");
//        fsheet.open(QFile::ReadOnly);
//        QTextStream in(&fsheet);
//        QString sheet = in.readAll();
//        qApp->setStyleSheet(sheet);
//    }
//    /*
//    QScriptEngine engine;
//
//#if !defined(QT_NO_SCRIPTTOOLS)
//    QScriptEngineDebugger debugger;
//    debugger.attachTo(&engine);
//    QMainWindow *debugWindow = debugger.standardWindow();
//    debugWindow->resize(1024, 640);
//    debugWindow->show();
//
//#endif
//    */
//
//    std::cout << "Started\n";
//    QtShanoir win;
//    //  win.main(ac, av);
//
//    //    engine.newQObject(&win, QScriptEngine::AutoOwnership, QScriptEngine::PreferExistingWrapperObject);
//
//
//    win.show();
//    app->exec();
//
//    // DJDecoderRegistration::cleanup();
//    return 0;
//}
