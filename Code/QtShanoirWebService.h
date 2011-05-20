#ifndef WSQUERY_H
#define WSQUERY_H

#include <QSettings>
#include <QProcessEnvironment>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QMessageBox>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QtSoap.h>

#include <QThread>
#include "QtShanoirSettings.h"
// Use this class to perform a Query

class QtShanoirWebServicePrivate;

class QtShanoirWebService : public QObject
{
    Q_OBJECT
    public:

        QtShanoirWebService();

        void
        query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);

        QString
        getresult();

        QByteArray&
        getRaw();

        static QtShanoirWebService&
        Instance();

    public:
        void
        run();

        bool
        finished();

        static QString
        Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);
        static QByteArray
        BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);

    protected slots:
        void
        sslErrors(const QList<QSslError> & errors);
        void
        getResponse();
//    protected:
//        QString result;
//        QByteArray raw;
//
//        QtSoapHttpTransport http;
//        QNetworkRequest req;
//
//        bool done;
//        QString WebService, WsMethod, WsImpl;
//        QStringList argname, argval;
    private:
        QtShanoirWebServicePrivate * d;
};
#endif // WSQUERY_H
