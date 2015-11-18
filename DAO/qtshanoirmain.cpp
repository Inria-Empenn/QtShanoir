#include "qtshanoirmain.h"
#include "qtshanoirdownload.h"
#include <QDebug>
namespace GlobalData
{
	QtShanoirSettings settings;
}

QtShanoirMain::QtShanoirMain()
{

}
QList<QString> QtShanoirMain::getSelectedIds()
{
    return this->selectedIds;
}

void QtShanoirMain::setSelectedIds(QList<QString> list)
{
    this->selectedIds = list;
}

void QtShanoirMain::clearSelectedIds()
{
    selectedIds.clear();
}

QString QtShanoirMain::authentification()
{
    QtSoapNamespaces &registry = QtSoapNamespaces::instance();
    registry.registerNamespace ( "ns1", "http://impl.webservices.shanoir.org/" );
    registry.registerNamespace ( "ns2", "http://finder.impl.webservices.shanoir.org/" );
    registry.registerNamespace ( "ns3", "http://importer.impl.webservices.shanoir.org/" );
    QString ws = "StudyFinder";
    QString impl ( "http://finder.impl.webservices.shanoir.org/" );

   QString xmlserializer;

    bool querySuccess = QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() <<  GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<< xmlserializer;
        qDebug()<<" error setUsername";
        return xmlserializer;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        qDebug()<<"error setPassword";
        return xmlserializer;
    }
    return "";
}



