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
