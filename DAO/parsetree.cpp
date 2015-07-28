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

void ParseTree::parseDatasetProcesing(QString xmlserializer, int idStudy, int idSubject, int idExam, int idDataset,QtShanoirTree* tree)
{
    qDebug()<<"parseDatasetProcesing";
    QDomDocument doc;
    doc.setContent(xmlserializer);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());

    QDomNode n = doc.firstChild().firstChildElement("return");
//    while (!n.isNull())
//    {

//           processType->setText(0,QString(n.firstChildElement("refDatasetProcessing").firstChild().nodeValue()));
//           processType->setText(1,"PROCESS");
//           processType->setIcon(0, QIcon(":Images/datasetProcessing.16.16.png"));
//           processType->setCheckState(0, sub->checkState(0));

//           QDomNode el = n.firstChildElement("outputs");

//           while (!el.isNull())
//           {
//               QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 6);

//               QString dataName = el.firstChildElement("name").firstChild().nodeValue();
//               if (dataName == "")
//                   dataName = el.firstChildElement("id").firstChild().nodeValue();

//               QDate creationDate = QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate);

//               exam->setText(0, QString("%1 - %2").arg(dataName) .arg(creationDate.toString(Qt::SystemLocaleShortDate)));
//               exam->setText(1, "DATASET");
//               exam->setIcon(0, QIcon(":Images/dataset.64x64.png"));
//               exam->setData(0, QTreeWidgetItem::UserType + 6, QString(el.firstChildElement("id").firstChild().nodeValue()));
//               exam->setCheckState(0, sub->checkState(0));

//               if (sub->checkState(0) == Qt::Checked)
//                   d->selectedId.insert(exam->data(0, QTreeWidgetItem::UserType + 6).toInt(),exam->text(0));

//               processType->addChild(exam);
//               el = el.nextSiblingElement("outputs");
//           }

//           sub->addChild(processType);
//           n = n.nextSiblingElement("return");
//       }
//       sub->setExpanded(true);

}



void ParseTree::RemoveEnveloppe()
{

}
