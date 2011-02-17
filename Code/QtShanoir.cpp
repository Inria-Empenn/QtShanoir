/*
 * QtShanoir.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoir.h>
#include <QtShanoirWsQuery.h>
#include <QtShanoirSettings.h>
#include <QtShanoirTreeWidget.h>
#include <QtShanoirProgressWidget.h>
#include <QtShanoirSettingsWidget.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

QtShanoir * QtShanoir::_instance = 0;

class QtShanoirPrivate
{
    public:
        QtShanoirTreeWidget * tree;
        QtShanoirProgressWidget * progress;
        int num_message;
        QtSoapHttpTransport http;
        QNetworkRequest req;
        // the server, the namespace of the ws and the ws name
        QString wsimpl, ws;
        const QtShanoirWsQuery * query;
        // Fill the following map with the properly set up query
        QMap<QString, QList<QtShanoirWsQuery*> > perWsQuery;
        int curId;
        QList<int> selectedIds;
        QString downloadDir;
        //        bool waitForDownload;
        QString downloadFileName;

};

QtShanoir *
QtShanoir::instance()
{
    if (_instance == 0)
        _instance = new QtShanoir();
    return _instance;
}

QtShanoir::QtShanoir() :
    d(new QtShanoirPrivate)
{
    d->tree = 0;
    d->progress = 0;
    d->downloadFileName = "";
    //    d->waitForDownload = false;
    //this->doQuery("StudyFindId");
}

void
QtShanoir::setDownloadFilename(QString filename)
{
    d->downloadFileName = filename;
}

void
QtShanoir::clearTree()
{
    d->selectedIds.clear();
    if (d->tree)
        d->tree->treeWidget->clear();
}

void
QtShanoir::initWS()
{
    if (d->tree) {
        QtShanoirSettings::Instance();
        this->populateQueries();

        QObject::connect(this, SIGNAL(nextMessage()), this, SLOT(sendMessage()));
        QObject::connect(&(d->http), SIGNAL(responseReady()), this, SLOT(getResponse()));
        d->req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);
    }
    QObject::connect(this, SIGNAL(getFileName()), this, SLOT(callGetFileNameWS()));
    QObject::connect(this, SIGNAL(startDownload()), this, SLOT(callDownloadWS()));
}

void
QtShanoir::attachTreeWidget(QtShanoirTreeWidget * widget)
{
    d->tree = widget;
    if (d->tree) {
        QObject::connect(d->tree, SIGNAL(mrExamQuery(QString)), this, SLOT(mrExamQuery(QString)));
        QObject::connect(d->tree, SIGNAL(datasetQuery(QString,QString)), this, SLOT(datasetQuery(QString,QString)));
        QObject::connect(d->tree, SIGNAL(id(int)), this, SLOT(currentId(int)));
        QObject::connect(d->tree, SIGNAL(selected(QList<int>)), this, SLOT(updateSelected(QList<int>)));
        QObject::connect(d->tree, SIGNAL(filename(QString)), this, SLOT(setDownloadFilename(QString)));
        //        QObject::connect(d->tree, SIGNAL(queryFinished()), this, SLOT(queryFinished()));
    }
}

void
QtShanoir::attachProgressWidget(QtShanoirProgressWidget * widget)
{
    d->progress = widget;
}

void
QtShanoir::prepareMessage()
{
    d->query = 0;
    if (d->num_message < d->perWsQuery[d->ws].count())
        d->query = d->perWsQuery[d->ws].at(d->num_message);
}

void
QtShanoir::sendMessage()
{
    this->prepareMessage();
    if (!d->query)
        return;

    //qDebug() << d->query->WsMethod;

    QtSoapMessage request;
    request.setMethod(d->query->WsMethod, d->query->WsImpl);
    for (int i = 0; i < d->query->WsMethodarg.count(); ++i)
        request.addMethodArgument(d->query->WsMethodarg.at(i).first, "", d->query->WsMethodarg.at(i).second);

    // Submit the request the the web service.
    d->http.setHost(QtShanoirSettings::Instance()->host(), true, QtShanoirSettings::Instance()->port().toInt()); // set secure connection and port

    d->http.setAction(QString("https://%1//Shanoir-Shanoir/%2").arg(QtShanoirSettings::Instance()->host()).arg(d->query->WebService));
    d->http.submitRequest(d->req, request, "//Shanoir-Shanoir/" + d->query->WebService);

    QNetworkReply *nrep = d->http.networkReply();
    QObject::connect(nrep, SIGNAL(sslErrors ( const QList<QSslError> & )), this, SLOT(sslErrors ( const QList<QSslError> &)));

    //    if (d->progress)
    //        QObject::connect(nrep, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
}

void
QtShanoir::doQuery(QString ws)
{
    d->ws = ws;
    d->num_message = 0;
    this->sendMessage();
}

void
QtShanoir::getError(QString xmlserial)
{
    //    qDebug() << xmlserial;

    QDomDocument doc;
    doc.setContent(xmlserial);

    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    QString errmsg = doc.firstChild().firstChild().firstChild().nodeValue();

    if (!errmsg.isEmpty())
        qDebug() << "SOAP Error" << errmsg;
    //qDebug() << ".";
}

void
QtShanoir::sslErrors(const QList<QSslError> & errors)
{
    if (errors.size() == 0)
        return;
    if (d->http.networkReply())
        d->http.networkReply()->ignoreSslErrors();

    for (int i = 0; i < errors.size(); ++i) {
        if (errors.at(i) == QSslError::SelfSignedCertificate || errors.at(i).error() == QSslError::SelfSignedCertificateInChain)
            d->http.networkReply()->ignoreSslErrors();
    }
}

void
QtShanoir::getResponse()
{
    // Get a reference to the response message.
    const QtSoapMessage &message = d->http.getResponse();

    // Check if the response is a SOAP Fault message
    if (message.isFault()) {
        qDebug() << message.faultString().value().toString();
        qDebug() << message.faultCode();
        qDebug() << message.toXmlString();
    }
    else {
        // Get the return value, and print the result.
        if (d->query) {
            //            qDebug() << message.toXmlString();
            if (d->query->displayResult)
                qDebug() << message.toXmlString();
            d->query->answer(message.toXmlString());
        }
    }
    d->num_message++;
    emit nextMessage();
}

void
QtShanoir::setLogin(QString key, QString ws, QString impl)
{
    //    qDebug() << QtShanoirSettings::Instance()->login() << " : " << QtShanoirSettings::Instance()->password();

    QtShanoirWsQuery* uname = new QtShanoirWsQuery(ws);
    uname->WsImpl = impl;
    uname->WsMethod = "setUsername";
    uname->WsMethodarg.push_back(qMakePair(QString("username"), QtShanoirSettings::Instance()->login()));

    QtShanoirWsQuery* pass = new QtShanoirWsQuery(ws);
    pass->WsImpl = impl;
    pass->WsMethod = "setPassword";
    pass->WsMethodarg.push_back(qMakePair(QString("dummy"), QtShanoirSettings::Instance()->password()));

    d->perWsQuery[key].push_back(uname);
    d->perWsQuery[key].push_back(pass);
}

void
QtShanoir::populateQueries()
{
    QtSoapNamespaces &registry = QtSoapNamespaces::instance();
    registry.registerNamespace("ns1", "http://impl.webservices.shanoir.org/");
    registry.registerNamespace("ns2", "http://finder.impl.webservices.shanoir.org/");

    d->perWsQuery.clear();
    {
        QString impl("http://finder.impl.webservices.shanoir.org/");

        this->setLogin("StudyFindId", "StudyFinder", impl);
        QtShanoirWsQuery* find = new QtShanoirWsQuery("StudyFinder");
        find->WsImpl = impl;
        find->WsMethod = "find";
        if (d->tree)
            QObject::connect(find, SIGNAL(response(QString)), d->tree, SLOT(parseStudy(QString)));

        QtShanoirWsQuery* errors = new QtShanoirWsQuery("StudyFinder");
        errors->WsImpl = impl;
        errors->WsMethod = "getErrorMessage";
        QObject::connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

        d->perWsQuery["StudyFindId"].push_back(find);
        d->perWsQuery["StudyFindId"].push_back(errors);
    }
}

void
QtShanoir::mrExamQuery(QString str)
{
    this->setMrExamQuery("FindMrExam", str);
    this->doQuery("FindMrExam");
}

void
QtShanoir::setMrExamQuery(QString key, QString id)
{
    //    qDebug() << "Prepare WS query for Id" << id;

    QString webs = "MrExaminationFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    d->perWsQuery[key].clear();

    this->setLogin(key, webs, impl);

    QtShanoirWsQuery* setId = new QtShanoirWsQuery(webs, impl);
    setId->WsMethod = "setSubjectIds";
    setId->WsMethodarg.push_back(qMakePair(QString("examinationSubjectIds"), QString("%1").arg(id)));

    QtShanoirWsQuery* find = new QtShanoirWsQuery(webs, impl);
    find->WsMethod = "find";
    if (d->tree)
        QObject::connect(find, SIGNAL(response(QString)), d->tree, SLOT(parseMrExamination(QString)));

    QtShanoirWsQuery* errors = new QtShanoirWsQuery(webs, impl);
    errors->WsMethod = "getErrorMessage";
    QObject::connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    d->perWsQuery[key].push_back(setId);
    d->perWsQuery[key].push_back(find);
    d->perWsQuery[key].push_back(errors);
}

void
QtShanoir::datasetQuery(QString str1, QString str2)
{
    this->setDatasetQuery("FindDataset", str1, str2);
    this->doQuery("FindDataset");
}

void
QtShanoir::setDatasetQuery(QString key, QString id, QString exId)
{
    //    qDebug() << "Prepare WS query for Id" << id << exId;
    QString webs = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";
    d->perWsQuery[key].clear();

    this->setLogin(key, webs, impl);

    QtShanoirWsQuery* setId = new QtShanoirWsQuery(webs, impl);
    setId->WsMethod = "setSubjectIds";
    setId->WsMethodarg.push_back(qMakePair(QString("mrDatasetSubjectIds"), QString("%1").arg(exId)));

    QtShanoirWsQuery* setEx = new QtShanoirWsQuery(webs, impl);
    setEx->WsMethod = "setExaminationIds";
    setEx->WsMethodarg.push_back(qMakePair(QString("mrDatasetExaminations"), QString("%1").arg(id)));

    QtShanoirWsQuery* find = new QtShanoirWsQuery(webs, impl);
    find->WsMethod = "find";
    if (d->tree)
        QObject::connect(find, SIGNAL(response(QString)), d->tree, SLOT(parseAcquisition(QString)));

    QtShanoirWsQuery* errors = new QtShanoirWsQuery(webs, impl);
    errors->WsMethod = "getErrorMessage";
    QObject::connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    //    perWsQuery[key].push_back(setId);
    d->perWsQuery[key].push_back(setEx);
    d->perWsQuery[key].push_back(find);
    d->perWsQuery[key].push_back(errors);
}

void
QtShanoir::currentId(int id)
{
    d->curId = id;
}

void
QtShanoir::find()
{
    this->clearTree();
    this->populateQueries();
    this->doQuery("StudyFindId");
}

void
QtShanoir::downloadToDir(QString directory)
{
    d->downloadDir = directory;
    d->curId = d->selectedIds.first();

    emit startDownload();
}

void
QtShanoir::download()
{
    if ((d->selectedIds.size() != 0) || !d->downloadFileName.isEmpty()) {
        // Open a QFileDialog in directory mode.
        QFileDialog * dialog = new QFileDialog(d->tree);
        dialog->setFileMode(QFileDialog::Directory);
        dialog->setOption(QFileDialog::ShowDirsOnly, true);
        dialog->setDirectory(QDir::home().dirName());
        dialog->setWindowTitle(tr("Choose datasets download directory"));
        QString directory;
        if (dialog->exec()) {
            directory = dialog->selectedFiles()[0];
        }
        dialog->close();

        if (!directory.isEmpty()) // A file has been chosen
        {
            d->downloadDir = directory;
            d->curId = d->selectedIds.first();
            //            emit getFileName();

            emit startDownload();
            //        qDebug() << d->curId;
            //        this->setFilename("getFileName", QString::number(d->curId));
            //        this->doQuery("getFileName");
            //        for (int i = 0; i < d->selectedIds.size(); i++) {
            //            this->setDownload("download", QString::number(d->selectedIds[i]));
            //            this->doQuery("download");
            //        }

        }
        delete dialog;
    }
    //    else {
    //        QMessageBox * msgBox = new QMessageBox(d->tree);
    //        msgBox->setIcon(QMessageBox::Information);
    //        msgBox->setText(tr("Please select at least one dataset to download"));
    //        msgBox->exec();
    //        delete msgBox;
    //    }

}

void
QtShanoir::callGetFileNameWS()
{
    qDebug() << "Start calling GetFilename";
    this->setFilename("getFileName", QString::number(d->curId));
    this->doQuery("getFileName");
}

void
QtShanoir::callDownloadWS()
{
    qDebug() << "Start Download";
    this->setDownload("download", QString::number(d->curId));
    this->doQuery("download");
}

void
QtShanoir::setFilename(QString key, QString id)
{
    //    d->waitForDownload = true;
    qDebug() << "Call set filename";
    d->curId = id.toInt();
    //    qDebug() << "Prepare WS query for Id" << id;
    QString webs = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";
    d->perWsQuery[key].clear();

    this->setLogin(key, webs, impl);

    QtShanoirWsQuery* setId = new QtShanoirWsQuery(webs, impl);
    setId->WsMethod = "setDatasetId";
    setId->WsMethodarg.push_back(qMakePair(QString("datasetId"), QString("%1").arg(id)));

    QtShanoirWsQuery* filename = new QtShanoirWsQuery(webs, impl);
    filename->WsMethod = "getFileName";
    QObject::connect(filename, SIGNAL(response(QString)), this, SLOT(getFileName(QString)));

    QtShanoirWsQuery* errors = new QtShanoirWsQuery(webs, impl);
    errors->WsMethod = "getErrorMessage";
    QObject::connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    d->perWsQuery[key].push_back(setId);
    d->perWsQuery[key].push_back(filename);
    //    d->perWsQuery[key].push_back(errors);
}

void
QtShanoir::getFileName(QString xmlserial)
{
    qDebug() << xmlserial;
    QDomDocument doc;
    doc.setContent(xmlserial);
    QDomNode n = doc.firstChild().firstChild().nextSibling().firstChild().firstChild();
    if (n.isElement()) {
        d->downloadFileName = n.toElement().text();
    }
    qDebug() << d->downloadFileName;
    qDebug() << "Filename Set";
    emit startDownload();
}

void
QtShanoir::setDownload(QString key, QString id)
{
    //    d->waitForDownload = true;
    d->curId = id.toInt();
    //    qDebug() << "Prepare WS query for Id" << id;
    QString webs = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";
    d->perWsQuery[key].clear();

    this->setLogin(key, webs, impl);

    QtShanoirWsQuery* setId = new QtShanoirWsQuery(webs, impl);
    setId->WsMethod = "setDatasetId";
    setId->WsMethodarg.push_back(qMakePair(QString("datasetId"), QString("%1").arg(id)));

    QtShanoirWsQuery* download = new QtShanoirWsQuery(webs, impl);
    download->WsMethod = "download";
    QObject::connect(download, SIGNAL(response(QString)), this, SLOT(download(QString)));

    QtShanoirWsQuery* errors = new QtShanoirWsQuery(webs, impl);
    errors->WsMethod = "getErrorMessage";
    QObject::connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    d->perWsQuery[key].push_back(setId);
    d->perWsQuery[key].push_back(download);
    d->perWsQuery[key].push_back(errors);
}

void
QtShanoir::download(QString xmlserial)
{
    //    qDebug() << xmlserial;
    const QtSoapMessage &message = d->http.getResponse();
    const QByteArray& bin = message.getBinary();
    if (bin.isEmpty()) {
        qDebug() << "Binary is empty";
        return;
    }
    //    QFile dFile(d->downloadDir + QDir::separator() + d->downloadFileName);
    QFile dFile(d->downloadDir + QDir::separator() + QString::number(d->curId) + ".nii");

    dFile.open(QFile::WriteOnly);
    dFile.write(bin);
    dFile.close();

    emit
    downloadFinished(dFile.fileName());

    qDebug() << "Download finished";

    if (d->progress)
        d->progress->download->setValue(0);
    //    d->waitForDownload = false;
}

void
QtShanoir::updateSelected(QList<int> listId)
{
    d->selectedIds = listId;
}

void
QtShanoir::queryFinished()
{
    if (d->progress)
        d->progress->download->setValue(0);
}

void
QtShanoir::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    //    d->progress->download->setMaximum(bytesTotal);
    d->progress->download->setValue(100 * bytesReceived / bytesTotal);
    qApp->processEvents();
}

