#include "qtshanoirwebservice.h"

QtShanoirWebService::QtShanoirWebService()
{
    QObject::connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
    req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);
}

void QtShanoirWebService::query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval)
{
    done = false;
    result.clear();
    raw.clear();
    this->webService = WebService;
    this->wsMethod = WsMethod;
    this->wsImpl = WsImpl;
    this->argname = argname;
    this->argval = argval;
    run();
}

void QtShanoirWebService::queryStruct(QString WebService, QString WsMethod, QString WsImpl, QtSoapType* structPro)
{
    done = false;
    result.clear();
    this->webService = WebService;
    this->wsMethod = WsMethod;
    this->wsImpl = WsImpl;


    runStruct(structPro);
}

bool QtShanoirWebService::QueryStruct(QString WebService, QString WsMethod, QString WsImpl, QtSoapType* structPro, QString &queryResult)
{
    QtShanoirWebService query;
    query.queryStruct(WebService, WsMethod, WsImpl, structPro);
    while (!query.getDone())
        qApp->processEvents(); //a voir
    queryResult = query.getresult();
    return query.getRequestSuccess();
        //return true;
}

bool QtShanoirWebService::Query(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QString &queryResult)
{
    QtShanoirWebService query;
    query.query(WebService, WsMethod, WsImpl, argname, argval);
    while (!query.getDone())
        qApp->processEvents(); //a voir
    queryResult = query.getresult();
    return query.getRequestSuccess();
        //return true;
}


bool QtShanoirWebService::BinaryQuery(QString WebService, QString WsMethod, QString WsImpl, QStringList argname, QStringList argval, QByteArray &queryResult)
{
    QtShanoirWebService query;
    query.query(WebService, WsMethod, WsImpl, argname, argval);
    while (!query.getDone())
        qApp->processEvents();
    queryResult = query.getRaw();
    return query.getRequestSuccess();
}

void QtShanoirWebService::run()
{
    requestSuccess = true;
    QtSoapMessage request;

    request.setMethod(wsMethod, wsImpl);

    for (int i = 0; i < argname.count(); ++i)
    {
        request.addMethodArgument(argname.at(i), "", argval.at(i));
    }
    QString host = GlobalData::settings.getHost();
    int port = GlobalData::settings.getPort();

    if (host == "localhost")
        http.setHost(host, false, port);
    else
        http.setHost(host, true, port);

    QString link = QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(webService);
    qDebug()<<"link"<<link;
    link = link+"?wsdl";
    qDebug()<<"link"<<link;
    http.setAction(link);
   // http.setAction(QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(WebService));
    http.submitRequest(req, request, "//Shanoir-Shanoir/" + webService);
    qDebug()<<"SoapMessage"<<request.toXmlString();
    QNetworkReply *nrep = http.networkReply();
    connect(nrep, SIGNAL(sslErrors ( const QList<QSslError>&)), this, SLOT(sslErrors (const QList<QSslError>&)));
}


void QtShanoirWebService::runStruct(QtSoapType* structName)
{
    requestSuccess = true;
    QtSoapMessage request;

    request.setMethod(wsMethod, wsImpl);

    request.addMethodArgument(structName);


    QString host = GlobalData::settings.getHost();
    int port = GlobalData::settings.getPort();

    if (host == "localhost")
        http.setHost(host, false, port);
    else
        http.setHost(host, true, port);

    QString link = QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(webService);
    qDebug()<<"link"<<link;
    link = link+"?wsdl";
    qDebug()<<"link"<<link;
    http.setAction(link);
    http.submitRequest(req, request, "//Shanoir-Shanoir/" + webService);
    qDebug()<<"SoapMessage"<<request.toXmlString();
    QNetworkReply *nrep = http.networkReply();
    connect(nrep, SIGNAL(sslErrors ( const QList<QSslError>&)), this, SLOT(sslErrors (const QList<QSslError>&)));
}

QString QtShanoirWebService::getresult()
{
    return this->result;
}

void QtShanoirWebService::setresult(QString result)
{
    this->result = result;
}

QByteArray& QtShanoirWebService::getRaw()
{
    return this->raw;
}

void QtShanoirWebService::setRaw(QByteArray& raw)
{
    this->raw = raw;
}

bool QtShanoirWebService::getDone()
{
    return this->done;
}

void QtShanoirWebService::setDone(bool done)
{
     this->done = done;
}

bool QtShanoirWebService::getRequestSuccess()
{
    return this->requestSuccess;
}

void QtShanoirWebService::setRequestSuccess(bool request)
{
    this->requestSuccess = request;
}

void QtShanoirWebService::sslErrors(const QList<QSslError> & errors)
{
    if (errors.size() == 0)
        return;
    if (http.networkReply())
        http.networkReply()->ignoreSslErrors();
    for (int i = 0; i < errors.size(); ++i)
    {
        if (errors.at(i).error() == QSslError::SelfSignedCertificate ||
                errors.at(i).error() == QSslError::SelfSignedCertificateInChain ||
                errors.at(i).error() == QSslError::CertificateUntrusted ||
                errors.at(i).error() == QSslError::HostNameMismatch)
        {
            http.networkReply()->ignoreSslErrors();
        }
        else
        {
            qDebug() << errors.at(i).errorString();
            result = errors.at(i).errorString();
            requestSuccess = false;
        }
    }
}

void QtShanoirWebService::getResponse()
{
    const QtSoapMessage &message = http.getResponse();
    if (message.isFault()) {
        qDebug() << message.faultString().value().toString();
        result = message.faultString().value().toString();
        requestSuccess = false;
    }
    else
        result = message.toXmlString();
    const QByteArray& bin = message.getBinary();
    if (!bin.isEmpty()) {
        qDebug() << "Binary file...";
        raw = bin;
    }
    done = true;
}

QString QtShanoirWebService::getWebService()
{
    return this->webService;
}
