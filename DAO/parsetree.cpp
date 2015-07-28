 #include "parsetree.h"
#include <QDomDocument>
#include "qtshanoirstudy.h"
#include "qtshanoirsubject.h"
#include "qtshanoirtree.h"
#include "qtshanoirexam.h"


ParseTree::ParseTree()
{

}
//void ParseTree::deleteEnvelop(QDomDocument* doc)
//{
//    *doc.setContent(xmlserializer);
//    *doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
//   *doc.removeChild(doc.firstChild());
//}
void ParseTree::parseStudy_Subject(QString xmlserializer,QtShanoirTree* tree)
{
    qDebug()<<"parseStudy_Subject";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    QDomNode n = doc.firstChild().firstChild();
    while (!n.isNull())
    {
        QtShanoirStudy study;
        QString id = n.firstChildElement("id").firstChild().toText().nodeValue();
        study.setId(id.toInt());
        study.setName(n.firstChildElement("name").firstChild().toText().nodeValue());
        QDomNode rel = n.firstChildElement("relSubjectStudyList");
        while (!rel.isNull())
        {
            QDomElement el = rel.toElement();
            QtShanoirSubject subject;
            QString id = el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue();
            subject.setId(id.toInt());
            subject.setName(el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue());
            subject.setBirthDate(QDate::fromString(el.firstChildElement("subject").firstChildElement("birthDate").firstChild().nodeValue(),Qt::ISODate));
            subject.setIdStudy(study.getId());
            QString sexe = el.firstChildElement("subject").firstChildElement("refSex").firstChild().nodeValue();
            if (sexe == "1")
                subject.setSexe('M');
            else
                subject.setSexe('F');

            study.insertSubject(subject);

            rel = rel.nextSiblingElement("relSubjectStudyList");
        }
        tree->insert(study);
        n = n.nextSibling();
    }
    //tree->displayAllTree();
}

void ParseTree::parseExam(QString xmlserializer,int idStudy, int idSubject, QtShanoirTree* tree)
{
    qDebug()<<"parseExam";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        QtShanoirExam exam;
        exam.setComment(el.firstChildElement("comment").firstChild().nodeValue());
        exam.setId(el.firstChildElement("id").firstChild().nodeValue().toInt());
        exam.setDate(QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(),Qt::ISODate));
        tree->getStudyById(idStudy).getSubjectById(idSubject).insertExam(exam);
        el = el.nextSiblingElement("return");
    }
    doc.clear();

        //emit queryFinished();
}

void ParseTree::parseDataset(QString xmlserializer, int idStudy, int idSubject, int idExam, QtShanoirTree* tree)
{
    qDebug()<<"parseDataset";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QDomNode el = doc.firstChild().firstChildElement("datasetResultList");

    while (!el.isNull())
    {
        QtShanoirDataset dataset;
        dataset.setId(el.firstChildElement("id").firstChild().nodeValue().toInt());
        dataset.setName(el.firstChildElement("name").firstChild().nodeValue());
        dataset.setCreationDate(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(),Qt::ISODate));
        dataset.setComment(el.firstChildElement("comment").firstChild().nodeValue());
        dataset.setFlipAngle(el.firstChildElement("flipAngle").firstChildElement("flipAngleValue").firstChild().nodeValue().toFloat());
        dataset.setRepetitionTime(el.firstChildElement("repetitionTime").firstChildElement("repetitionTimeValue").firstChild().nodeValue().toFloat());
        dataset.setEchoTime(el.firstChildElement("echoTime").firstChildElement("echoTimeValue").firstChild().nodeValue().toFloat());

        tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam).insertDataset(dataset);



        el = el.nextSiblingElement("datasetResultList");
    }
        doc.clear();


}

