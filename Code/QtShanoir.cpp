/*
 * QtShanoir.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoir.h>
#include <QtShanoirSettings.h>
#include <QtShanoirTreeWidget.h>
#include <QtShanoirProgressWidget.h>
#include <QtShanoirSettingsWidget.h>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

#include "QtShanoirWebService.h"
#include "QtShanoirUploadWidget.h"

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

QtShanoir * QtShanoir::_instance = 0;

class QtShanoirPrivate
{
    public:
        QtShanoirTreeWidget * tree;
        QtShanoirProgressWidget * progress;
        QtShanoirUploadWidget * upload;
        int curId;
        QList<int> selectedIds;
        QString downloadDir;
        QString downloadFileName;
        bool downloadMetadata;
        QList<QString> filesToUploadList;

        QRegExp studyNameFilter;
        QString dateFilter;
        QRegExp patientNameFilter;
        QRegExp datasetNameFilter;
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
    d->downloadMetadata = false;

    d->studyNameFilter.setPattern("*");
    d->patientNameFilter.setPattern("*");
    d->dateFilter = "";
    d->datasetNameFilter.setPattern("*");

    d->studyNameFilter.setPatternSyntax(QRegExp::Wildcard);
    d->patientNameFilter.setPatternSyntax(QRegExp::Wildcard);
    d->datasetNameFilter.setPatternSyntax(QRegExp::Wildcard);
}

void
QtShanoir::setDateFilter(QString text)
{

    QDate tmpDate = QDate::fromString(text, "dd/MM/yyyy");
    d->dateFilter = tmpDate.toString(Qt::ISODate);

}

void
QtShanoir::setStudyNameFilter(QString text)
{
    if (text != "")
        d->studyNameFilter.setPattern(text);
    else
        d->studyNameFilter.setPattern("*");
}

void
QtShanoir::setPatientNameFilter(QString text)
{
    if (text != "")
        d->patientNameFilter.setPattern(text);
    else
        d->patientNameFilter.setPattern("*");
}

void
QtShanoir::setDatasetNameFilter(QString text)
{
    if (text != "")
        d->datasetNameFilter.setPattern(text);
    else
        d->datasetNameFilter.setPattern("*");
}

void
QtShanoir::setDownloadFilename(QString filename)
{
    d->downloadFileName = filename;
}

void
QtShanoir::setDownloadMetadata(int state)
{
    d->downloadMetadata = (state == Qt::Checked);
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
    QObject::connect(this, SIGNAL(startUpload()), this, SLOT(callUpload()));
}

void
QtShanoir::attachTreeWidget(QtShanoirTreeWidget * widget)
{
    d->tree = widget;
    if (d->tree) {
        QObject::connect(d->tree, SIGNAL(mrExamQuery(QString)), this, SLOT(findExam(QString)));
        QObject::connect(d->tree, SIGNAL(datasetQuery(QString,QString)), this, SLOT(findDataset(QString,QString)));
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
QtShanoir::attachUploadWidget(QtShanoirUploadWidget * widget)
{
    d->upload = widget;
    if (d->upload && d->tree)
    {
        QObject::connect(d->tree, SIGNAL(selected(QList<int>)), d->upload, SLOT(updateInputDatasetComboBox(QList<int>)));
        QObject::connect(this, SIGNAL(processingMap(QMap<int, QString>)), d->upload, SLOT(updateProcessingComboBox(QMap<int, QString>)));
    }
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

    QString ws = "StudyFinder";
    QString impl("http://finder.impl.webservices.shanoir.org/");

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setStudyName", impl, QStringList() << "studyName", QStringList() << d->studyNameFilter.pattern());
    QString xmlserial = QtShanoirWebService::Query(ws, "find", impl, QStringList(), QStringList());

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    d->tree->parseStudy(xmlserial, d->patientNameFilter);

    this->getProcessingListId();
}

void
QtShanoir::findExam(QString str)
{

    QString ws = "MrExaminationFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setSubjectIds", impl, QStringList() << "examinationSubjectIds", QStringList() << str);
    QString xmlserial = QtShanoirWebService::Query(ws, "find", impl, QStringList(), QStringList());

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    d->tree->parseMrExamination(xmlserial, d->dateFilter);

}

void
QtShanoir::findDataset(QString examId, QString subjectId)
{
    QString ws = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setSubjectIds", impl, QStringList() << "mrDatasetSubjectIds", QStringList() << subjectId);
    QtShanoirWebService::Query(ws, "setExaminationIds", impl, QStringList() << "mrDatasetExaminations", QStringList() << examId);
    QString xmlserial = QtShanoirWebService::Query(ws, "find", impl, QStringList(), QStringList());

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    d->tree->parseAcquisition(xmlserial, d->datasetNameFilter);
}

void
QtShanoir::getDatasetFilename(QString datasetId)
{
    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    d->curId = datasetId.toInt();

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId);

    QString xmlserial = QtShanoirWebService::Query(ws, "getFileName", impl, QStringList(), QStringList());
    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());

    QDomDocument doc;
    doc.setContent(xmlserial);
    QDomNode n = doc.firstChild().firstChild().nextSibling().firstChild().firstChild();
    if (n.isElement()) {
        d->downloadFileName = n.toElement().text();
    }
}

void
QtShanoir::getProcessingListId()
{
    QString ws = "ReferenceLister";
    QString impl = "http://impl.webservices.shanoir.org/";

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());

    QString xmlserial = QtShanoirWebService::Query(ws, "listReferenceValue", impl, QStringList() << "arg0", QStringList() << "DatasetProcessing");

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());

    QMap<int,QString> map;
    int id;
    QString label;
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QDomNode n = doc.firstChild().firstChild();
    while (!n.isNull()) {
        id = n.firstChildElement("id").firstChild().toText().nodeValue().toInt();
        label = n.firstChildElement("label").firstChild().toText().nodeValue();
        map.insert(id ,label);
        n = n.nextSibling();
    }
    emit processingMap(map);
}

void
QtShanoir::downloadMetadata(QString datasetId)
{
    QString ws = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setMrDatasetIds", impl, QStringList() << "mrDatasetIds", QStringList() << datasetId);
    QString xmlserial = QtShanoirWebService::Query(ws, "find", impl, QStringList(), QStringList());

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());

    QDomDocument doc;
    doc.setContent(xmlserial);
    QFile dFile(d->downloadDir + QDir::separator() + d->downloadFileName.replace(".nii", ".xml").replace(".zip", ".xml"));
    dFile.open(QFile::WriteOnly);
    dFile.write(doc.toString().toUtf8().data());
    dFile.close();

}

void
QtShanoir::downloadDataset(QString datasetId)
{
    this->getDatasetFilename(datasetId);
    d->curId = datasetId.toInt();

    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    d->curId = datasetId.toInt();

    QtShanoirWebService::Query(ws, "setUsername", impl, QStringList() << "username", QStringList() << QtShanoirSettings::Instance()->login());
    QtShanoirWebService::Query(ws, "setPassword", impl, QStringList() << "dummy", QStringList() << QtShanoirSettings::Instance()->password());
    QtShanoirWebService::Query(ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId);

    QByteArray bin = QtShanoirWebService::BinaryQuery(ws, "download", impl, QStringList(), QStringList());

    QtShanoirWebService::Query(ws, "getErrorMessage", impl, QStringList(), QStringList());
    if (bin.isEmpty()) {
        qDebug() << "Binary is empty";
        return;
    }

    QFile dFile(d->downloadDir + QDir::separator() + (d->downloadFileName.isEmpty() ? QString("%1.nii").arg(d->curId) : d->downloadFileName));

    dFile.open(QFile::WriteOnly);
    dFile.write(bin);
    dFile.close();

    if (d->downloadMetadata)
        this->downloadMetadata(datasetId);

    if (dFile.fileName().contains(".zip")) {
        // Decompression using QuaZIP
        QuaZip zipFile(dFile.fileName());
        zipFile.open(QuaZip::mdUnzip);
        QuaZipFileInfo info;
        QuaZipFile file(&zipFile);

        for (bool more = zipFile.goToFirstFile(); more; more = zipFile.goToNextFile()) {
            zipFile.getCurrentFileInfo(&info);
            file.open(QIODevice::ReadOnly);
            QString name = file.getActualFileName();

            QString outFileName = d->downloadDir + QDir::separator() + name;
            QFile out(outFileName);
            out.open(QIODevice::WriteOnly);

            char buf[4096];
            char c;
            int len = 0;
            while (file.getChar(&c)) {
                buf[len++] = c;
                if (len >= 4096) {
                    out.write(buf, len);
                    len = 0;
                }
            }
            if (len > 0) {
                out.write(buf, len);
            }
            out.close();

            if (name.contains(".nii"))
                emit downloadFinished(outFileName);

            file.close();
        }
        zipFile.close();
    }
    else
        emit downloadFinished(dFile.fileName());
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
    if (d->progress) {
        d->progress->download->setValue(0);
        d->progress->download->show();
    }
    for (int i = 0; i < d->selectedIds.size(); i++) {
        d->curId = d->selectedIds.at(i);
        this->downloadDataset(QString::number(d->curId));
        if (d->progress)
            d->progress->download->setValue((int) (100.00 * (i + 1) / d->selectedIds.size()));
    }
    if (d->progress)
        d->progress->download->hide();
    qDebug() << "Download finished";
}

void
QtShanoir::upload()
{
    d->filesToUploadList.clear();
    QFileDialog dialog(d->tree);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::home().dirName());
    dialog.setWindowTitle("Open filename");
    dialog.setNameFilter(tr("Images (*.nii *.vtk)"));

    if (dialog.exec()) {
        d->filesToUploadList = dialog.selectedFiles();
        emit startUpload();
    }
    dialog.close();
}

void
QtShanoir::callUpload()
{
    this->getProcessingListId();
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

