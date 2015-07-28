#include "qtshanoiruploadwidgetselectinputs.h"

QtShanoirUploadWidgetSelectInputs::QtShanoirUploadWidgetSelectInputs(QWidget *parent): QWizardPage(parent), ui (new Ui::QtShanoirUploadWidgetSelectInputs)
{
    ui->setupUi(this);
    setButtonText(QWizard::NextButton,tr("Next >"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));

    attchShowStepsWidget(ui->steps);
    showsteps->steps(2);

    //Explain step
    ui->detailsLabel->setText(tr("<b> Step 2 : </b> Select the input Datasets corresponding to files early selected."));

    ui->selectLabel->setText("Input Datasets :");

    tree = new QtShanoirTreeWidget();

}

void QtShanoirUploadWidgetSelectInputs::attchShowStepsWidget(QtShanoirUploadWidgetShowSteps* widget)
{
    showsteps = widget;
}

void QtShanoirUploadWidgetSelectInputs::initConnections()
{
    QObject::connect(tree, SIGNAL(callUpdateSelectedIds(QMap<int,QString>)), this, SLOT(updateSelectedIds(QMap<int,QString>)));
}

void QtShanoirUploadWidgetSelectInputs::attachTreeWidget(QtShanoirTreeWidget * widget)
{
    tree = widget;
    if (tree)
    {
        QDate defaultDate (1752,9,14);
        tree->build(studySelected,"",defaultDate,"");
        initConnections();
    }
}

void QtShanoirUploadWidgetSelectInputs::selectStudy(QString study)
{
    this->studySelected = study;
    attachTreeWidget(ui->treeWidget);
}

void QtShanoirUploadWidgetSelectInputs::updateSelectedIds (QMap<int,QString> list)
{
    this->selectedInputsDatasetIds = list;
    ui->detailsnuminputLabel->setText(QString("%1 files selected").arg(selectedInputsDatasetIds.size()));
    emit callUpdateSelectedInputsDataset(selectedInputsDatasetIds);
}

bool QtShanoirUploadWidgetSelectInputs::validatePage()
{
    if (selectedInputsDatasetIds.isEmpty())
            QMessageBox::critical(this,tr("Error Message"),tr("You should select input Dataset."),QMessageBox::Ok,0);

    return !(selectedInputsDatasetIds.isEmpty());
}


