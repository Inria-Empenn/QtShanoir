/*
 * QtShanoirController.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoirController.h>
#include <QtShanoirWsQuery.h>
#include <QtShanoirSettings.h>

class QtShanoirControllerPrivate
{
    private:
        int num_message;
        QtSoapHttpTransport http;
        QNetworkRequest req;

        // the server, the namespace of the ws and the ws name
        QString wsimpl, ws;

        const QtShanoirWsQuery * query;

        // Fill the following map with the properly set up query
        QMap<QString, QList<WsQuery*> > perWsQuery;
        int curId;

};

QtShanoirController::QtShanoirController() :
    d(new QtShanoirControllerPrivate)
{

}

void
QtShanoirController::prepareMessage()
{
    d->query = 0;
    if (d->num_message < d->perWsQuery[ws].count())
        d->query = d->perWsQuery[ws].at(d->num_message);
}

void
QtShanoirController::setConfiguration()
{
    ShanoirServerParameters dia(this);
    dia.exec();

    dia.getParameters(user, password, host, port);
    QFile set(QDir::homePath() + "/.shanoir/server.properties");
    QDir dir(QDir::homePath());
    dir.mkdir(".shanoir");
    if (!set.open(QFile::WriteOnly))
        QMessageBox::warning(this, "Write Error", QString("Properties were not written to file:\n %1").arg(QDir::homePath() + "/.shanoir/server.properties"));

    QTextStream out(&set);
    out << "user=" << user << "\r\n";
    out << "password=" << password << "\r\n";
    out << "host=" << host << "\r\n";
    out << "port=" << port << "\r\n";
    out << QString("truststore=%1/.shanoir/neurinfo.truststore\r\n").arg(QDir::homePath());
    set.close();
}

void
QtShanoirController::sendMessage()
{
    prepareMessage();
    if (!query)
        return;

    qDebug() << query->WsMethod;

    QtSoapMessage request;
    request.setMethod(query->WsMethod, query->WsImpl);
    for (int i = 0; i < query->WsMethodarg.count(); ++i)
        request.addMethodArgument(query->WsMethodarg.at(i).first, "", query->WsMethodarg.at(i).second);

    //    if (query->WsMethod == "download")
    //        qDebug() << request.toXmlString();

    // Submit the request the the web service.
    http.setHost(host, true, port.toInt()); // set secure connection and port

    http.setAction(QString("https://%1//Shanoir-Shanoir/%2").arg(host).arg(query->WebService));
    http.submitRequest(req, request, "//Shanoir-Shanoir/" + query->WebService);

    //    if (ws == "FindDataSets")
    //  qDebug() << request.toXmlString();

    QNetworkReply *nrep = http.networkReply();
    connect(nrep, SIGNAL(sslErrors ( const QList<QSslError> & )), this, SLOT(sslErrors ( const QList<QSslError> &)));
    //ui->download->setFormat ("Download started %p");
    //  ui->upload->setFormat ("upload started %p");
    ui->infos->setText("Sending request to Server");
    connect(nrep, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    //    connect(nrep, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
}

void
QtShanoirController::doQuery(QString ws)
{
    this->ws = ws;

    num_message = 0;
    emit sendMessage();
}
