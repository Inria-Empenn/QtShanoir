#include "qtshanoirsearchwidget.h"
//#include "qtshanoirmain.h"

QtShanoirSearchWidget::QtShanoirSearchWidget(QWidget *parent): QWidget(parent),ui (new Ui::QtShanoirSearchWidget)
{
    ui->setupUi(this);
    this->reset();
    initConnections();
}

void QtShanoirSearchWidget::initConnections()
{
    QObject::connect(ui->studyNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(studyTextChanged(QString)));
    QObject::connect(ui->patientNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(patientTextChanged(QString)));
    QObject::connect(ui->examinationDateDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(examDateChanged(QDate)));
    QObject::connect(ui->datasetNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(datasetTextChanged(QString)));
}

void QtShanoirSearchWidget::reset()
{
    ui->studyNameLineEdit->setText("");
    ui->studyNameLineEdit->setToolTip("Enter study name");
    this->studyTextChanged("");

    ui->patientNameLineEdit->setText("");
    ui->patientNameLineEdit->setToolTip("Enter first study name and then patient name");
    this->patientTextChanged("");

    ui->examinationDateDateEdit->setSpecialValueText(" ");
    QDate defaultDate (1,1,1);
    ui->examinationDateDateEdit->setDate(defaultDate);
    ui->examinationDateDateEdit->setToolTip("Enter first study name and patient name and then examination date");
    this->examDateChanged(defaultDate);

    ui->datasetNameLineEdit->setText("");
    ui->datasetNameLineEdit->setToolTip("Enter first study name, patient name and examination date the dataset name");
    this->datasetTextChanged("");
}

void QtShanoirSearchWidget::studyTextChanged(QString text)
{
    if(ui->studyNameLineEdit->text()!="")
    {
        ui->patientNameLineEdit->setEnabled(1);
    }
    else
    {
        ui->patientNameLineEdit->setDisabled(1);
        ui->patientNameLineEdit->setText("");

        ui->examinationDateDateEdit->setDisabled(1);
        ui->examinationDateDateEdit->setSpecialValueText(" ");
        QDate defaultDate (1,1,1);
        ui->examinationDateDateEdit->setDate(defaultDate);

        ui->datasetNameLineEdit->setDisabled(1);
        ui->datasetNameLineEdit->setText("");
    }

}

void QtShanoirSearchWidget::patientTextChanged(QString text)
{
    if(ui->patientNameLineEdit->text()!="")
    {
        ui->examinationDateDateEdit->setEnabled(1);
    }
    else
    {
        ui->examinationDateDateEdit->setDisabled(1);
        ui->examinationDateDateEdit->setSpecialValueText(" ");
        QDate defaultDate (1,1,1);
        ui->examinationDateDateEdit->setDate(defaultDate);

        ui->datasetNameLineEdit->setDisabled(1);
        ui->datasetNameLineEdit->setText("");
    }
}

void QtShanoirSearchWidget::examDateChanged(QDate date)
{
    QDate defaultDate (1752,9,14);
    if(ui->examinationDateDateEdit->date()!= defaultDate)
    {
        ui->datasetNameLineEdit->setEnabled(1);
    }
    else
    {
        ui->datasetNameLineEdit->setDisabled(1);
        ui->datasetNameLineEdit->setText("");
    }


}

void QtShanoirSearchWidget::datasetTextChanged(QString text)
{

}

void QtShanoirSearchWidget::findValidation()
{
    emit startFind(ui->studyNameLineEdit->text(),ui->patientNameLineEdit->text(),ui->examinationDateDateEdit->date(),ui->datasetNameLineEdit->text());

}
