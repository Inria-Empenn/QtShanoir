#include "QtShanoir.h"
#include "ui_qtshanoir.h"

#include <iostream>

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
#include <QMenu>
#include "QtShanoirConfiguration.h"

QtShanoir::QtShanoir(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QtShanoir)
{
    ui->setupUi(this);

    setWindowTitle("Shanoir Download");

    ico_shanoir = new QIcon(":/icones/shanoir.png");
    ico_study = new QIcon(":/icones/study.png");
    ico_subject = new QIcon(":/icones/subject.png");
    ico_exam = new QIcon(":/icones/exam.png");
    ico_acq = new QIcon(":/icones/acq.png");


    ui->toolButton->hide();
    ui->label->hide();

    QFile in(QDir::homePath()+"/.shanoir/server.properties");
    if (in.open(QFile::ReadOnly))
    {
        QTextStream f(&in);
        QMap<QString,QString> settings;
        while (!f.atEnd())
        {
            QString line = f.readLine();
            QStringList pair = line.split("=",QString::SkipEmptyParts);
            settings[pair.at(0)] = pair.at(1);
        }

        user = settings["user"].trimmed();
        password = settings["password"].trimmed();
        host = settings["host"].trimmed();
        port = settings["port"].trimmed();
        truststore = settings["truststore"].trimmed();
    } else
        setConfiguration();

    populateQueries();

    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
    req.sslConfiguration().setPeerVerifyMode(QSslSocket::VerifyNone);

    connect(this, SIGNAL(nextMessage()), this, SLOT(sendMessage()));

    // QString wservice = "StudyFinder";
    doQuery("StudyFindId");
}

void QtShanoir::prepareMessage()
{
    query = 0;

    //    qDebug() << perWsQuery[ws].count();

    if (num_message < perWsQuery[ws].count())
        query = perWsQuery[ws].at(num_message);
    if (!query) ui->infos->setText("");

}

void QtShanoir::setConfiguration()
{
    ShanoirServerParameters dia(this);
    dia.exec();

    dia.getParameters(user, password, host, port);
    QFile set(QDir::homePath()+"/.shanoir/server.properties");
    QDir dir(QDir::homePath());  dir.mkdir(".shanoir");
    if (!set.open(QFile::WriteOnly)) QMessageBox::warning(this, "Write Error", QString("Properties were not written to file:\n %1").arg(QDir::homePath()+"/.shanoir/server.properties"));

    QTextStream out(&set);
    out << "user="<<user <<"\r\n";
    out << "password="<<password << "\r\n";
    out << "host="<<host<< "\r\n";
    out << "port="<<port<< "\r\n";
    out << QString("truststore=%1/.shanoir/neurinfo.truststore\r\n").arg(QDir::homePath());
    set.close();
}


void QtShanoir::sendMessage()
{
    prepareMessage();
    if (!query) return;

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
    http.submitRequest(req, request, "//Shanoir-Shanoir/"+query->WebService);

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

void QtShanoir::doQuery(QString ws)
{
    this->ws = ws;

    num_message = 0;
    emit sendMessage();
}


void QtShanoir::getError(QString xmlserial)
{
    //    qDebug() << xmlserial;

    QDomDocument doc;
    doc.setContent(xmlserial);

    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    QString errmsg =  doc.firstChild().firstChild().firstChild().nodeValue();

    if (!errmsg.isEmpty()) qDebug() << "SOAP Error" << errmsg;
    qDebug() << ".";
}



void	QtShanoir::sslErrors ( const QList<QSslError> & errors )
{
    if (errors.size() == 0) return;
    if (http.networkReply())
        http.networkReply()->ignoreSslErrors();

    for (int i = 0; i < errors.size(); ++i)
    {
        if (errors.at(i) == QSslError::SelfSignedCertificate || errors.at(i).error() == QSslError::SelfSignedCertificateInChain)
            http.networkReply()->ignoreSslErrors();
        /*else
        {
            qDebug() << errors.at(i).error() << errors.at(i).errorString();
        }
        qDebug() << errors.at(i).error() << errors.at(i).errorString();
        */
    }
}

QtShanoir::~QtShanoir()
{
    delete ui;
}

void QtShanoir::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QtShanoir::getResponse()
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
    else {
        // Get the return value, and print the result.
        //   const QtSoapType &response = message.returnValue();
        /*        qDebug("%s has a population of %s (last updated at %s)",
               response["Country"].value().toString().toLatin1().constData(),
               response["Pop"].value().toString().toLatin1().constData(),
               response["Date"].value().toString().toLatin1().constData()); */
        if (query)
        {
            if (query->displayResult)
                qDebug() << message.toXmlString();
            query->answer(message.toXmlString());
        }
        //        lock = false;
    }
    num_message++;
    emit nextMessage();
    //  qApp->quit();
}


