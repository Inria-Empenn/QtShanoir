#include "qtshanoiruploadwidgetshowsteps.h"
#include<QDebug>
#include <QLabel>

QtShanoirUploadWidgetShowSteps::QtShanoirUploadWidgetShowSteps(QWidget *parent): QWidget(parent), ui (new Ui::QtShanoirUploadWidgetShowSteps)
{
    ui->setupUi(this);
}

void QtShanoirUploadWidgetShowSteps::steps(int i)
{
    QLabel*  selectFiles = new QLabel();
    QLabel*  selectInputDatasets = new QLabel();
    QLabel*  selectCoressFilesInputs = new QLabel();
    QLabel*  selectProcess = new QLabel();
    QLabel*  checkCoreespondance = new QLabel();
    QLabel*  datasetdetails = new QLabel();

    switch(i)
    {
    case 1:
    {

        selectFiles->setText("<img src=\":Images/arrow.12x12.png\"> Select files");

        selectInputDatasets->setText("<font color='grey'> Select input Datasets </font>");

        selectCoressFilesInputs->setText("<font color='grey'> Choose Files/Inputs </font>");

        selectProcess->setText("<font color='grey'> Select process </font>");

        checkCoreespondance->setText("<font color='grey'> Choose Files/Process & Dataset </font>");

        datasetdetails->setText("<font color='grey'> DatasetDetails </font>");
        break;
    }
    case 2:
    {
        selectFiles->setText("<img src=\":Images/true.12x12.png\">  <font color='grey'> Select files");


        selectInputDatasets->setTextFormat(Qt::RichText);
        selectInputDatasets->setText("<img src=\":Images/arrow.12x12.png\"> Select input Datasets");

        selectCoressFilesInputs->setText("<font color='grey'> Choose Files/Inputs </font>");

        selectProcess->setText("<font color='grey'> Select process </font>");

        checkCoreespondance->setText("<font color='grey'> Choose Files/Process & Dataset </font>");

        datasetdetails->setText("<font color='grey'> DatasetDetails </font>");

        break;
    }
    case 3:
    {
        selectFiles->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select files </font>");

        selectInputDatasets->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select input Datasets </font>");

        selectCoressFilesInputs->setTextFormat(Qt::RichText);
        selectCoressFilesInputs->setText("<img src=\":Images/arrow.12x12.png\"> Choose Files/Inputs");

        selectProcess->setText("<font color='grey'> Select process </font>");

        checkCoreespondance->setText("<font color='grey'> Choose Files/Process & Dataset </font>");

        datasetdetails->setText("<font color='grey'> DatasetDetails </font>");

        break;
    }
    case 4:
    {
        selectFiles->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select files </font>");

        selectInputDatasets->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select input Datasets </font>");

        selectCoressFilesInputs->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Inputs </font>");

        selectProcess->setTextFormat(Qt::RichText);
        selectProcess->setText("<img src=\":Images/arrow.12x12.png\"> Select process");

        checkCoreespondance->setText("<font color='grey'> Choose Files/Process & Dataset </font>");

        datasetdetails->setText("<font color='grey'> DatasetDetails </font>");

        break;
    }
    case 5:
    {
        selectFiles->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select files </font>");

        selectInputDatasets->setText("<img src=\":Images/true.12x12.png\"><font color='grey'> Select input Datasets </font>");

        selectCoressFilesInputs->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Inputs </font>");

        selectProcess->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select process </font>");

        checkCoreespondance->setTextFormat(Qt::RichText);
        checkCoreespondance->setText("<img src=\":Images/arrow.12x12.png\"> Choose Files/Process & Dataset");

        datasetdetails->setText("<font color='grey'> DatasetDetails </font>");

        break;
    }

    case 6:
    {
        selectFiles->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select files </font>");

        selectInputDatasets->setText("<img src=\":Images/true.12x12.png\"><font color='grey'> Select input Datasets </font>");

        selectCoressFilesInputs->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Inputs </font>");

        selectProcess->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Select process </font>");

        checkCoreespondance->setText("<img src=\":Images/true.12x12.png\"> <font color='grey'> Choose Files/Process & Dataset </font>");

        datasetdetails->setTextFormat(Qt::RichText);
        datasetdetails->setText("<img src=\":Images/arrow.12x12.png\"> DatasetDetails");
    }
    }

    ui->verticalLayout->addWidget(selectFiles);
    ui->verticalLayout->addWidget(selectInputDatasets);
    ui->verticalLayout->addWidget(selectCoressFilesInputs);
    ui->verticalLayout->addWidget(selectProcess);
    ui->verticalLayout->addWidget(checkCoreespondance);
    ui->verticalLayout->addWidget((datasetdetails));

}
