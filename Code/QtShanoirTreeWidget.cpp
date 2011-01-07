/*
 * QtShanoirTreeWidget.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoirTreeWidget.h>
#include <QtShanoirController.h>

class QtShanoirTreeWidgetPrivate
{
    private:

};

QtShanoirTreeWidget::QtShanoirTreeWidget(QWidget * widget) :
    d(new QtShanoirTreeWidgetPrivate)
{
    setupUi(this);
}

void
QtShanoirTreeWidget::initConnections()
{
    QObject::connect(treeWidget, SIGNAL(itemClicked (QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    QObject::connect(treeWidget, SIGNAL(itemDoubleClicked (QTreeWidgetItem*, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*, int)));
    QObject::connect(treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextExportMenu(QPoint)));
}

void
QtShanoirTreeWidget::itemDoubleClicked(QTreeWidgetItem * item, int column)
{

}

void
QtShanoirTreeWidget::itemClicked(QTreeWidgetItem* item, int )
{
    // Item has user defined datatype && the data was not fetched yet
    if (!item->data(0, QTreeWidgetItem::UserType + 3).isNull() && item->childCount() == 0) {
        emit mrExamQuery(item->data(0, QTreeWidgetItem::UserType + 3).toString());
//        setMrExamQuery("FindMrExam", item->data(0, QTreeWidgetItem::UserType + 3).toString());
//        doQuery("FindMrExam");
    }

    if (!item->data(0, QTreeWidgetItem::UserType + 4).isNull() && item->childCount() == 0) {
        emit datasetQuery(item->data(0, QTreeWidgetItem::UserType + 4).toString(), item->data(0, QTreeWidgetItem::UserType + 5).toString());

//        setDatasetQuery("FindDataset", item->data(0, QTreeWidgetItem::UserType + 4).toString(), item->data(0, QTreeWidgetItem::UserType + 5).toString());
//        doQuery("FindDataset");
    }

    if (!item->data(0, QTreeWidgetItem::UserType + 6).isNull()) {
//        emit acquisitionQuery(item->data(0, QTreeWidgetItem::UserType + 6).toString().toInt());
//        ui->label->setText(QString("%1 - %2").arg(item->text(0)).arg(item->data(0, QTreeWidgetItem::UserType + 6).toString()));
        emit id(item->data(0, QTreeWidgetItem::UserType + 6).toString().toInt());

//        ui->label->show();
//        ui->toolButton->show();
    }

}

void
QtShanoirTreeWidget::contextExportMenu( const QPoint point )
  {



  }

void
QtShanoirTreeWidget::parseStudy(QString xmlserial)
{
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem *root = treeWidget->invisibleRootItem();

    QTreeWidgetItem* shanoir = new QTreeWidgetItem();
    root->addChild(shanoir);

    //    shanoir
//    shanoir->setText(0, QString("Shanoir (%1)").arg(host));
//    shanoir->setToolTip(0, QString("User:%1 (port: %2)").arg(user).arg(port));
//    shanoir->setExpanded(true);
//    shanoir->setIcon(0, *ico_shanoir);
    // list the study by name + id
    QDomNode n = doc.firstChild().firstChild();

    while (!n.isNull()) {
        if (n.toElement().tagName() == "return") {
            QTreeWidgetItem * study = new QTreeWidgetItem;
            study->setText(0, QString("%1").arg(n.firstChildElement("name").firstChild().toText().nodeValue()));
            study->setToolTip(0, QString("Study Id : %1").arg(n.firstChildElement("id").firstChild().toText().nodeValue()));
//            study->setIcon(0, *ico_study);
            shanoir->addChild(study);
            // find patients for each study
            QDomNode rel = n.firstChildElement("relSubjectStudyList");

            while (!rel.isNull()) {
                QDomElement el = rel.toElement();
                QTreeWidgetItem* sub = new QTreeWidgetItem;
                sub->setText(0, QString("%1").arg(el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue()));
                sub->setToolTip(0, QString("Sex: %2 BirthDate: %3 (id: %1)") .arg(el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()) .arg(el.firstChildElement("subject").firstChildElement("refSex").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("subject").firstChildElement("birthDate").firstChild().nodeValue(), Qt::ISODate) .toString(Qt::SystemLocaleShortDate)));
                sub->setData(0, QTreeWidgetItem::UserType + 3, (el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()));
//                sub->setIcon(0, *ico_subject);
                sub->setCheckState(0, Qt::Unchecked);
                study->addChild(sub);
                rel = rel.nextSiblingElement("relSubjectStudyList");
            }
        }
        n = n.nextSibling();
    }
    //    treeWidget->itemClicked();
    doc.clear();
}

void
QtShanoirTreeWidget::parseMrExamination(QString xmlserial)
{
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem* sub = treeWidget->selectedItems().front();
    QString id = sub->data(0, QTreeWidgetItem::UserType + 3).toString();

    QDomNode el = doc.firstChild().firstChildElement("return");
    if (el.isNull()) {
        QFont f = sub->font(0);
        f.setStrikeOut(true);
        sub->setFont(0, f);
    }
    while (!el.isNull()) {
        QTreeWidgetItem* exam = new QTreeWidgetItem;
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));

        exam->setData(0, QTreeWidgetItem::UserType + 4, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setData(0, QTreeWidgetItem::UserType + 5, id);
//        exam->setIcon(0, *ico_exam);

        exam->setCheckState(0, Qt::Unchecked);

        sub->addChild(exam);
        el = el.nextSiblingElement("return");
    }
    sub->setExpanded(true);

    doc.clear();
}

void
QtShanoirTreeWidget::parseAcquisition(QString xmlserial)
{
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem* sub = treeWidget->selectedItems().front();

    QDomNode el = doc.firstChild().firstChildElement("mrDatasetResultList");

    if (el.isNull()) {
        QFont f = sub->font(0);
        f.setStrikeOut(true);
        sub->setFont(0, f);
    }

    while (!el.isNull()) {
        QTreeWidgetItem* exam = new QTreeWidgetItem;
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("name").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));
        exam->setToolTip(0, QString("%1 - (TR %2, TE %3, FA %4) ").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(el.firstChildElement("repetitionTime").firstChildElement("repetitionTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("echoTime").firstChildElement("echoTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("flipAngle").firstChildElement("flipAngleValue").firstChild().nodeValue()));

        exam->setData(0, QTreeWidgetItem::UserType + 6, QString(el.firstChildElement("id").firstChild().nodeValue()));
//        exam->setIcon(0, *ico_acq);
        exam->setCheckState(0, Qt::Unchecked);

        sub->addChild(exam);
        el = el.nextSiblingElement("mrDatasetResultList");
    }
    sub->setExpanded(true);
    doc.clear();
}

