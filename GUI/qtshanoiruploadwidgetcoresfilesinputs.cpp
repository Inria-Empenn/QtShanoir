#include "qtshanoiruploadwidgetcoresfilesinputs.h"
#include <QtGui>
#include <QCheckBox>
#include <QMessageBox>


QtShanoirUploadWidgetCoresFilesInputs::QtShanoirUploadWidgetCoresFilesInputs(QWidget *parent): QWizardPage(parent), ui (new Ui::QtShanoirUploadWidgetCoresFilesInputs)
{
    ui->setupUi(this);
    setButtonText(QWizard::NextButton,tr("Next >"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));

    attachShowStepsWidget(ui->steps);
    showsteps->steps(3);

    //Explain step
    ui->detailsLabel->setText(tr("<b> Step 3 : </b> Match your files with the correct input Datasets."));


}

void QtShanoirUploadWidgetCoresFilesInputs::attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* widget)
{
    showsteps = widget;
}

void QtShanoirUploadWidgetCoresFilesInputs::initConnections()
{
    QObject::connect(ui->uncheckButton,SIGNAL(pressed()),this, SLOT (resetClicked()));
    QObject::connect(ui->checkAllButton,SIGNAL(pressed()),this, SLOT (checkAllClicked()));
}

void QtShanoirUploadWidgetCoresFilesInputs::resetClicked()
{
    ui->filesInputsTable->clearContents();
    for (int i=0;i<ui->filesInputsTable->rowCount();i++)
        for(int j=0;j<ui->filesInputsTable->columnCount();j++)
            addCheckBox(i,j);
}

void QtShanoirUploadWidgetCoresFilesInputs::buildTable()
{
    ui->filesInputsTable->setColumnCount(selectedInputsDatasetIds.size());
    ui->filesInputsTable->setRowCount(filesList.size());
    ui->filesInputsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    foreach (QString value, filesList)
        verticalLabels.append(reduceFilenameToTwoDir(value));
    ui->filesInputsTable->setVerticalHeaderLabels(verticalLabels);

    QStringList horizontalLabels;
    for (int i=0; i<selectedInputsDatasetIds.size();i++)
        horizontalLabels.append(selectedInputsDatasetIds.values().at(i));
    ui->filesInputsTable->setHorizontalHeaderLabels(horizontalLabels);

    for(int i=0;i<ui->filesInputsTable->rowCount();i++)
        for(int j=0;j<ui->filesInputsTable->columnCount();j++)
            addCheckBox(i,j);

    initConnections();
    //ui->filesInputsTable->resizeColumnsToContents();
    //ui->filesInputsTable->resizeRowsToContents();

}

void QtShanoirUploadWidgetCoresFilesInputs::addCheckBox(int row, int colum)
{
    QWidget * widget = new QWidget();
    QCheckBox* checkBox = new QCheckBox();


    QHBoxLayout* layout = new QHBoxLayout(widget);
    checkBox->setCheckState(Qt::Unchecked);

    QString row_colum = QString::number(row)+"_"+ QString::number(colum);
    QSignalMapper* ButtonSignalMapper = new QSignalMapper(this);
    ButtonSignalMapper->setMapping(checkBox,row_colum);
    QObject::connect(checkBox, SIGNAL(clicked()), ButtonSignalMapper, SLOT(map()));
    QObject::connect(ButtonSignalMapper, SIGNAL(mapped(QString)), this, SLOT(cellCheckBoxChanged(QString)));

    layout->addWidget(checkBox);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);
    ui->filesInputsTable->setCellWidget(row,colum,widget);
}

void QtShanoirUploadWidgetCoresFilesInputs::cellCheckBoxChanged(QString row_colum)
{
    int row = QString(row_colum.left(row_colum.lastIndexOf("_"))).toInt();
    int column = QString(row_colum.right(row_colum.size()-row_colum.lastIndexOf("_")-1)).toInt();

    QWidget *pWidget = ui->filesInputsTable->cellWidget(row, column);
    QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
    if (checkbox && checkbox->isChecked())
    {
         qDebug()<<"checked";
    }
    else
        qDebug()<<"unchecked";

}
void QtShanoirUploadWidgetCoresFilesInputs::updateFilesList(QStringList files)
{
    this->filesList = files;
    buildTable();
}

bool QtShanoirUploadWidgetCoresFilesInputs::validatePage()
{
    bool exist;
    for (int i=0; i<ui->filesInputsTable->rowCount();i++)
    {
        exist = matchExist(i);
        if (!exist)
        {
            QString filename = reduceFilenameToTwoDir(verticalLabels.value(i));
            QString message = QString("Can not find match for file << %1 >> in row %2.").arg(filename).arg(QString::number(i));
            QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
            break;
        }
    }

    // save match files/inputs
    if (exist)
    {
        for(int i=0; i<filesToUpload.size();i++)
        {
            if (filesToUpload[i].getFilename()== filesList.value(i))
                    filesToUpload[i].setInputDatasetIdList(getInputsDatasetIds(i));
        }
        emit callUpdateFilesToUpload(filesToUpload);
    }
    return exist;
}

QList<int> QtShanoirUploadWidgetCoresFilesInputs::getInputsDatasetIds(int row)
{
    QList<int> list;
    for (int i=0; i<ui->filesInputsTable->columnCount();i++)
    {
        QWidget *pWidget = ui->filesInputsTable->cellWidget(row, i);
        QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
        if (checkbox && checkbox->isChecked())
        {

            list.append(selectedInputsDatasetIds.keys().at(i));
        }
    }
    return list;
}

bool QtShanoirUploadWidgetCoresFilesInputs::matchExist(int row)
{
    bool matchExist = false;
    for (int i=0; i<ui->filesInputsTable->columnCount();i++)
    {
        QWidget *pWidget = ui->filesInputsTable->cellWidget(row, i);
        QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
        if (checkbox && checkbox->isChecked())
        {
            matchExist = true;
            break;
        }
    }
    return matchExist;
}

void QtShanoirUploadWidgetCoresFilesInputs::updateSelectedInputsDataset(QMap<int,QString> list)
{
    this->selectedInputsDatasetIds = list;
    buildTable();
}

QString QtShanoirUploadWidgetCoresFilesInputs::reduceFilenameToTwoDir(QString filename)
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

void QtShanoirUploadWidgetCoresFilesInputs::checkAllClicked() // a revoir s'il y 'a mieux
{
    for (int i=0;i<ui->filesInputsTable->rowCount();i++)
        for(int j=0;j<ui->filesInputsTable->columnCount();j++)
        {
            QWidget *pWidget = ui->filesInputsTable->cellWidget(i, j);
            QCheckBox *checkbox = pWidget->findChild<QCheckBox *>();
            if (checkbox && !checkbox->isChecked())
            {
                checkbox->setCheckState(Qt::Checked);
                QString row_colum = QString::number(i)+"_"+ QString::number(j);
                cellCheckBoxChanged(row_colum);
            }
        }
}

void QtShanoirUploadWidgetCoresFilesInputs::updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> list)
{
    this->filesToUpload = list;
}
