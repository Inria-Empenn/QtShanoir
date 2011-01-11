/*
 * QtShanoirTreeWidget.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoirTreeWidget.h>
#include <QtShanoir.h>
#include <QtShanoirSettings.h>

class QtShanoirTreeWidgetPrivate
{
    public:
        QList<int> selectedId;

};

QtShanoirTreeWidget::QtShanoirTreeWidget(QWidget * widget) :
    d(new QtShanoirTreeWidgetPrivate)
{
    setupUi(this);
    treeWidget->setColumnWidth(0, 350);
    treeWidget->setColumnWidth(1, 50);
    initConnections();
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
QtShanoirTreeWidget::itemClicked(QTreeWidgetItem* item, int)
{
    // Item has user defined datatype && the data was not fetched yet
    if (!item->data(0, QTreeWidgetItem::UserType + 3).isNull() && item->childCount() == 0)
        emit mrExamQuery(item->data(0, QTreeWidgetItem::UserType + 3).toString());
    if (!item->data(0, QTreeWidgetItem::UserType + 4).isNull() && item->childCount() == 0)
        emit datasetQuery(item->data(0, QTreeWidgetItem::UserType + 4).toString(), item->data(0, QTreeWidgetItem::UserType + 5).toString());
    if (!item->data(0, QTreeWidgetItem::UserType + 6).isNull())
        emit id(item->data(0, QTreeWidgetItem::UserType + 6).toString().toInt());

    this->updateCheckBoxes(item);
}

void
QtShanoirTreeWidget::updateCheckBoxes(QTreeWidgetItem * item)
{
    if (item->checkState(0) == Qt::Checked) {
        if ((item->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->data(0, QTreeWidgetItem::UserType + 6).toInt())) {
            d->selectedId.append(item->data(0, QTreeWidgetItem::UserType + 6).toInt());
        }
        for (int i = 0; i < item->childCount(); i++) {
            item->child(i)->setCheckState(0, Qt::Checked);
            if ((item->child(i)->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt()))
                d->selectedId.append(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt());
            for (int j = 0; j < item->child(i)->childCount(); j++) {
                item->child(i)->child(j)->setCheckState(0, Qt::Checked);
                if ((item->child(i)->child(j)->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt()))
                    d->selectedId.append(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt());
            }
        }
    }
    else {
        if (item->type() == QTreeWidgetItem::UserType + 3) {
            for (int i = 0; i < item->childCount(); i++) {
                item->child(i)->setCheckState(0, Qt::Unchecked);
                for (int j = 0; j < item->child(i)->childCount(); j++) {
                    d->selectedId.removeOne(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                    item->child(i)->child(j)->setCheckState(0, Qt::Unchecked);
                }
            }
        }
        if (item->type() == QTreeWidgetItem::UserType + 4) {
            for (int i = 0; i < item->childCount(); i++) {
                d->selectedId.removeOne(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
        if (item->type() == QTreeWidgetItem::UserType + 6) {
            item->parent()->setCheckState(0, Qt::Unchecked);
            item->parent()->parent()->setCheckState(0, Qt::Unchecked);
            d->selectedId.removeOne(item->data(0, QTreeWidgetItem::UserType + 6).toInt());
        }
    }
    emit
    filename(QString(""));
//    qDebug()<< d->selectedId;
    emit
    selected(d->selectedId);
}

void
QtShanoirTreeWidget::contextExportMenu(const QPoint point)
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
    shanoir->setText(0, QString("Shanoir (%1)").arg(QtShanoirSettings::Instance()->host()));
    shanoir->setText(1, QString("SERVER"));
    shanoir->setIcon(0,QIcon(":Images/network.64x64.png"));
    shanoir->setExpanded(true);
    // list the study by name + id
    QDomNode n = doc.firstChild().firstChild();

    while (!n.isNull()) {
        if (n.toElement().tagName() == "return") {
            QTreeWidgetItem * study = new QTreeWidgetItem;
            study->setText(0, QString("%1").arg(n.firstChildElement("name").firstChild().toText().nodeValue()));
            study->setText(1, "STUDY");
            study->setIcon(0,QIcon(":Images/study.64x64.png"));
            study->setToolTip(0, QString("Study Id : %1").arg(n.firstChildElement("id").firstChild().toText().nodeValue()));
            shanoir->addChild(study);
            // find patients for each study
            QDomNode rel = n.firstChildElement("relSubjectStudyList");

            while (!rel.isNull()) {
                QDomElement el = rel.toElement();
                QTreeWidgetItem* sub = new QTreeWidgetItem(QTreeWidgetItem::UserType + 3);
                sub->setText(0, QString("%1").arg(el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue()));
                sub->setText(1, "SUBJECT");
                sub->setIcon(0,QIcon(":Images/subject.64x64.png"));
                sub->setToolTip(0, QString("Sex: %2 BirthDate: %3 (id: %1)") .arg(el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()) .arg(el.firstChildElement("subject").firstChildElement("refSex").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("subject").firstChildElement("birthDate").firstChild().nodeValue(), Qt::ISODate) .toString(Qt::SystemLocaleShortDate)));
                sub->setData(0, QTreeWidgetItem::UserType + 3, (el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()));
                sub->setCheckState(0, Qt::Unchecked);
                study->addChild(sub);
                rel = rel.nextSiblingElement("relSubjectStudyList");
            }
        }
        n = n.nextSibling();
    }
    //    treeWidget->itemClicked();
    doc.clear();

    emit queryFinished();
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
        QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 4);
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));
        exam->setData(0, QTreeWidgetItem::UserType + 4, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setData(0, QTreeWidgetItem::UserType + 5, id);
        exam->setIcon(0,QIcon(":Images/examination.16x16.png"));
        exam->setText(1, "Exam");
        exam->setCheckState(0, sub->checkState(0));
        sub->addChild(exam);
        el = el.nextSiblingElement("return");
    }
    sub->setExpanded(true);

    doc.clear();

    emit queryFinished();
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
        QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 6);
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("name").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));
        exam->setToolTip(0, QString("%1 - (TR %2, TE %3, FA %4) ").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(el.firstChildElement("repetitionTime").firstChildElement("repetitionTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("echoTime").firstChildElement("echoTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("flipAngle").firstChildElement("flipAngleValue").firstChild().nodeValue()));
        exam->setText(1, "DATASET");
        exam->setIcon(0,QIcon(":Images/dataset.64x64.png"));
        exam->setData(0, QTreeWidgetItem::UserType + 6, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setCheckState(0, sub->checkState(0));

        if (sub->checkState(0) == Qt::Checked)
            d->selectedId.append(exam->data(0, QTreeWidgetItem::UserType + 6).toInt());

        sub->addChild(exam);
        el = el.nextSiblingElement("mrDatasetResultList");
    }
    sub->setExpanded(true);
    doc.clear();

    emit queryFinished();
}

