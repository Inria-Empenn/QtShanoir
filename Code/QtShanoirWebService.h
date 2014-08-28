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

        bool requestSuccess();

    public:
        void
        run();

        bool
        finished();

        static bool Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QString &queryResult);
        static bool BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QByteArray &queryResult);

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