QString QtShanoirMain::acquireStudy_Subject()
{
    qDebug()<<"Debut Populate";
//    QtSoapNamespaces& registry = QtSoapNamespaces::instance();
//    registry.registerNamespace("ns1","http://impl.webservices.shanoir.org/");
//    registry.registerNamespace("ns2", "http://finder.impl.webservices.shanoir.org/");
//    registry.registerNamespace("ns3", "http://importer.impl.webservices.shanoir.org/");

    QString ws = "StudyFinder";
    QString impl ("http://finder.impl.webservices.shanoir.org/");
    bool querySucess;
    QString xmlserializer;

    authentification();

//    bool querySuccess = QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << login, xmlserializer);

//    if (!querySuccess)
//    {
//        qDebug()<< xmlserializer;
//        //emit queryFailed(xmlserial);
//        qDebug()<<" error setUsername";
//        //return;
//    }
//    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << password, xmlserializer);
//    if (!querySuccess)
//    {
//        //emit queryFailed(xmlserial);
//        qDebug()<<"error setPassword";
//        //return;
//    }

    querySucess = QtShanoirWebService::Query(ws,"find",impl,QStringList(),QStringList(),xmlserializer);
    if (!querySucess)
    {
       // emit queryFailed(xmlserializer);
        qDebug()<<"error studyName";
        //return;
    }


    //les messages d'erreur

    QFile file("populate.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
        //return;
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();



return xmlserializer;


}

QString QtShanoirMain::acquireExam(QString str)
{
         QString ws = "ExaminationFinder";
        QString impl = "http://finder.impl.webservices.shanoir.org/";

        QString xmlserializer;
        //authentification();
        QString login = "ttest";
        QString password = "shanoir$1";
        bool querySuccess ;
        querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

        if (!querySuccess)
        {
            qDebug()<< xmlserializer;
            //emit queryFailed(xmlserial);
            qDebug()<<" error setUsername";
            //return;
        }
        querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
        if (!querySuccess)
        {
            //emit queryFailed(xmlserial);
            qDebug()<<"error setPassword";
            //return;
        }



    querySuccess = QtShanoirWebService::Query ( ws, "setSubjectIds", impl, QStringList() << "examinationSubjectIds", QStringList() << str, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setSubjectIds";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "find", impl, QStringList(), QStringList(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"error find";
        //return;
    }

    QFile file("examination.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();

    return xmlserializer;


}

QString QtShanoirMain::acquireDataset(QString idSubject,QString idExam)
{
    QString ws = "DatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    QString xmlserializer;
    //authentification();
    QString login = "ttest";
    QString password = "shanoir$1";
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<< xmlserializer;
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }

        querySuccess = QtShanoirWebService::Query ( ws, "setSubjectIds", impl, QStringList() << "datasetSubjectIds", QStringList() << idSubject, xmlserializer);
        if (!querySuccess)
        {
            //emit queryFailed(xmlserial);
            qDebug()<<"error setSubjectIds";
            //return;
        }

        querySuccess = QtShanoirWebService::Query ( ws, "setExaminationIds", impl, QStringList() << "datasetExaminations", QStringList() << idExam, xmlserializer);
        if (!querySuccess)
        {
           // emit queryFailed(xmlserial);
            qDebug()<<"error setExaminationIds";
            //return;
        }

        querySuccess = QtShanoirWebService::Query ( ws, "find", impl, QStringList(), QStringList(), xmlserializer);
        if (!querySuccess)
        {
           // emit queryFailed(xmlserial);
            qDebug()<<"error find";
            //return;
        }

        QFile file("dataset.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << " Could not open file for writing";
        }
        QTextStream out(&file);
        out << xmlserializer;
        file.close();

        return xmlserializer;


}

QString QtShanoirMain::acquireProcess_ProcessedDataset(QString idDataset)
{
    QString ws = "DatasetProcessingFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";

    QString xmlserializer;
    //authentification();
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<< xmlserializer;
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setInputDatasetIds", impl, QStringList() << "datasetIds", QStringList() << idDataset, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setInputDatasetIds";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "find", impl, QStringList(), QStringList(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("process.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();

    return xmlserializer;

}

void QtShanoirMain::downloadMetadata(QString datasetId)
{
    QString ws = "DatasetFinder";
    QString impl = "http://finder.impl.webservices.shanoir.org/";
    QString xmlserializer;

    bool querySuccess = QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"setUsername";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"setPassword";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setDatasetIds", impl, QStringList() << "datasetIds", QStringList() << datasetId, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"setDatasetIds";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "find", impl, QStringList(), QStringList(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"find";
        //return;
    }

//    QString xmlserializerError;
//    querySuccess = QtShanoirWebService::Query ( ws, "getErrorMessage", impl, QStringList(), QStringList(), xmlserializerError);
//    if (!querySuccess)
//    {
//        emit queryFailed(xmlserializerError);
//        return;
//    }

//    if (this->getErrorMessage(xmlserializerError) != "")
//    {
//        emit queryFailed(this->getErrorMessage(xmlserialError));
//    }

//    QDomDocument doc;
//    doc.setContent (xmlserializer);

//    QString tmpName = downloadFileName.replace ( ".nii", ".xml" ).replace ( ".zip", ".xml" );
//    tmpName.replace ( QDir::separator(),"_" );

//    QFile dFile (downloadDir + QDir::separator() + tmpName);
//    dFile.open ( QFile::WriteOnly );
//    dFile.write ( doc.toString().toUtf8().data());
//    dFile.close();

}


QString QtShanoirMain::getDownloadFilename (QString datasetId)
{
    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess;

    querySuccess = QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"setUsername";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"setPassword";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"setDatasetId";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "getFileName", impl, QStringList(), QStringList(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"getFileName";
        //return;
    }

//    QString xmlserializerError;
//    querySuccess = QtShanoirWebService::Query ( ws, "getErrorMessage", impl, QStringList(), QStringList(), xmlserializerError);
//    if (!querySuccess)
//    {
//        emit queryFailed(xmlserializer);
//        return;
//    }

//    if (this->getErrorMessage(xmlserialError) != "")
//    {
//        emit queryFailed(this->getErrorMessage(xmlserialError));
//        return;
//    }

    qDebug()<<"messsssssssssssssssssssssssssssssssssssssage"<<xmlserializer;
    qDebug()<<"messsssssssssssssssssssssssssssssssssssssage";
    return xmlserializer;
}

QByteArray QtShanoirMain::downloadDataset(QString datasetId)
{
    QString ws = "Downloader";
    QString impl = "http://impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess;
    querySuccess = QtShanoirWebService::Query (ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"setUsername";
        //return;
    }

    querySuccess = QtShanoirWebService::Query (ws, "setPassword", impl, QStringList() << "dummy", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"setUsername";
        //return;
    }

    querySuccess = QtShanoirWebService::Query (ws, "setDatasetId", impl, QStringList() << "datasetId", QStringList() << datasetId, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"setDatasetId";
        //return;
    }

    QByteArray bin;
    querySuccess = QtShanoirWebService::BinaryQuery (ws, "download", impl, QStringList(), QStringList(), bin);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"download";
        //return;
    }

//    QString xmlserializerError;
//    querySuccess = QtShanoirWebService::Query (ws, "getErrorMessage", impl, QStringList(), QStringList(), xmlserializerError);
//    if (!querySuccess)
//    {
//        emit queryFailed(xmlserializer);
//        return;
//    }

    return bin;

}





void QtShanoirMain::getProcessingListId()
{

}

QString QtShanoirMain::getErrorMessage(QString xmlserialize)
{
	return xmlserialize;
}

void QtShanoirMain::queryFinished()
{

}

int QtShanoirMain::getCurrentId()
{
    return this->currentId;
}

void QtShanoirMain::setCurrentId(int id)
{
    this->currentId = id;
}

QString QtShanoirMain::acquireProcessingList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);

    qDebug()<< "message"<<xmlserializer;

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getDatasetProcessingList", impl, QStringList(), QStringList(), xmlserializer);


    if (!querySuccess)
    {
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("processingList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();

    return xmlserializer;

}


QString QtShanoirMain::acquireDatasetTypeList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    qDebug()<<xmlserializer;
    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);

    qDebug()<< "message"<<xmlserializer;

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getDatasetTypeList", impl, QStringList(), QStringList(), xmlserializer);

    qDebug()<<xmlserializer;
    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("datasetTypeList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;

}

