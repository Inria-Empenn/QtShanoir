#include "wsquery.h"
//#include "shanoirserverparameters.h"

#include <QMessageBox>
namespace WebServices
{
WSQuery::WSQuery()
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
    req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);

}

void WSQuery::getResponse()
{
    //    qDebug() << "Response arrived";
    // Get a reference to the response message.
    const QtSoapMessage &message = http.getResponse();

    // Check if the response is a SOAP Fault message
    if (message.isFault()) {
        qDebug() << message.faultString().value().toString();
        qDebug() << message.faultCode();
        qDebug() << message.toXmlString();
        //        qDebug() << "Error: " << message.faultDetail().toString();

        //        qDebug("Error: %s", message.returnValue().toString().toLatin1().constData());
    }
    else
        this->result = message.toXmlString();
    const QByteArray& bin = message.getBinary();
    if (!bin.isEmpty())
    {
        qDebug() << "Binary file...";
        raw = bin;
    }
    done = true;
    //    mutex.unlock();
}



void	WSQuery::sslErrors ( const QList<QSslError> & errors )
{
    if (errors.size() == 0) return;
    if (http.networkReply())
        http.networkReply()->ignoreSslErrors();

    for (int i = 0; i < errors.size(); ++i)
    {
        if (errors.at(i) == QSslError::SelfSignedCertificate || errors.at(i).error() == QSslError::SelfSignedCertificateInChain)
            http.networkReply()->ignoreSslErrors();
        else
        {
            qDebug() << errors.at(i).error() << errors.at(i).errorString();
        }
        qDebug() << errors.at(i).error() << errors.at(i).errorString();

    }
    //    mutex.unlock();
}


void WSQuery::run()
{
    //    mutex.lock();
    qDebug() << "Starting query for " << WsMethod;

    QtSoapMessage request;
    request.setMethod(WsMethod, WsImpl);

    for (int i = 0; i < argname.count(); ++i)
        request.addMethodArgument(argname.at(i), "", argval.at(i));

    // Submit the request the the web service.
    QString host = QtShanoirSettings::Instance()->host();
    QString port = QtShanoirSettings::Instance()->port();

    http.setHost(host, true, port.toInt()); // set secure connection and port

    http.setAction(QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(WebService));
    http.submitRequest(req, request, "//Shanoir-Shanoir/"+WebService);


    QNetworkReply *nrep = http.networkReply();
    connect(nrep, SIGNAL(sslErrors ( const QList<QSslError> & )), this, SLOT(sslErrors ( const QList<QSslError> &)));
}


void WSQuery::query(QString WebService_, QString WsMethod_, QString WsImpl_, QStringList argname_, QStringList argval_)
{
    done = false;
    result.clear();
    raw.clear();

    WebService = WebService_;
    WsMethod = WsMethod_;
    WsImpl = WsImpl_;
    argname = argname_;
    argval = argval_;
    this->run();
}

QString Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval)
{
    WSQuery& query = WSQuery::Instance();

    query.query(WebService,  WsMethod,  WsImpl,  argname,  argval);

    while (!query.finished())
        qApp->processEvents();

    return query.getresult();
}

QByteArray BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval)
{
    WSQuery& query = WSQuery::Instance();

    query.query(WebService,  WsMethod,  WsImpl,  argname,  argval);

    while (!query.finished())
        qApp->processEvents();

    return query.getRaw();
}


}