void ParseTree::parseProcess_ProcessedDataset(QString xmlserializer, int idStudy, int idSubject, int idExam, int idDataset,QtShanoirTree* tree)
{
    qDebug()<<"parseDatasetProcesing";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QDomNode n = doc.firstChild().firstChildElement("return");
    while (!n.isNull())
    {
        QtShanoirProcess process;
        process.setId(n.firstChildElement("id").firstChild().nodeValue().toInt());
        process.setName(n.firstChildElement("refDatasetProcessing").firstChild().nodeValue());
        process.setCreationDate(QDate::fromString(n.firstChildElement("processingDate").firstChild().nodeValue(),Qt::ISODate));

        QDomNode el = n.firstChildElement("outputs");

        while (!el.isNull())
       {
           QtShanoirProcessedDataset processedDataset;
           processedDataset.setId(el.firstChildElement("id").firstChild().nodeValue().toInt());
           processedDataset.setName(el.firstChildElement("name").firstChild().nodeValue());
           processedDataset.setName(el.firstChildElement("comment").firstChild().nodeValue());
           processedDataset.setProcessedDatasetCreationDate(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(),Qt::ISODate));

           process.insertProcessedDataset(processedDataset);
           el = el.nextSiblingElement("outputs");
       }

       tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam).getDatasetById(idDataset).insertProcess(process);
       n = n.nextSiblingElement("return");
   }
       doc.clear();
}

void ParseTree::parseProcessingList(QString xmlserializer,QtShanoirUpload* upload) // gerer les messages d'erreur
{
    qDebug()<<"parseProcessingList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> processingList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {

        processingList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setProcessingList(processingList);
    //return processingList;
}

void ParseTree::parseDatasetTypeList(QString xmlserializer,QtShanoirUpload* upload) // gerer les messages d'erreur
{
    qDebug()<<"parseDatasetTypeList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QStringList datasetTypeList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        datasetTypeList.append(el.firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    //return datasetTypeList;
    upload->setDatasetTypeList(datasetTypeList);
}

void ParseTree::parseMrdatasetNatureList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseMrdatasetNatureList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> mrdatasetNatureList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        mrdatasetNatureList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setMrdatasetNatureList(mrdatasetNatureList);
}

void ParseTree::parseMrSpectroscopydatasetNatureList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseMrSpectroscopydatasetNatureList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> mrSpectroscopydatasetNatureList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        mrSpectroscopydatasetNatureList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setMrSpectroscopydatasetNatureList(mrSpectroscopydatasetNatureList);
}

void ParseTree::parseMrDatasetQualityProcedureTypeList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseMrDatasetQualityProcedureTypeList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> mrDatasetQualityProcedureTypeList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        mrDatasetQualityProcedureTypeList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setMrDatasetQualityProcedureTypeList(mrDatasetQualityProcedureTypeList);
}

void ParseTree::parseCalibrationDatasetTypeList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseCalibrationDatasetTypeList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> calibrationDatasetTypeList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        calibrationDatasetTypeList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setCalibrationDatasetTypeList(calibrationDatasetTypeList);
}

void ParseTree::parseProcessedDatasetTypeList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseProcessedDatasetTypeList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> processedDatasetTypeList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        processedDatasetTypeList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setProcessedDatasetTypeList(processedDatasetTypeList);
}

void ParseTree::parseTemplateDatasetNatureList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseTemplateDatasetNatureList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> templateDatasetNatureList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        templateDatasetNatureList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setTemplateDatasetNatureList(templateDatasetNatureList);
}

void ParseTree::parseParameterQuantificationNatureList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseParameterQuantificationNatureList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> parameterQuantificationNatureList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        parameterQuantificationNatureList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setParameterQuantificationNatureList(parameterQuantificationNatureList);
}

void ParseTree::parseSpectNatureList(QString xmlserializer, QtShanoirUpload* upload)
{
    qDebug()<<"parseSpectNatureList";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QMap<int,QString> spectNatureList;
    QDomNode el = doc.firstChild().firstChildElement("return");
    while (!el.isNull())
    {
        spectNatureList.insert(el.firstChildElement("id").firstChild().nodeValue().toInt(),el.firstChildElement("labelName").firstChild().nodeValue());
        el = el.nextSiblingElement("return");
    }
    doc.clear();
    upload->setSpectNatureList(spectNatureList);
}

void ParseTree::RemoveEnveloppe()
{

}
