#include "qtshanoirsettingswidget.h"


QtShanoirSettingsWidget::QtShanoirSettingsWidget(QWidget *parent): QWidget (parent)
{
    setupUi(this);
    portSpinBox->setMaximum(9999);

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef struct Settings* (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("loadSettings");
    if (cf)
    {
         struct Settings* settings = cf();
         loginLineEdit->setText(settings->login);
         passwordLineEdit->setText(settings->password);
         passwordLineEdit->setEchoMode(QLineEdit::Password);
         passwordLineEdit->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
         hostLineEdit->setText(settings->host);
         portSpinBox->setValue(settings->port);
         portSpinBox->setMaximum(9999);
         initConnections();
    }
    else
        qDebug() << "could not call function";


}

void QtShanoirSettingsWidget::initConnections()
{
    QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(connect()));
    QObject::connect(loginLineEdit, SIGNAL(textChanged(QString)), this, SLOT(loginTextChanged(QString)));
    QObject::connect(passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(passwordTextChanged(QString)));
    QObject::connect(hostLineEdit, SIGNAL(textChanged(QString)), this, SLOT(hostTextChanged(QString)));
    QObject::connect(portSpinBox, SIGNAL(valueChanged(int)), this, SLOT(portValueChanged(int)));
}

void QtShanoirSettingsWidget::loginTextChanged(QString text)
{
    //GlobalData::settings.setLogin(text.trimmed());
    //GlobalData::settings.update();
}

void QtShanoirSettingsWidget::passwordTextChanged(QString text)
{
    //GlobalData::settings.setPassword(text.trimmed());
    //GlobalData::settings.update();
}

void QtShanoirSettingsWidget::hostTextChanged(QString text)
{

}

void QtShanoirSettingsWidget::portValueChanged(int value)
{
    //GlobalData::settings.setPort(value.toInt());
    //GlobalData::settings.update();
}

void QtShanoirSettingsWidget::connect()
{
    struct Settings* settings = new struct Settings;
    settings->login = loginLineEdit->text();
    settings->password = passwordLineEdit->text();
    settings->host = hostLineEdit->text();
    settings->port = portSpinBox->value();

    QDir iniDir (QDir::homePath() + QDir::separator() + ".shanoir");
    QString iniFile = iniDir.absolutePath() + QDir::separator() + "properties";

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef void (* CallFunction)(struct Settings*,QString);
    CallFunction cf = (CallFunction)library.resolve("updateSettings");
    if (cf)
    {
          cf(settings,iniFile);
    }
    else
        qDebug() << "could not call function";

    connectServer();
}

void QtShanoirSettingsWidget::connectServer()
{
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QString (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("authentification");
    if (cf)
    {
          QString error = cf();
          if (error != "")
          {
              QMessageBox::critical(this, "Error message", error, QMessageBox::Ok, 0);
          }
          else
          {
              QMessageBox::information(this, "Information message", "You are successfully connected.", QMessageBox::Ok, 0);
              emit callServer();
          }
    }
    else
        qDebug() << "could not call function";
}
