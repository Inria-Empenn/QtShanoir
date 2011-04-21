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

namespace WebServices
{

class WSQuery: public QObject
{
    Q_OBJECT
public:

    WSQuery();

    void query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);
    QString getresult() { return result; }
    QByteArray& getRaw() { return raw; }
    static WSQuery& Instance() { static WSQuery q; return q; }

public:
    void run();
    //    QMutex mutex;
    bool finished()  { return done; }

    static QString Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);
    static QByteArray BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);

protected slots:
    void sslErrors ( const QList<QSslError> & errors );
    void getResponse();
protected:
    QString result;
    QByteArray raw;

    QtSoapHttpTransport http;
//    QString user, password, host, port, truststore;
    QNetworkRequest req;

    bool done;
    QString WebService, WsMethod,  WsImpl;
    QStringList argname, argval;

};


}
#endif // WSQUERY_H
