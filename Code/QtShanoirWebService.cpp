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

#include "QtShanoirWebService.h"
#include <QMessageBox>

class QtShanoirWebServicePrivate
{
    public:
        QString result;
        QByteArray raw;

        QtSoapHttpTransport http;
        QNetworkRequest req;

        bool done;
        bool requestSuccess;
        QString WebService, WsMethod, WsImpl;
        QStringList argname, argval;
};

QtShanoirWebService&
QtShanoirWebService::Instance()
{
    static QtShanoirWebService q;
    return q;
}

QtShanoirWebService::QtShanoirWebService() : d(new QtShanoirWebServicePrivate)
{
    QObject::connect(&d->http, SIGNAL(responseReady()), this, SLOT(getResponse()));
    d->req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);
}

QString
QtShanoirWebService::getresult()
{
    return d->result;
}

QByteArray&
QtShanoirWebService::getRaw()
{
    return d->raw;
}

bool QtShanoirWebService::requestSuccess()
{
    return d->requestSuccess;
}

bool
QtShanoirWebService::finished()
{
    return d->done;
}

void
QtShanoirWebService::getResponse()
{
    // Get a reference to the response message.
    const QtSoapMessage &message = d->http.getResponse();

    // Check if the response is a SOAP Fault message
    if (message.isFault()) {
        qDebug() << message.faultString().value().toString();
        d->result = message.faultString().value().toString();
        d->requestSuccess = false;
    }
    else
        d->result = message.toXmlString();
    const QByteArray& bin = message.getBinary();
    if (!bin.isEmpty()) {
        qDebug() << "Binary file...";
        d->raw = bin;
    }
    d->done = true;
}

void
QtShanoirWebService::sslErrors(const QList<QSslError> & errors)
{
    if (errors.size() == 0)
        return;
    if (d->http.networkReply())
        d->http.networkReply()->ignoreSslErrors();

    for (int i = 0; i < errors.size(); ++i)
    {
        if (errors.at(i).error() == QSslError::SelfSignedCertificate ||
                errors.at(i).error() == QSslError::SelfSignedCertificateInChain ||
                errors.at(i).error() == QSslError::CertificateUntrusted ||
                errors.at(i).error() == QSslError::HostNameMismatch)
        {
            d->http.networkReply()->ignoreSslErrors();
        }
        else
        {
            qDebug() << errors.at(i).errorString();
            d->result = errors.at(i).errorString();
            d->requestSuccess = false;
        }
    }
}

void
QtShanoirWebService::run()
{
    d->requestSuccess = true;
    QtSoapMessage request;
    request.setMethod(d->WsMethod, d->WsImpl);

    for (int i = 0; i < d->argname.count(); ++i)
        request.addMethodArgument(d->argname.at(i), "", d->argval.at(i));

    // Submit the request the the web service.
    QString host = QtShanoirSettings::Instance()->host();
    QString port = QtShanoirSettings::Instance()->port();

    d->http.setHost(host, true, port.toInt()); // set secure connection and port

    d->http.setAction(QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(d->WebService));
    d->http.submitRequest(d->req, request, "//Shanoir-Shanoir/" + d->WebService);

    QNetworkReply *nrep = d->http.networkReply();
    connect(nrep, SIGNAL(sslErrors ( const QList<QSslError> & )), this, SLOT(sslErrors ( const QList<QSslError> &)));
}

void
QtShanoirWebService::query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval)
{
    d->done = false;
    d->result.clear();
    d->raw.clear();

    d->WebService = WebService;
    d->WsMethod = WsMethod;
    d->WsImpl = WsImpl;
    d->argname = argname;
    d->argval = argval;
    this->run();
}

bool
QtShanoirWebService::Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QString &queryResult)
{
    QtShanoirWebService& query = QtShanoirWebService::Instance();

    query.query(WebService, WsMethod, WsImpl, argname, argval);

    while (!query.finished())
        qApp->processEvents();

    queryResult = query.getresult();
    return query.requestSuccess();
}

bool
QtShanoirWebService::BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QByteArray &queryResult)
{
    QtShanoirWebService& query = QtShanoirWebService::Instance();

    query.query(WebService, WsMethod, WsImpl, argname, argval);

    while (!query.finished())
        qApp->processEvents();

    queryResult = query.getRaw();
    return query.requestSuccess();
}