void QtShanoir::on_actionQuit_triggered()
{
    qApp->quit();
}


void QtShanoir::setLogin(QString key, QString ws, QString impl)
{
    WsQuery* uname = new WsQuery(ws);
    //    qDebug() << ws;
    uname->WsImpl = impl;
    uname->WsMethod="setUsername";
    uname->WsMethodarg.push_back(qMakePair(QString("username"), user));

    WsQuery* pass = new WsQuery(ws);
    pass->WsImpl = impl;
    pass->WsMethod="setPassword";
    pass->WsMethodarg.push_back(qMakePair(QString("dummy"), password));

    perWsQuery[key].push_back(uname);
    perWsQuery[key].push_back(pass);
}

void QtShanoir::populateQueries()
{
    QtSoapNamespaces &registry = QtSoapNamespaces::instance();
    registry.registerNamespace("ns1", "http://impl.webservices.shanoir.org/");
    registry.registerNamespace("ns2", "http://finder.impl.webservices.shanoir.org/");

    perWsQuery.clear();
    {
        QString impl("http://finder.impl.webservices.shanoir.org/");

        setLogin("StudyFindId", "StudyFinder", impl);
        WsQuery* find = new WsQuery("StudyFinder");
        find->WsImpl = impl;
        find->WsMethod="find";
        connect(find, SIGNAL(response(QString)), this, SLOT(parseStudy(QString)));

        WsQuery* errors = new WsQuery("StudyFinder");
        errors->WsImpl = impl;
        errors->WsMethod="getErrorMessage";
        connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

        perWsQuery["StudyFindId"].push_back(find);
        perWsQuery["StudyFindId"].push_back(errors);

        //   exit(0);
    }
}


void QtShanoir::parseStudy(QString xmlserial)
{
    qDebug() << "Deserialize data from signal";
    //    qDebug() << xmlserial;
    QDomDocument doc;
    //  doc.firstChild().firstChild().parentNode(
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem *root =  this->ui->treeWidget->invisibleRootItem();
    QTreeWidgetItem* shanoir = new QTreeWidgetItem();
    root->addChild(shanoir);

//    shanoir
    shanoir->setText(0, QString("Shanoir (%1)").arg(host));
    shanoir->setToolTip(0, QString("User:%1 (port: %2)").arg(user).arg(port));
    shanoir->setExpanded(true);
    shanoir->setIcon(0, *ico_shanoir);
    // list the study by name + id
    QDomNode n = doc.firstChild().firstChild();

    while (!n.isNull())
    {
        if (n.toElement().tagName() == "return")
        {
            QTreeWidgetItem * study = new QTreeWidgetItem;
            study->setText(0, QString("%1").arg(n.firstChildElement("name").firstChild().toText().nodeValue()));
            study->setToolTip(0, QString("Study Id : %1").arg(n.firstChildElement("id").firstChild().toText().nodeValue()));
            study->setIcon(0, *ico_study);
            shanoir->addChild(study);
            // find patients for each study
            QDomNode rel = n.firstChildElement("relSubjectStudyList");

            while (!rel.isNull())
            {
                QDomElement el = rel.toElement();
                //                qDebug() << el.tagName();
                QTreeWidgetItem* sub = new QTreeWidgetItem;
                sub->setText(0, QString("%1").arg(
                        el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue()));
                sub->setToolTip(0, QString("Sex: %2 BirthDate: %3 (id: %1)")
                                .arg(el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue())
                                .arg(el.firstChildElement("subject").firstChildElement("refSex").firstChild().nodeValue())
                                .arg(QDate::fromString(el.firstChildElement("subject").firstChildElement("birthDate").firstChild().nodeValue(), Qt::ISODate)
                                     .toString(Qt::SystemLocaleShortDate))
                                );

                sub->setData(0, QTreeWidgetItem::UserType+3, (el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()));
                sub->setIcon(0, *ico_subject);

                sub->setCheckState(0, Qt::Unchecked);

                study->addChild(sub);

                rel = rel.nextSiblingElement("relSubjectStudyList");
            }
        }
        n = n.nextSibling();
    }
    //    ui->treeWidget->itemClicked();
    doc.clear();
}




//void WsQuery::answer(QString str) const
//{
//    emit response(str);
//}


void QtShanoir::setMrExamQuery(QString key, QString id)
{
    qDebug() << "Prepare WS query for Id" << id;

    QString webs = "MrExaminationFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    perWsQuery[key].clear();

    setLogin(key, webs, impl);

    WsQuery* setId = new WsQuery(webs, impl);
    setId->WsMethod = "setSubjectIds";
    setId->WsMethodarg.push_back(qMakePair(QString("examinationSubjectIds"),QString("%1").arg(id)));

    WsQuery* find = new WsQuery(webs, impl);
    find->WsMethod="find";
    connect(find, SIGNAL(response(QString)), this, SLOT(parseMrExamination(QString)));

    WsQuery* errors = new WsQuery(webs, impl);
    errors->WsMethod="getErrorMessage";
    connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    perWsQuery[key].push_back(setId);
    perWsQuery[key].push_back(find);
    perWsQuery[key].push_back(errors);
}

