#ifndef QTSHANOIRWEBSERVICE_H
#define QTSHANOIRWEBSERVICE_H

#include <QtCore>
#include <QNetworkRequest>
#include <QtNetwork>
#include "qtshanoirmain.h"
#include <qtsoap.h>



class  QtShanoirWebService : public QObject
{
    Q_OBJECT
private:
    QString result;
    QByteArray raw;
    QtSoapHttpTransport http;
    QNetworkRequest req;
    bool done;
    bool requestSuccess;
    QString webService, wsMethod, wsImpl;
    QStringList argname, argval;

public:
    QtShanoirWebService();
    void query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval);
    void queryStruct(QString WebService, QString WsMethod, QString WsImpl, QtSoapType* structPro);
    static bool Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QString &queryResult);
    static bool QueryStruct(QString WebService, QString WsMethod, QString WsImpl, QtSoapType* structPro, QString &queryResult);
    static bool BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QByteArray &queryResult);
    void run();
    void runStruct(QtSoapType* structName);
    QString getresult();
    void setresult(QString);
    QByteArray& getRaw();
    void setRaw(QByteArray&);
    bool getDone();
    void setDone(bool);
    bool getRequestSuccess();
    void setRequestSuccess(bool);
    QString getWebService();

public slots:
    void sslErrors(const QList<QSslError> & errors);
    void getResponse();
};

#endif // QTSHANOIRWEBSERVICE_H
