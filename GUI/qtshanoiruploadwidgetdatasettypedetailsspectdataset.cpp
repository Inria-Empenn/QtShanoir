#include "qtshanoiruploadwidgetdatasettypedetailsspectdataset.h"
#include "ui_qtshanoiruploadwidgetdatasettypedetailsspectdataset.h"

#include <QDebug>
#include <QLibrary>
#include <QMessageBox>

QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::QtShanoirUploadWidgetDatasettypeDetailsSpectDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent) : QWidget(parent), ui(new Ui::QtShanoirUploadWidgetDatasettypeDetailsSpectDataset)
{
    ui->setupUi(this);
    fillComboBoxes();
    filesToUploadInitial = files;
    filesToUpload = files;
    buildTable();
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::fillComboBoxes()
{
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QMap<int,QString> (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("getSpectNatureList");
    if (cf)
    {
        spectDatasetNatureList = cf();
        if (!spectDatasetNatureList.isEmpty())
        {
            ui->spectDatasetNatureComboBox->insertItem(0,"");
            for (int i=0; i<spectDatasetNatureList.size();i++)
                ui->spectDatasetNatureComboBox->insertItem(i+1,spectDatasetNatureList.values().at(i));
        }
    }
    else
        qDebug() << "could not call function";

    cf = (CallFunction)library.resolve("getProcessedDatasetTypeList");
        if (cf)
        {
            processedDatasetTypeList = cf();
            if (!processedDatasetTypeList.isEmpty())
            {
                ui->processedDatasetTypeComboBox->insertItem(0,"");
                for (int i=0; i<processedDatasetTypeList.size();i++)
                    ui->processedDatasetTypeComboBox->insertItem(i+1,processedDatasetTypeList.values().at(i));
            }
        }
        else
            qDebug() << "could not call function";
}


void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::buildTable()
{
    QStringList verticalLabels;
    QStringList horizontalLabels;
    for (int i=0;i<filesToUpload.size();i++)
    {
        verticalLabels.append(reduceFilenameToTwoDir(filesToUpload[i].getFilename()));
    }

    ui->processedDatasetTypeTable->setColumnCount(5);
    ui->processedDatasetTypeTable->setRowCount(verticalLabels.size());


    horizontalLabels << "" << tr("Name") << tr("Comment") << tr("Spect Dataset Nature") << tr("Processed Dataset Type");
    ui->processedDatasetTypeTable->setHorizontalHeaderLabels(horizontalLabels);
    ui->processedDatasetTypeTable->setVerticalHeaderLabels(verticalLabels);

    ui->processedDatasetTypeTable->resizeColumnsToContents();
    ui->processedDatasetTypeTable->resizeRowsToContents();

    fillTable(filesToUploadInitial);
    initConnections();
}


void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files)
{
    //Add checkbox
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
            addCheckBox(i);

    //Add items
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
    {
        ui->processedDatasetTypeTable->setItem(i,1,new QTableWidgetItem(files[i].getDatasetName()));
        ui->processedDatasetTypeTable->setItem(i,2,new QTableWidgetItem(files[i].getDatasetComment()));

        int refSpectDatasetNatureId = files[i].getRefSpectDatasetNatureId();
        ui->processedDatasetTypeTable->setItem(i,3,new QTableWidgetItem(spectDatasetNatureList[refSpectDatasetNatureId]));

        int refProcessedDatasetTypeId = files[i].getRefProcessedDatasetTypeId();
        ui->processedDatasetTypeTable->setItem(i,4,new QTableWidgetItem(processedDatasetTypeList[refProcessedDatasetTypeId]));
    }
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::initConnections()
{
    QObject::connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(nameTextChanged(QString)));
    QObject::connect(ui->commentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(commentTextChanged(QString)));
    QObject::connect(ui->spectDatasetNatureComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(spectDatasetNatureComboBoxChanged(QString)));
    QObject::connect(ui->processedDatasetTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(processedDatasetTypeComboBoxChanged(QString)));
    QObject::connect(ui->processedDatasetTypeTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemTableChanged(QTableWidgetItem*)));
    QObject::connect(ui->checkAllButton, SIGNAL(clicked()), this, SLOT(checkAllClicked()));
    QObject::connect(ui->uncheckAllButton, SIGNAL(clicked()), this, SLOT(uncheckAllClicked()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::checkAllClicked()
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

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::uncheckAllClicked()
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

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::resetClicked()
{
    selectedRows.clear();
    fillTable(filesToUploadInitial);
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::nameTextChanged(QString name)
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

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::commentTextChanged(QString comment)
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

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::spectDatasetNatureComboBoxChanged(QString spectDatasetNature)
{
    if(!selectedRows.isEmpty())
    {
        // check value
        QList<int> ids = spectDatasetNatureList.keys(spectDatasetNature);
        if (!ids.isEmpty() || spectDatasetNature != "")
            for(int i=0; i<selectedRows.size();i++)
            {
                ui->processedDatasetTypeTable->item(selectedRows[i],3)->setText(spectDatasetNature);
            }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}
void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::processedDatasetTypeComboBoxChanged(QString processedDatasetType)
{
    if(!selectedRows.isEmpty())
    {
        QList<int> ids = processedDatasetTypeList.keys(processedDatasetType);
        if (!ids.isEmpty() || processedDatasetType != "")
            for(int i=0; i<selectedRows.size();i++)
            {
                ui->processedDatasetTypeTable->item(selectedRows[i],4)->setText(processedDatasetType);
            }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::itemTableChanged(QTableWidgetItem *item)
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
            QList<int> ids = spectDatasetNatureList.keys(item->text());
            if (!ids.isEmpty())
                filesToUpload[item->row()].setRefSpectDatasetNatureId(ids.first());
            else
                item->setText("");
        }
        break;
    case 4:
        if (item->text() != "")
        {
            QList<int> ids = processedDatasetTypeList.keys(item->text());
            if (!ids.isEmpty())
                filesToUpload[item->row()].setRefProcessedDatasetTypeId(ids.first());
            else
                item->setText("");
        }
        break;
    }
    emit callUpdateSpectDatasetFilesToUpload(filesToUpload);
}

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::addCheckBox(int i)
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

void QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::rowSelectionChanged(int row)
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

QString QtShanoirUploadWidgetDatasettypeDetailsSpectDataset::reduceFilenameToTwoDir(QString filename)
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


