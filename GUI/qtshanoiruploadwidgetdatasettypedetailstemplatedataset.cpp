#include "qtshanoiruploadwidgetdatasettypedetailstemplatedataset.h"
#include "ui_qtshanoiruploadwidgetdatasettypedetailstemplatedataset.h"

QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files,QWidget *parent) : QWidget(parent), ui(new Ui::QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset)
{
    ui->setupUi(this);
    fillComboBox();
    filesToUploadInitial = files;
    filesToUpload = files;
    buildTable();
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::fillComboBox()
{
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QMap<int,QString> (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("getTemplateDatasetNatureList");
    if (cf)
    {
        templateDatasetTypeList = cf();
        if (!templateDatasetTypeList.isEmpty())
        {
            ui->templateDatasetTypeComboBox->insertItem(0,"");
            for (int i=0; i<templateDatasetTypeList.size();i++)
                ui->templateDatasetTypeComboBox->insertItem(i+1,templateDatasetTypeList.values().at(i));
        }
    }
    else
        qDebug() << "could not call function";
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::buildTable()
{
    QStringList verticalLabels;
    QStringList horizontalLabels;
    for (int i=0;i<filesToUpload.size();i++)
    {
        verticalLabels.append(reduceFilenameToTwoDir(filesToUpload[i].getFilename()));
    }

    ui->processedDatasetTypeTable->setColumnCount(4);
    ui->processedDatasetTypeTable->setRowCount(verticalLabels.size());


    horizontalLabels << "" << tr("Name") << tr("Comment") << tr("Template Dataset Type");
    ui->processedDatasetTypeTable->setHorizontalHeaderLabels(horizontalLabels);
    ui->processedDatasetTypeTable->setVerticalHeaderLabels(verticalLabels);

    ui->processedDatasetTypeTable->resizeColumnsToContents();
    ui->processedDatasetTypeTable->resizeRowsToContents();

    fillTable(filesToUploadInitial);
    initConnections();
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files)
{
    //Add checkbox
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
            addCheckBox(i);

    //Add items
    for(int i=0;i<ui->processedDatasetTypeTable->rowCount();i++)
    {
        ui->processedDatasetTypeTable->setItem(i,1,new QTableWidgetItem(files[i].getDatasetName()));
        ui->processedDatasetTypeTable->setItem(i,2,new QTableWidgetItem(files[i].getDatasetComment()));

        int templateDatasetTypeId = files[i].getRefTemplateDatasetNatureId();
        ui->processedDatasetTypeTable->setItem(i,3,new QTableWidgetItem(templateDatasetTypeList[templateDatasetTypeId]));
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::initConnections()
{
    QObject::connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(nameTextChanged(QString)));
    QObject::connect(ui->commentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(commentTextChanged(QString)));
    QObject::connect(ui->templateDatasetTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(templateDatasetTypeComboBoxChanged(QString)));
    QObject::connect(ui->processedDatasetTypeTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemTableChanged(QTableWidgetItem*)));
    QObject::connect(ui->checkAllButton, SIGNAL(clicked()), this, SLOT(checkAllClicked()));
    QObject::connect(ui->uncheckAllButton, SIGNAL(clicked()), this, SLOT(uncheckAllClicked()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::checkAllClicked()
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

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::uncheckAllClicked()
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

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::resetClicked()
{
    selectedRows.clear();
    fillTable(filesToUploadInitial);
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::nameTextChanged(QString name)
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

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::commentTextChanged(QString comment)
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

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::templateDatasetTypeComboBoxChanged(QString templateDatasetType)
{
    if(!selectedRows.isEmpty())
    {
        // check value
        QList<int> ids = templateDatasetTypeList.keys(templateDatasetType);
        if (!ids.isEmpty() || templateDatasetType != "")
            for(int i=0; i<selectedRows.size();i++)
            {
                ui->processedDatasetTypeTable->item(selectedRows[i],3)->setText(templateDatasetType);
            }
    }
    else
    {
        QString message = QString("no file selected.");
        QMessageBox::warning(this,tr("Warning Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
    }
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::itemTableChanged(QTableWidgetItem *item)
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
            QList<int> ids = templateDatasetTypeList.keys(item->text());
            if (!ids.isEmpty())
                filesToUpload[item->row()].setRefTemplateDatasetNatureId(ids.first());
            else
                item->setText("");
        }
        break;
    }
    emit callUpdateTemplateDatasetFilesToUpload(filesToUpload);
}

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::addCheckBox(int i)
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

void QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::rowSelectionChanged(int row)
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


QString QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset::reduceFilenameToTwoDir(QString filename)
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

