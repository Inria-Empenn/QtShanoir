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
        int curId;
        QList<int> selectedIds;
        QString downloadDir;
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
QtShanoir::init()
{
    if (d->tree)
        QtShanoirSettings::Instance();
    QObject::connect(this, SIGNAL(startDownload()), this, SLOT(callDownload()));
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
    }
}

void
QtShanoir::attachProgressWidget(QtShanoirProgressWidget * widget)
{
    d->progress = widget;
    if (d->progress)
        d->progress->download->hide();
}

void
QtShanoir::getError(QString xmlserial)
{
    QDomDocument doc;
    doc.setContent(xmlserial);

    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    QString errmsg = doc.firstChild().firstChild().firstChild().nodeValue();

    if (!errmsg.isEmpty())
        qDebug() << "SOAP Error" << errmsg;
}

void
QtShanoir::populate()
{
    QtSoapNamespaces &registry = QtSoapNamespaces::instance();
    registry.registerNamespace("ns1", "http://impl.webservices.shanoir.org/");
    registry.registerNamespace("ns2", "http://finder.impl.webservices.shanoir.org/");

    QString impl("http://finder.impl.webservices.shanoir.org/");

    WebServices::Query("StudyFinder", "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query("StudyFinder", "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QString xmlserial = WebServices::Query("StudyFinder", "find", impl, QStringList(), QStringList());

    WebServices::Query("StudyFinder", "getErrorMessage", impl, QStringList(), QStringList());
    d->tree->parseStudy(xmlserial);
}

void
QtShanoir::mrExamQuery(QString str)
{

    QString ws = "MrExaminationFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setSubjectIds", impl, QStringList() << "examinationSubjectIds", QStringList() << str);
    QString xmlserial = WebServices::Query(ws, "find", impl, QStringList(), QStringList());

    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    d->tree->parseMrExamination(xmlserial);

}

void
QtShanoir::datasetQuery(QString examId, QString subjectId)
{
    QString ws = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setSubjectIds", impl, QStringList() << "mrDatasetSubjectIds", QStringList() << subjectId);
    WebServices::Query(ws, "setExaminationIds", impl, QStringList() << "mrDatasetExaminations", QStringList() << examId);
    QString xmlserial = WebServices::Query(ws, "find", impl, QStringList(), QStringList());

    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
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
    this->populate();
}

void
QtShanoir::downloadToDir(QString directory)
{
    d->downloadDir = directory;
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
            emit startDownload();
        }
        delete dialog;
    }
}

void
QtShanoir::callDownload()
{
    qDebug() << "Start Download";
    if (d->progress)
        d->progress->download->show();
    for (int i = 0; i < d->selectedIds.size(); i++) {
        d->curId = d->selectedIds.at(i);
        this->setDownload(QString::number(d->curId));
        if (d->progress)
            d->progress->download->setValue((int) (100.00 * (i + 1) / d->selectedIds.size()));
    }
    if (d->progress)
        d->progress->download->hide();
    qDebug() << "Download finished";
}

void
QtShanoir::setFilename(QString datasetId)
{
    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    qDebug() << "Call set filename";
    d->curId = datasetId.toInt();

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId);

    QString xmlserial = WebServices::Query(ws, "getFileName", impl, QStringList(), QStringList());
    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());

    QDomDocument doc;
    doc.setContent(xmlserial);
    QDomNode n = doc.firstChild().firstChild().nextSibling().firstChild().firstChild();
    if (n.isElement()) {
        d->downloadFileName = n.toElement().text();
    }
}

void
QtShanoir::setDownload(QString datasetId)
{
    setFilename(datasetId);
    d->curId = datasetId.toInt();

    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    d->curId = datasetId.toInt();

    WebServices::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    WebServices::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    WebServices::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId);

    QByteArray bin = WebServices::BinaryQuery(ws, "download", impl, QStringList(), QStringList());

    WebServices::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    if (bin.isEmpty()) {
        qDebug() << "Binary is empty";
        return;
    }
    QFile dFile(d->downloadDir + QDir::separator() + (d->downloadFileName.isEmpty() ? QString("%1.nii").arg(d->curId) : d->downloadFileName));

    dFile.open(QFile::WriteOnly);
    dFile.write(bin);
    dFile.close();
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
    d->progress->download->setValue(100 * bytesReceived / bytesTotal);
    qApp->processEvents();
}