void QtShanoir::setDatasetQuery(QString key, QString id, QString exId)
{
    qDebug() << "Prepare WS query for Id" << id << exId;
    QString webs = "MrDatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";
    perWsQuery[key].clear();

    setLogin(key, webs, impl);


    WsQuery* setId = new WsQuery(webs, impl);
    setId->WsMethod = "setSubjectIds";
    setId->WsMethodarg.push_back(qMakePair(QString("mrDatasetSubjectIds"),QString("%1").arg(exId)));

    WsQuery* setEx = new WsQuery(webs, impl);
    setEx->WsMethod = "setExaminationIds";
    setEx->WsMethodarg.push_back(qMakePair(QString("mrDatasetExaminations"),QString("%1").arg(id)));


    WsQuery* find = new WsQuery(webs, impl);
    find->WsMethod="find";
    connect(find, SIGNAL(response(QString)), this, SLOT(parseAcquisition(QString)));

    WsQuery* errors = new WsQuery(webs, impl);
    errors->WsMethod="getErrorMessage";
    connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    //    perWsQuery[key].push_back(setId);
    perWsQuery[key].push_back(setEx);
    perWsQuery[key].push_back(find);
    perWsQuery[key].push_back(errors);
}


void QtShanoir::on_treeWidget_itemClicked(QTreeWidgetItem* item, int )
{
    // Item has user defined datatype && the data was not fetched yet
    if (!item->data(0, QTreeWidgetItem::UserType+3).isNull() && item->childCount() == 0)
    {
        setMrExamQuery("FindMrExam", item->data(0, QTreeWidgetItem::UserType+3).toString());
        doQuery("FindMrExam");
    }

    if (!item->data(0, QTreeWidgetItem::UserType+4).isNull() && item->childCount() == 0)
    {
        setDatasetQuery("FindDataset", item->data(0, QTreeWidgetItem::UserType+4).toString(),
                        item->data(0, QTreeWidgetItem::UserType+5).toString()
                        );
        doQuery("FindDataset");
    }

    if (!item->data(0, QTreeWidgetItem::UserType+6).isNull())
    {
        ui->label->setText(QString("%1 - %2").arg(item->text(0)).arg(item->data(0, QTreeWidgetItem::UserType+6).toString()));
        curId = item->data(0, QTreeWidgetItem::UserType+6).toString().toInt();

        ui->label->show();
        ui->toolButton->show();
    }

}

void QtShanoir::parseMrExamination(QString xmlserial)
{
 //  qDebug() << "Deserialize the MrDataset"  << xmlserial;

    QDomDocument doc;
    //  doc.firstChild().firstChild().parentNode(
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem* sub = ui->treeWidget->selectedItems().front();
    QString id = sub->data(0, QTreeWidgetItem::UserType+3).toString();
    qDebug() << id << sub->text(0);

    QDomNode el =  doc.firstChild().firstChildElement("return");
    if (el.isNull())
    {
        QFont f = sub->font(0);
        f.setStrikeOut(true);
        sub->setFont(0, f);
    }
    while (!el.isNull())
    {
        //        qDebug() << "!";
        QTreeWidgetItem* exam = new QTreeWidgetItem;
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("comment").firstChild().nodeValue())
                      .arg(QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate))
                      );
        qDebug() << exam->text(0);

        exam->setData(0, QTreeWidgetItem::UserType+4, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setData(0, QTreeWidgetItem::UserType+5, id);
        exam->setIcon(0, *ico_exam);

        exam->setCheckState(0, Qt::Unchecked);

        sub->addChild(exam);
        el = el.nextSiblingElement("return");
    }
    sub->setExpanded(true);

    doc.clear();
}


