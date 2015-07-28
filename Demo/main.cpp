#include <QtGui>
#include <Demo.h>

int main( int argc , char *argv[] )
{
	QApplication app(argc, argv);

            QDir iniDir (QDir::homePath() + QDir::separator() + ".shanoir");
            if (!iniDir.exists())
                QDir(QDir::homePath()).mkdir(".shanoir");
            QString iniFile = iniDir.absolutePath() + QDir::separator() + "properties";

                QLibrary library("DAO.dll");
                if (!library.load())
                        qDebug() << library.errorString();
                else
                        qDebug() << "library loaded";
                typedef void (* CallFunction)(QString);
                CallFunction cf = (CallFunction)library.resolve("configureSettings");
                if (cf)
                {
                     cf(iniFile);
                }
                else
                    qDebug() << "could not call function";




/*
	QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
	QTranslator myappTranslator;
    myappTranslator.load("myapp_" + QLocale::system().name());
    app.installTranslator(&myappTranslator);
*/
	/*path lib */
	//QCoreApplication::addLibraryPath(const QString& path)
	//qDebug()<<QDir::currentPath();
	//SetDllDirectory("QDir::separator() + GUI");
	//QCoreApplication::addLibraryPath("..\\GUI\\");

//        QLibrary dao_library("DAO.dll");
//        if (!dao_library.load())
//                qDebug() << dao_library.errorString();
//        else
//                qDebug() << "library loaded";

         QLibrary gui_library("GUI.dll");
        if (!gui_library.load())
                qDebug() << gui_library.errorString();
	else
		qDebug() << "library loaded";
	typedef Demo* (* CreateWidgetFunction)(void);
        CreateWidgetFunction cwf = (CreateWidgetFunction)gui_library.resolve("createShanoirMainwidget");
	if (cwf) 
	{
		Demo* wid = cwf();
		if (wid)
			wid->show();
	} 
	else 
	{
		qDebug() << "Could not show widget from the loaded library";
	}
 return app.exec();
}

