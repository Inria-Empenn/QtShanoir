#include "qtshanoiruploadwidgetdatasettypedetailsmrdataset.h"
#include "ui_qtshanoiruploadwidgetdatasettypedetailsmrdataset.h"

#include <QDebug>
#include <QLibrary>
#include <QMessageBox>


//class MyHeader : public QHeaderView
//{
//public:
//  MyHeader(Qt::Orientation orientation, QWidget * parent = 0) : QHeaderView(orientation, parent)
//  {}

//protected:
//  void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
//  {
//    painter->save();
//    QHeaderView::paintSection(painter, rect, logicalIndex);
//    painter->restore();
//    if (logicalIndex == 0)
//    {
//      QStyleOptionButton option;
//      option.rect = QRect(25,25,25,25);
//      if (isOn)
//        option.state = QStyle::State_On;
//      else
//        option.state = QStyle::State_Off;
//      this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
//    }

//  }
//  void mousePressEvent(QMouseEvent *event)
//  {
//    if (isOn)
//      isOn = false;
//    else
//      isOn = true;
//    this->update();
//    QHeaderView::mousePressEvent(event);
//  }
//private:
//  bool isOn;
//};
//MyHeader *myHeader = new MyHeader(Qt::Horizontal, ui->processedDatasetTypeTable);
//ui->processedDatasetTypeTable->setHorizontalHeader(myHeader);

QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::QtShanoirUploadWidgetDatasetTypeDetailsMrDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent ): QWidget(parent), ui(new Ui::QtShanoirUploadWidgetDatasetTypeDetailsMrDataset)
{
    ui->setupUi(this);

    fillComboBoxes();
    filesToUploadInitial = files;
    filesToUpload = files;
    buildTable();
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::fillComboBoxes()
{
    // Fill MrDataset Nature Combo box
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QMap<int,QString> (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("getMrdatasetNatureList");
    if (cf)
    {
        mrDatasetNatureList = cf();
        if (!mrDatasetNatureList.isEmpty())
        {
            ui->mrDatasetNatureComboBox->insertItem(0,"");
            for (int i=0; i<mrDatasetNatureList.size();i++)
                ui->mrDatasetNatureComboBox->insertItem(i+1,mrDatasetNatureList.values().at(i));
        }
    }
    else
        qDebug() << "could not call function";

    // Fil MrDataset Quality Procedure Type
    cf = (CallFunction)library.resolve("getMrDatasetQualityProcedureTypeList");
        if (cf)
        {
            mrDatasetQualityProcedureTypeList = cf();
            if (!mrDatasetQualityProcedureTypeList.isEmpty())
            {
                ui->mrDatasetQualityProcedureTypeComboBox->insertItem(0,"");
                for (int i=0; i<mrDatasetQualityProcedureTypeList.size();i++)
                    ui->mrDatasetQualityProcedureTypeComboBox->insertItem(i+1,mrDatasetQualityProcedureTypeList.values().at(i));
            }
        }
        else
            qDebug() << "could not call function";
}


void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::buildTable()
{
    QStringList verticalLabels;
    QStringList horizontalLabels;
    for (int i=0;i<filesToUpload.size();i++)
    {
        verticalLabels.append(reduceFilenameToTwoDir(filesToUpload[i].getFilename()));
    }

    ui->processedDatasetTypeTable->setColumnCount(5);
    ui->processedDatasetTypeTable->setRowCount(verticalLabels.size());


    horizontalLabels << "" << tr("Name") << tr("Comment") << tr("MrDataset Nature") << tr("MrDataset Quality Procedue Type");
    ui->processedDatasetTypeTable->setHorizontalHeaderLabels(horizontalLabels);
    ui->processedDatasetTypeTable->setVerticalHeaderLabels(verticalLabels);

    ui->processedDatasetTypeTable->resizeColumnsToContents();
    ui->processedDatasetTypeTable->resizeRowsToContents();

    fillTable(filesToUploadInitial);
    initConnections();
}


void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files)
{
    //Add checkbox
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
            addCheckBox(i);

    //Add items
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
    {
        ui->processedDatasetTypeTable->setItem(i,1,new QTableWidgetItem(files[i].getDatasetName()));
        ui->processedDatasetTypeTable->setItem(i,2,new QTableWidgetItem(files[i].getDatasetComment()));

        int refMrDatasetNatureId = files[i].getRefMrDatasetNatureId();
        ui->processedDatasetTypeTable->setItem(i,3,new QTableWidgetItem(mrDatasetNatureList[refMrDatasetNatureId]));

        int refMrQualityProcedureTypeId = files[i].getRefMrQualityProcedureTypeId();
        ui->processedDatasetTypeTable->setItem(i,4,new QTableWidgetItem(mrDatasetQualityProcedureTypeList[refMrQualityProcedureTypeId]));
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::initConnections()
{
    QObject::connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(nameTextChanged(QString)));
    QObject::connect(ui->commentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(commentTextChanged(QString)));
    QObject::connect(ui->mrDatasetNatureComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(mrDatasetNatureComboBoxChanged(QString)));
    QObject::connect(ui->mrDatasetQualityProcedureTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(mrDatasetQualityProcedureTypeComboBoxChanged(QString)));
    QObject::connect(ui->processedDatasetTypeTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemTableChanged(QTableWidgetItem*)));
    QObject::connect(ui->checkAllButton, SIGNAL(clicked()), this, SLOT(checkAllClicked()));
    QObject::connect(ui->uncheckAllButton, SIGNAL(clicked()), this, SLOT(uncheckAllClicked()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::checkAllClicked()
{
    selectedRows.clear();
    for(int i=0; i<filesToUpload.size();i++)
    {
        selectedRows.append(i);
        QWidget *pWidget = ui->processedDatasetTypeTable->cellWidget(i,0);
        QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
        if (checkbox && !checkbox->isChecked())
            checkbox->setCheckState(Qt::Checked);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::uncheckAllClicked()
{
    selectedRows.clear();
    for(int i=0; i<filesToUpload.size();i++)
    {
        QWidget *pWidget = ui->processedDatasetTypeTable->cellWidget(i,0);
        QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
        if (checkbox && checkbox->isChecked())
            checkbox->setCheckState(Qt::Unchecked);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::resetClicked()
{
    selectedRows.clear();
    fillTable(filesToUploadInitial);
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::nameTextChanged(QString name)
{
    if(!selectedRows.isEmpty())
    {
        for(int i=0; i<selectedRows.size();i++)
        {
            ui->processedDatasetTypeTable->item(selectedRows[i],1)->setText(name);
        }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::commentTextChanged(QString comment)
{
    if(!selectedRows.isEmpty())
    {
        for(int i=0; i<selectedRows.size();i++)
        {
            ui->processedDatasetTypeTable->item(selectedRows[i],2)->setText(comment);
        }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::mrDatasetNatureComboBoxChanged(QString mrDatasetNature)
{
    if(!selectedRows.isEmpty())
    {
        // check value
        QList<int> ids = mrDatasetNatureList.keys(mrDatasetNature);
        if (!ids.isEmpty() || mrDatasetNature != "")
            for(int i=0; i<selectedRows.size();i++)
            {
                ui->processedDatasetTypeTable->item(selectedRows[i],3)->setText(mrDatasetNature);
            }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}
void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::mrDatasetQualityProcedureTypeComboBoxChanged(QString mrDatasetQualityProcedureType)
{
    if(!selectedRows.isEmpty())
    {
        QList<int> ids = mrDatasetQualityProcedureTypeList.keys(mrDatasetQualityProcedureType);
        if (!ids.isEmpty() || mrDatasetQualityProcedureType != "")
            for(int i=0; i<selectedRows.size();i++)
            {
                ui->processedDatasetTypeTable->item(selectedRows[i],4)->setText(mrDatasetQualityProcedureType);
            }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::itemTableChanged(QTableWidgetItem *item)
{
    int column = item->column();
    switch(column)
    {
    case 1:
            filesToUpload[item->row()].setDatasetName(item->text());
        break;
    case 2:
            filesToUpload[item->row()].setDatasetComment(item->text());
        break;
    case 3:
        if (item->text() != "")
        {
            QList<int> ids = mrDatasetNatureList.keys(item->text());
            if (!ids.isEmpty())
                filesToUpload[item->row()].setRefMrDatasetNatureId(ids.first());
            else
                item->setText("");
        }
        break;
    case 4:
        if (item->text() != "")
        {
            QList<int> ids = mrDatasetQualityProcedureTypeList.keys(item->text());
            if (!ids.isEmpty())
                filesToUpload[item->row()].setRefMrQualityProcedureTypeId(ids.first());
            else
                item->setText("");
        }
        break;
    }
    emit callUpdateMrDatasetFilesToUpload(filesToUpload);
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::addCheckBox(int i)
{
    QWidget * widget = new QWidget();
    QCheckBox* checkBox = new QCheckBox();

    QHBoxLayout* layout = new QHBoxLayout(widget);
    checkBox->setCheckState(Qt::Unchecked);

    QSignalMapper* ButtonSignalMapper = new QSignalMapper(this);
    ButtonSignalMapper->setMapping(checkBox,i);
    QObject::connect(checkBox, SIGNAL(clicked()), ButtonSignalMapper, SLOT(map()));
    QObject::connect(ButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(rowSelectionChanged(int)));

    layout->addWidget(checkBox);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);
    ui->processedDatasetTypeTable->setCellWidget(i,0,widget);
}

void QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::rowSelectionChanged(int row)
{
    QWidget *pWidget = ui->processedDatasetTypeTable->cellWidget(row, 0);
    QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
    if (checkbox && checkbox->isChecked())
    {
         selectedRows.append(row);
    }
    else
    {
        selectedRows.removeAll(row);
    }
}

QString QtShanoirUploadWidgetDatasetTypeDetailsMrDataset::reduceFilenameToTwoDir(QString filename)
{
    QString inter1 = filename.left(filename.lastIndexOf("/"));
    QString inter2 = inter1.left(inter1.lastIndexOf("/"));
    if (inter2.lastIndexOf("/") != -1)
    {
        return filename.right(filename.size()-inter2.lastIndexOf("/"));
    }
     else
        return filename;
}