QString QtShanoirMain::acquireMrdatasetNatureList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getMrdatasetNatureList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("mrdatasetNatureList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireMrSpectroscopydatasetNatureList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getMrSpectroscopydatasetNatureList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("mrSpectroscopydatasetNatureList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireMrDatasetQualityProcedureTypeList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getMrDatasetQualityProcedureTypeList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("mrDatasetQualityProcedureTypeList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireCalibrationDatasetTypeList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getCalibrationDatasetTypeList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("calibrationDatasetTypeList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireProcessedDatasetTypeList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getProcessedDatasetTypeList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("processedDatasetTypeList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireTemplateDatasetNatureList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getTemplateDatasetNatureList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("templateDatasetNatureList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireParameterQuantificationNatureList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getParameterQuantificationNatureList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("parameterQuantificationNatureList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}

QString QtShanoirMain::acquireSpectNatureList()
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess ;
    querySuccess= QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);

    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<" error setUsername";
        //return;
    }
    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);


    if (!querySuccess)
    {
        //emit queryFailed(xmlserial);
        qDebug()<<"error setPassword";
        //return;
    }


    querySuccess = QtShanoirWebService::Query ( ws, "getSpectNatureList", impl, QStringList(), QStringList(), xmlserializer);

    if (!querySuccess)
    {
        qDebug()<<"errror"<<xmlserializer;
       // emit queryFailed(xmlserial);
        qDebug()<<"error find";
        //return;
    }

    QFile file("spectNatureList.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << " Could not open file for writing";
    }
    QTextStream out(&file);
    out << xmlserializer;
    file.close();
    return xmlserializer;
}


void QtShanoirMain::uploadProcessedDatasetFile(QtShanoirUploadProcessedDatasetAttributes processedDatasetFile)
{
    QString ws = "ProcessedDatasetUpload";
    QString impl = "http://importer.impl.webservices.shanoir.org/";

    QString xmlserializer;
    bool querySuccess = QtShanoirWebService::Query ( ws, "setUsername", impl, QStringList() << "username", QStringList() << GlobalData::settings.getLogin(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"error username";
        //return;
    }

    querySuccess = QtShanoirWebService::Query ( ws, "setPassword", impl, QStringList() << "password", QStringList() << GlobalData::settings.getPassword(), xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"error password";
        //return;
    }

    QFile file (processedDatasetFile.getFilename());
    file.open ( QIODevice::ReadOnly );
    querySuccess = QtShanoirWebService::Query ( ws, "uploadFile", impl, QStringList() << "dataHandler" << "filename", QStringList() << file.readAll().toBase64() << QDir (processedDatasetFile.getFilename()).dirName(),xmlserializer);
    file.close();

    QtSoapStruct *str_processedDatasetFile=new QtSoapStruct(QtSoapQName("ProcessedDatasetAttributes"));

   str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("studyId"),processedDatasetFile.getStudyId()));

   for(int i=0; i<processedDatasetFile.getInputDatasetIdList().size();i++)
    str_processedDatasetFile->insert(new QtSoapSimpleType(QtSoapQName("inputDatasetIdList"),processedDatasetFile.getInputDatasetIdList()[i]));

    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refDatasetProcessingId"),processedDatasetFile.getRefDatasetProcessingId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("datasetClass"),processedDatasetFile.getDatasetClass()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("datasetName"),processedDatasetFile.getDatasetName()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("datasetComment"),processedDatasetFile.getDatasetComment()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refMrDatasetNatureId"),processedDatasetFile.getRefMrDatasetNatureId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refMrQualityProcedureTypeId"),processedDatasetFile.getRefMrQualityProcedureTypeId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refCalibrationDatasetTypeId"),processedDatasetFile.getRefCalibrationDatasetTypeId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refProcessedDatasetTypeId"),processedDatasetFile.getRefProcessedDatasetTypeId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refParameterQuantificationDatasetNatureId"),processedDatasetFile.getRefParameterQuantificationDatasetNatureId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refSpectDatasetNatureId"),processedDatasetFile.getRefSpectDatasetNatureId()));
    str_processedDatasetFile->insert( new QtSoapSimpleType(QtSoapQName("refTemplateDatasetNatureId"),processedDatasetFile.getRefTemplateDatasetNatureId()));

    querySuccess = QtShanoirWebService::QueryStruct( ws, "importProcessedDatasetAttributes", impl,str_processedDatasetFile, xmlserializer);
    if (!querySuccess)
    {
        //emit queryFailed(xmlserializer);
        qDebug()<<"error import";
        //return;
    }
}