void QtShanoir::parseAcquisition(QString xmlserial)
{
    //    qDebug() << "Deserialize the MrDataset"  << xmlserial;

    QDomDocument doc;
    //  doc.firstChild().firstChild().parentNode(
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe
    //    qDebug() << doc.toString();

    QTreeWidgetItem* sub = ui->treeWidget->selectedItems().front();

    QDomNode el =  doc.firstChild().firstChildElement("mrDatasetResultList");

    if (el.isNull())
    {
        QFont f = sub->font(0);
        f.setStrikeOut(true);
        sub->setFont(0, f);
    }

    while (!el.isNull())
    {
        QTreeWidgetItem* exam = new QTreeWidgetItem;

        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("name").firstChild().nodeValue())
                      .arg(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate))
                      );
        exam->setToolTip(0, QString("%1 - (TR %2, TE %3, FA %4) ").arg(el.firstChildElement("comment").firstChild().nodeValue())
                         .arg(el.firstChildElement("repetitionTime").firstChildElement("repetitionTimeValue").firstChild().nodeValue())
                         .arg(el.firstChildElement("echoTime").firstChildElement("echoTimeValue").firstChild().nodeValue())
                         .arg(el.firstChildElement("flipAngle").firstChildElement("flipAngleValue").firstChild().nodeValue())

                         );

        exam->setData(0, QTreeWidgetItem::UserType+6, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setIcon(0, *ico_acq);

        exam->setCheckState(0, Qt::Unchecked);

        sub->addChild(exam);
        el = el.nextSiblingElement("mrDatasetResultList");
    }
    sub->setExpanded(true);
    doc.clear();
}


void QtShanoir::download(QString xmlserial)
{
    qDebug() << xmlserial;
    const QtSoapMessage &message = http.getResponse();
    const QByteArray& bin = message.getBinary();
    if (bin.isEmpty()) return;

    QString t = ui->label->text().replace(" ", "_").replace("/","_").replace("\\","_") + ".nii";
    qDebug() << ui->label->text() << t;
    ui->label->setText("");

    QString defFileName;
#ifdef Q_WS_MAC
    defFileName = QDir::homePath()+"/Documents/"+t;
#elif Q_WS_WIN
    defFileName = QDir::homePath()+tr("\\Mes Documents\\")+t;
#else
    defFileName = QDir::homePath()+"/Documents/"+t;
#endif

    QString fname = QFileDialog::getSaveFileName(this, "Save downloaded file", defFileName, "Nifti (*.nii);;");
    if (fname.isEmpty()) return;
    QFile file(fname);

    if (!file.open(QFile::WriteOnly))
        QMessageBox::warning(this, "Warning", QString("File not writable %1").arg(fname));

    file.write(bin);
    file.close();

    ui->toolButton->hide();
    ui->label->hide();

}

void QtShanoir::setDownload(QString key, QString id)
{
    qDebug() << "Prepare WS query for Id" << id;
    QString webs = "Downloader";
    QString impl ="http://impl.webservices.shanoir.org/";
    perWsQuery[key].clear();

    setLogin(key, webs, impl);

    WsQuery* setId = new WsQuery(webs, impl);
    setId->WsMethod = "setDatasetId";
    setId->WsMethodarg.push_back(qMakePair(QString("datasetId"),QString("%1").arg(id)));

    WsQuery* download = new WsQuery(webs, impl);
    download->WsMethod="download";
    connect(download, SIGNAL(response(QString)), this, SLOT(download(QString)));

    WsQuery* errors = new WsQuery(webs, impl);
    errors->WsMethod="getErrorMessage";
    connect(errors, SIGNAL(response(QString)), this, SLOT(getError(QString)));

    perWsQuery[key].push_back(setId);
    perWsQuery[key].push_back(download);
    perWsQuery[key].push_back(errors);
}


void QtShanoir::on_toolButton_clicked()
{
    // do download
    if (ui->label->text().isEmpty()) return;

    setDownload("download", QString("%1").arg(curId));
    doQuery("download");

}


void QtShanoir::downloadProgress(qint64 bytesReceived, qint64 bytesTotal )
{
    ui->download->setMaximum(bytesTotal);
    ui->download->setValue(bytesReceived);
}

void QtShanoir::uploadProgress(qint64 bytesReceived, qint64 bytesTotal )
{
    //    ui->upload->setMaximum(bytesTotal);
    //    ui->upload->setValue(bytesReceived);
}


void QtShanoir::on_treeWidget_itemDoubleClicked(QTreeWidgetItem* item, int )
{
    if (item->text(0) ==  QString("Shanoir (%1)").arg(host))
    {
        ShanoirServerParameters dia(this);
        dia.exec();

        dia.getParameters(user, password, host, port);
        QFile set(QDir::homePath()+"/.shanoir/server.properties");
        QDir dir(QDir::homePath());  dir.mkdir(".shanoir");
        if (!set.open(QFile::WriteOnly)) QMessageBox::warning(this, "Write Error", QString("Properties were not written to file:\n %1").arg(QDir::homePath()+"/.shanoir/server.properties"));

        QTextStream out(&set);
        out << "user="<<user <<"\r\n";
        out << "password="<<password << "\r\n";
        out << "host="<<host<< "\r\n";
        out << "port="<<port<< "\r\n";
        out << QString("truststore=%1/.shanoir/neurinfo.truststore\r\n").arg(QDir::homePath());
        set.close();
    }
}
