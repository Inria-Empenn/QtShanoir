/*
 * QtShanoir.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoir.h>
//#include <QtShanoirWsQuery.h>
#include <QtShanoirSettings.h>
#include <QtShanoirTreeWidget.h>
#include <QtShanoirProgressWidget.h>
#include <QtShanoirSettingsWidget.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

#include "wsquery.h"

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
//    const QtShanoirWsQuery * query;
    // Fill the following map with the properly set up query
//    QMap<QString, QList<QtShanoirWsQuery*> > perWsQuery;
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

        //        QObject::connect(this, SIGNAL(nextMessage()), this, SLOT(sendMessage()));
        //        QObject::connect(&(d->http), SIGNAL(responseReady()), this, SLOT(getResponse()));
        //        d->req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);
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
//    d->query = 0;
//    if (d->num_message < d->perWsQuery[d->ws].count())
//        d->query = d->perWsQuery[d->ws].at(d->num_message);
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

void QtShanoir::populateQueries()
{
    QtSoapNamespaces &registry = QtSoapNamespaces::instance();
    registry.registerNamespace("ns1", "http://impl.webservices.shanoir.org/");
    registry.registerNamespace("ns2", "http://finder.impl.webservices.shanoir.org/");


    QString impl("http://finder.impl.webservices.shanoir.org/");
    WebServices::Query("StudyFinder", "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query("StudyFinder", "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QString xmlserial = WebServices::Query("StudyFinder", "find", impl, QStringList(), QStringList() );
    WebServices::Query("StudyFinder", "getErrorMessage", impl, QStringList(), QStringList() );
    d->tree->parseStudy(xmlserial);
}

void QtShanoir::mrExamQuery(QString str)
{

    QString ws = "MrExaminationFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setSubjectIds", impl, QStringList() << "examinationSubjectIds", QStringList() <<str);
    QString xmlserial = WebServices::Query(ws, "find", impl, QStringList(), QStringList() );
    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList() );
    d->tree->parseMrExamination(xmlserial);


}



void
QtShanoir::datasetQuery(QString str1, QString str2)
{
    //    this->setDatasetQuery("FindDataset", str1, str2);
    //    this->doQuery("FindDataset");

    QString ws = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setSubjectIds", impl,
                       QStringList() << "mrDatasetSubjectIds",
                       QStringList() << str2);

    WebServices::Query(ws, "setExaminationIds", impl,
                       QStringList() << "mrDatasetExaminations",
                       QStringList() << str1);

    QString xmlserial = WebServices::Query(ws, "find", impl, QStringList(), QStringList() );
    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList() );
    d->tree->parseAcquisition(xmlserial);
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
//    this->doQuery("StudyFindId");
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
// this->doQuery("getFileName");
}

void
QtShanoir::callDownloadWS()
{
    qDebug() << "QtShanoir Start Download";
    this->setDownload("download", QString::number(d->curId));
//    this->doQuery("download");
}

void
QtShanoir::setFilename(QString key, QString id)
{
    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    //    d->waitForDownload = true;
    qDebug() << "Call set filename";
    d->curId = id.toInt();
    //    qDebug() << "Prepare WS query for Id" << id;


    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << id);


    QString xmlserial = WebServices::Query(ws, "getFileName", impl, QStringList(), QStringList() );
    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList() );
    getFileName(xmlserial);
}

void
QtShanoir::getFileName(QString xmlserial)
{
//    qDebug() << xmlserial;
    QDomDocument doc;
    doc.setContent(xmlserial);
    QDomNode n = doc.firstChild().firstChild().nextSibling().firstChild().firstChild();
    if (n.isElement()) {
        d->downloadFileName = n.toElement().text();
    }
//    qDebug() << d->downloadFileName;
//    qDebug() << "Filename Set";
//    emit startDownload();
}

void
QtShanoir::setDownload(QString key, QString id)
{

    qDebug() << "Setting download" << key << id;

    setFilename(key, id);
    //    d->waitForDownload = true;
    d->curId = id.toInt();
    //    qDebug() << "Prepare WS query for Id" << id;

    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    //    d->waitForDownload = true;
    qDebug() << "Call set filename";
    d->curId = id.toInt();
    //    qDebug() << "Prepare WS query for Id" << id;


    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << id);


    QByteArray bin = WebServices::BinaryQuery(ws, "download", impl, QStringList(), QStringList() );

    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList() );

    if (bin.isEmpty()) {
        qDebug() << "Binary is empty";
        return;
    }
    QFile dFile(d->downloadDir + QDir::separator() + (d->downloadFileName.isEmpty() ? QString("%1.nii").arg(d->curId) :  d->downloadFileName));
//    QFile dFile(d->downloadDir + QDir::separator() + QString::number(d->curId) + ".nii");

    dFile.open(QFile::WriteOnly);
    dFile.write(bin);
    dFile.close();

    qDebug() << "Download finished";

    if (d->progress)
        d->progress->download->setValue(0);
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

