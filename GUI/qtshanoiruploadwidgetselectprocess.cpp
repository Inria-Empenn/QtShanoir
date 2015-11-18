#include "qtshanoiruploadwidgetselectprocess.h"
#include <QMessageBox>
QtShanoirUploadWidgetSelectProcess::QtShanoirUploadWidgetSelectProcess(QWidget *parent): QWizardPage(parent), ui (new Ui::QtShanoirUploadWidgetSelectProcess)
{

    ui->setupUi(this);

    setButtonText(QWizard::NextButton,tr("Next >"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));
    attachShowStepsWidget(ui->steps);
    showsteps->steps(4);

    //Explain step
        ui->detailsLabel->setText(tr("<b> Step 4 : </b> Select the list of process."));

    ui->processLabel->setText(tr("Process : <font color='red'>*</font>"));

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QMap<int,QString> (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("getProcessingList");
    if (cf)
    {
        processList = cf();
        if (!processList.isEmpty())
        {
            for (int i=0; i<processList.size();i++)
            {
                QListWidgetItem* item = new QListWidgetItem(processList.values().at(i));
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(Qt::Unchecked);
                ui->listWidget->addItem(item);
            }
        }
    }
    else
        qDebug() << "could not call function";

    initConnections();
}

void QtShanoirUploadWidgetSelectProcess::initConnections()
{
    QObject::connect(ui->selectAllButton,SIGNAL(pressed()),this, SLOT (selectAllClicked()));
    QObject::connect(ui->unselectAllButton,SIGNAL(pressed()),this, SLOT (unselectAllClicked()));
    QObject::connect(ui->listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this, SLOT(updateCheckBoxes(QListWidgetItem*)));
}

void QtShanoirUploadWidgetSelectProcess::unselectAllClicked()
{
    selectedProcessList.clear();
    for (int i=0; i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
        selectedProcessList.insert(processList.keys().at(i),processList.values().at(i));
    }
    emit callUpdateProcessList(selectedProcessList);

}

void QtShanoirUploadWidgetSelectProcess::selectAllClicked()
{
    for (int i=0; i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
    selectedProcessList.clear();
    emit callUpdateProcessList(selectedProcessList);
}

void QtShanoirUploadWidgetSelectProcess::updateCheckBoxes(QListWidgetItem * item)
{
    QList<int> processIds = processList.keys(item->text());
    if (item->checkState() == Qt::Checked)
    {
        selectedProcessList.insert(processIds.first(),item->text());

    }
    else
    {
        int d = selectedProcessList.remove(processIds.first()); // remove return int number of item deleted
    }
    emit callUpdateProcessList(selectedProcessList);

}

void QtShanoirUploadWidgetSelectProcess::attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* widget)
{
    showsteps = widget;
}

bool QtShanoirUploadWidgetSelectProcess::validatePage()
{
    if (processList.isEmpty())
        QMessageBox::critical(this,tr("Error Message"),tr("You should select at least one process."),QMessageBox::Ok,0);
    return !processList.isEmpty();
}
