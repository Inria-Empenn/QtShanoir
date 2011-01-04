#include "QtShanoirConfiguration.h"
#include "ui_qtshanoirconfiguration.h"

ShanoirServerParameters::ShanoirServerParameters(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ShanoirServerParameters)
{
    ui->setupUi(this);
}

ShanoirServerParameters::~ShanoirServerParameters()
{
    delete ui;
}

void ShanoirServerParameters::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void ShanoirServerParameters::getParameters(QString &user, QString &password, QString &host, QString &port)
{
    user = ui->username->text().trimmed();
    password = ui->password->text().trimmed();
    host = ui->host->text().trimmed();
    port = ui->port->text().trimmed();
}
