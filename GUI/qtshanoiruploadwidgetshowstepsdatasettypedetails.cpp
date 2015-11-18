#include "qtshanoiruploadwidgetshowstepsdatasettypedetails.h"
#include "ui_qtshanoiruploadwidgetshowstepsdatasettypedetails.h"

QtShanoirUploadWidgetShowStepsDatasetTypeDetails::QtShanoirUploadWidgetShowStepsDatasetTypeDetails(QWidget *parent) : QWidget(parent), ui(new Ui::QtShanoirUploadWidgetShowStepsDatasetTypeDetails)
{
    ui->setupUi(this);
}

void QtShanoirUploadWidgetShowStepsDatasetTypeDetails::buildUpdateSteps(QMap<QString,int> datasetTypeSelectedList)
{
    clearWidget();

    QLabel*  selectFiles = new QLabel();
    QLabel*  selectInputDatasets = new QLabel();
    QLabel*  selectCoressFilesInputs = new QLabel();
    QLabel*  selectProcess = new QLabel();
    QLabel*  checkCoreespondance = new QLabel();
    QLabel*  datasetdetails = new QLabel();

    selectFiles->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select files </font>");

    selectInputDatasets->setText("<img src=\":Images/true.12x12.png\"><font color='grey'> Select input Datasets </font>");

    selectCoressFilesInputs->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Inputs </font>");

    selectProcess->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select process </font>");

    checkCoreespondance->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Process & Dataset </font>");

    datasetdetails->setTextFormat(Qt::RichText);
    datasetdetails->setText("<img src=\":Images/arrow.12x12.png\"> DatasetDetails");

    ui->verticalLayout->addWidget(selectFiles);
    ui->verticalLayout->addWidget(selectInputDatasets);
    ui->verticalLayout->addWidget(selectCoressFilesInputs);
    ui->verticalLayout->addWidget(selectProcess);
    ui->verticalLayout->addWidget(checkCoreespondance);
    ui->verticalLayout->addWidget((datasetdetails));

    for(int i=0;i<datasetTypeSelectedList.size();i++)
    {
        QLabel*  datasetType = new QLabel();
        if(datasetTypeSelectedList.values().at(i)== 0)
            datasetType->setText(QString("<img src=\":Images/delete.12x12.png\"> <font size='2'> %1 </font>").arg(datasetTypeSelectedList.keys().at(i)));
        else if (datasetTypeSelectedList.values().at(i)== 1)
                datasetType->setText(QString("<img src=\":Images/true.12x12.png\"> <font size='2'> %1 </font>").arg(datasetTypeSelectedList.keys().at(i)));
        ui->verticalLayout->addWidget((datasetType));
    }
}

void QtShanoirUploadWidgetShowStepsDatasetTypeDetails::clearWidget()
{
    while (ui->verticalLayout->count())
    {
        QWidget* widget = ui->verticalLayout->itemAt(0)->widget();
        ui->verticalLayout->removeWidget(widget);
        delete widget;
    }
}

