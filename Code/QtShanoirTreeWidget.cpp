/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <QtShanoirTreeWidget.h>
#include <QtShanoir.h>
#include <QtShanoirSettings.h>

class QtShanoirTreeWidgetPrivate
{
    public:
        QMap<int,QString> selectedId;
        QMap<int,QString> studyIds;

};

QtShanoirTreeWidget::QtShanoirTreeWidget(QWidget * widget) :
    d(new QtShanoirTreeWidgetPrivate)
{
    setupUi(this);
    treeWidget->setColumnWidth(0, 350);
    treeWidget->setColumnWidth(1, 50);
    treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    initConnections();
}

void
QtShanoirTreeWidget::initConnections()
{
    QObject::connect(treeWidget, SIGNAL(itemClicked (QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    //QObject::connect(treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextExportMenu(QPoint)));
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
    {
        emit id(item->data(0, QTreeWidgetItem::UserType + 6).toString().toInt());
    
        if (item->childCount() == 0)
            emit processingQuery(item->data(0, QTreeWidgetItem::UserType + 6).toString());
    }
        
    this->updateCheckBoxes(item);
}

void
QtShanoirTreeWidget::contextExportMenu(const QPoint point)
{
    // Get the QTreeWidgetItem corresponding to the clic
//    QTreeWidgetItem * item = 0;
//    item = treeWidget->itemAt(point);
    QMenu menu(treeWidget);
    QAction * find = new QAction(this);
//    QAction * expand = QAction(this);
    QAction * download = new QAction(this);

//    if (item != 0) {
//        // If the selected item is a patient
//        if (item->type() == QTreeWidgetItem::UserType + 3) {
//            expand->setText(tr("Expand"));
//            QObject::connect(expand, SIGNAL(triggered()), this, SLOT(showPreview()));
//            menu.addAction(actionPreview);
//            menu.addSeparator();
//        }
//    }

    // By default the context menu contains an open dicomdir a find command.
    find->setText(tr("Find studies"));
    find->setIconVisibleInMenu(true);
    find->setIcon(QIcon(":/Images/search.16x16.png"));
    QObject::connect(find, SIGNAL(triggered()), QtShanoir::instance(), SLOT(find()));
    menu.addAction(find);
    // If there's items selected
    if (!d->selectedId.isEmpty()) {
        menu.addSeparator();
        download->setText(tr("Download"));
        download->setIconVisibleInMenu(true);
        download->setIcon(QIcon(":/Images/download.16x16.png"));
        QObject::connect(download, SIGNAL(triggered()), QtShanoir::instance(), SLOT(download()));
        menu.addAction(download);
    }
    menu.exec(treeWidget->mapToGlobal(point));
}

void
QtShanoirTreeWidget::updateCheckBoxes(QTreeWidgetItem * item)
{
    if (item->checkState(0) == Qt::Checked) 
    {
        if ((item->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->data(0, QTreeWidgetItem::UserType + 6).toInt())) 
        {
            d->selectedId.insert(item->data(0, QTreeWidgetItem::UserType + 6).toInt(), item->text(0));
        }
        
        if (item->type() != QTreeWidgetItem::UserType + 6)
        {
            for (int i = 0; i < item->childCount(); i++) 
            {
                item->child(i)->setCheckState(0, Qt::Checked);
                if ((item->child(i)->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt()))
                    d->selectedId.insert(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt(), item->child(i)->text(0));
                
                for (int j = 0; j < item->child(i)->childCount(); j++) 
                {
                    item->child(i)->child(j)->setCheckState(0, Qt::Checked);
                    if ((item->child(i)->child(j)->type() == QTreeWidgetItem::UserType + 6) && !d->selectedId.contains(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt()))
                        d->selectedId.insert(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt(),item->child(i)->child(j)->text(0));
                }
            }
        }
    }
    else 
    {
        if (item->type() == QTreeWidgetItem::UserType + 3) 
        {
            for (int i = 0; i < item->childCount(); i++) 
            {
                item->child(i)->setCheckState(0, Qt::Unchecked);
                for (int j = 0; j < item->child(i)->childCount(); j++) 
                {
                    d->selectedId.remove(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                    //d->selectedId.removeOne(item->child(i)->child(j)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                    item->child(i)->child(j)->setCheckState(0, Qt::Unchecked);
                }
            }
        }
        
        if (item->type() == QTreeWidgetItem::UserType + 4) 
        {
            for (int i = 0; i < item->childCount(); i++) 
            {
                d->selectedId.remove(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
        
        if (item->type() == QTreeWidgetItem::UserType + 6) 
        {
            item->parent()->setCheckState(0, Qt::Unchecked);
            item->parent()->parent()->setCheckState(0, Qt::Unchecked);
            d->selectedId.remove(item->data(0, QTreeWidgetItem::UserType + 6).toInt());
        }
        
        if (item->type() == QTreeWidgetItem::UserType + 7) 
        {
            for (int i = 0; i < item->childCount(); i++) 
            {
                d->selectedId.remove(item->child(i)->data(0, QTreeWidgetItem::UserType + 6).toInt());
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }

            item->parent()->setCheckState(0, Qt::Unchecked);
            item->parent()->parent()->setCheckState(0, Qt::Unchecked);
        }
    } 
    
    emit filename(QString(""));
    //    qDebug()<< d->selectedId;
    emit selected(d->selectedId);
}

void
QtShanoirTreeWidget::parseStudy(QString xmlserial, QRegExp patientNameFilter)
{
  d->studyIds.clear();
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
  shanoir->setIcon(0, QIcon(":Images/network.64x64.png"));
  shanoir->setExpanded(true);
  // list the study by name + id
  QDomNode n = doc.firstChild().firstChild();
  
  while (!n.isNull()) {
    if (n.toElement().tagName() == "return") {
      QTreeWidgetItem * study = new QTreeWidgetItem;
      study->setText(0, QString("%1").arg(n.firstChildElement("name").firstChild().toText().nodeValue()));
      study->setText(1, "STUDY");
      study->setIcon(0, QIcon(":Images/study.64x64.png"));
      study->setToolTip(0, QString("Study Id : %1").arg(n.firstChildElement("id").firstChild().toText().nodeValue()));
      
      d->studyIds.insert(n.firstChildElement("id").firstChild().toText().nodeValue().toInt(), n.firstChildElement("name").firstChild().toText().nodeValue());
      //shanoir->addChild(study);
      // find patients for each study
      QDomNode rel = n.firstChildElement("relSubjectStudyList");
      
      while (!rel.isNull()) {
        QDomElement el = rel.toElement();
        if (patientNameFilter.exactMatch(el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue()))
        {
          QTreeWidgetItem* sub = new QTreeWidgetItem(QTreeWidgetItem::UserType + 3);
          sub->setText(0, QString("%1").arg(el.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue()));
          sub->setText(1, "SUBJECT");
          sub->setIcon(0, QIcon(":Images/subject.64x64.png"));
          sub->setToolTip(0, QString("Sex: %2 BirthDate: %3 (id: %1)") .arg(el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()) .arg(el.firstChildElement("subject").firstChildElement("refSex").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("subject").firstChildElement("birthDate").firstChild().nodeValue(), Qt::ISODate) .toString(Qt::SystemLocaleShortDate)));
          sub->setData(0, QTreeWidgetItem::UserType + 3, (el.firstChildElement("subject").firstChildElement("id").firstChild().nodeValue()));
          sub->setCheckState(0, Qt::Unchecked);
          study->addChild(sub);
        }
        rel = rel.nextSiblingElement("relSubjectStudyList");
      }
      
      if (study->childCount() > 0)
        shanoir->addChild(study);
    }
    n = n.nextSibling();
  }
  emit studyMap(d->studyIds);
  //    treeWidget->itemClicked();
  doc.clear();
  
  emit queryFinished();
}

void
QtShanoirTreeWidget::parseMrExamination(QString xmlserial, QString dateFilter)
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
      if ((QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::ISODate) == dateFilter)||(dateFilter == "")) {
        QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 4);
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("examinationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));
        exam->setData(0, QTreeWidgetItem::UserType + 4, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setData(0, QTreeWidgetItem::UserType + 5, id);
        exam->setIcon(0, QIcon(":Images/examination.16x16.png"));
        exam->setText(1, "Exam");
        exam->setCheckState(0, sub->checkState(0));
        sub->addChild(exam);
      }
      el = el.nextSiblingElement("return");
    }
    sub->setExpanded(true);

    doc.clear();

    emit queryFinished();
}

void
QtShanoirTreeWidget::parseAcquisition(QString xmlserial, QRegExp datasetNameFilter)
{
    //qDebug() << xmlserial;
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe

    QTreeWidgetItem* sub = treeWidget->selectedItems().front();
    QDomNode el = doc.firstChild().firstChildElement("datasetResultList");

    if (el.isNull()) {
        QFont f = sub->font(0);
        f.setStrikeOut(true);
        sub->setFont(0, f);
    }

    while (!el.isNull()) {
      if (datasetNameFilter.exactMatch(el.firstChildElement("name").firstChild().nodeValue())) {
        QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 6);
        exam->setText(0, QString("%1 - %2").arg(el.firstChildElement("name").firstChild().nodeValue()) .arg(QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate).toString(Qt::SystemLocaleShortDate)));
        exam->setToolTip(0, QString("%1 - (TR %2, TE %3, FA %4) ").arg(el.firstChildElement("comment").firstChild().nodeValue()) .arg(el.firstChildElement("repetitionTime").firstChildElement("repetitionTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("echoTime").firstChildElement("echoTimeValue").firstChild().nodeValue()) .arg(el.firstChildElement("flipAngle").firstChildElement("flipAngleValue").firstChild().nodeValue()));
        exam->setText(1, "DATASET");
        exam->setIcon(0, QIcon(":Images/dataset.64x64.png"));
        exam->setData(0, QTreeWidgetItem::UserType + 6, QString(el.firstChildElement("id").firstChild().nodeValue()));
        exam->setCheckState(0, sub->checkState(0));

        if (sub->checkState(0) == Qt::Checked)
            d->selectedId.insert(exam->data(0, QTreeWidgetItem::UserType + 6).toInt(),exam->text(0));

        sub->addChild(exam);
      }
      el = el.nextSiblingElement("datasetResultList");
    }
    sub->setExpanded(true);
    doc.clear();

    emit queryFinished();
}

void
QtShanoirTreeWidget::parseProcessingData(QString xmlserial)
{
    QDomDocument doc;
    doc.setContent(xmlserial);
    doc.appendChild(doc.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
    doc.removeChild(doc.firstChild());
    // Sub root the document to remove the SOAP Enveloppe
    
    QTreeWidgetItem* sub = treeWidget->selectedItems().front();
    QDomNode n = doc.firstChild().firstChildElement("return");
        
    while (!n.isNull()) {
        QTreeWidgetItem* processType = new QTreeWidgetItem(QTreeWidgetItem::UserType + 7);
        
        processType->setText(0,QString(n.firstChildElement("refDatasetProcessing").firstChild().nodeValue()));
        processType->setText(1,"PROCESS");
        processType->setIcon(0, QIcon(":Images/datasetProcessing.16.16.png"));
        processType->setCheckState(0, sub->checkState(0));
        
        QDomNode el = n.firstChildElement("outputs");
        
        while (!el.isNull())
        {
            QTreeWidgetItem* exam = new QTreeWidgetItem(QTreeWidgetItem::UserType + 6);
        
            QString dataName = el.firstChildElement("name").firstChild().nodeValue();
            if (dataName == "")
                dataName = el.firstChildElement("id").firstChild().nodeValue();
        
            QDate creationDate = QDate::fromString(el.firstChildElement("datasetCreationDate").firstChild().nodeValue(), Qt::ISODate);
        
            exam->setText(0, QString("%1 - %2").arg(dataName) .arg(creationDate.toString(Qt::SystemLocaleShortDate)));
            exam->setText(1, "DATASET");
            exam->setIcon(0, QIcon(":Images/dataset.64x64.png"));
            exam->setData(0, QTreeWidgetItem::UserType + 6, QString(el.firstChildElement("id").firstChild().nodeValue()));
            exam->setCheckState(0, sub->checkState(0));
        
            if (sub->checkState(0) == Qt::Checked)
                d->selectedId.insert(exam->data(0, QTreeWidgetItem::UserType + 6).toInt(),exam->text(0));
            
            processType->addChild(exam);
            el = el.nextSiblingElement("outputs");
        }
        
        sub->addChild(processType);
        n = n.nextSiblingElement("return");
    }
    sub->setExpanded(true);
    doc.clear();
    
    emit queryFinished();
}
