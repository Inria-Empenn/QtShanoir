
#include"qtshanoirsettings.h"


void QtShanoirSettings::loadSettings(QString iniFile)
{
     QFile file(iniFile);
        if (file.exists() == false)
        this->initializeSettings(iniFile);
    else
    {
        QSettings prefs(iniFile,QSettings::IniFormat);
        prefs.beginGroup("User");
        login = prefs.value("login").toString();
        password = prefs.value("password").toString();
        prefs.endGroup();
        prefs.beginGroup("Server");
        host = prefs.value("host").toString();
        port = prefs.value("port").toInt();
        prefs.endGroup();
        prefs.beginGroup("Security");
        truststore = prefs.value("truststore").toString();
        prefs.endGroup();
    }
}

void QtShanoirSettings::initializeSettings(QString iniFile)
{
    login = "ttest";
    password = "shanoir$1";
    host = "shanoir-qualif.irisa.fr";
    port = 0;//8843
    truststore = "";
    this->update(iniFile);
}

void QtShanoirSettings::update(QString iniFile)
{
    QFile ini(iniFile);
    ini.remove();
    QSettings prefs(iniFile,QSettings::IniFormat);
    prefs.beginGroup("User");
    prefs.setValue("login",login);
    prefs.setValue("password",password);
    prefs.endGroup();
    prefs.beginGroup("Server");
    prefs.setValue("host",host);
    prefs.setValue("port",port);
    prefs.endGroup();
    prefs.beginGroup("Security");
    prefs.setValue("truststore",truststore);
    prefs.endGroup();
}

QString QtShanoirSettings::getLogin()
{
    return this->login;
}

void QtShanoirSettings::setLogin(const QString & login)
{
    this->login = login;
}

QString QtShanoirSettings::getPassword()
{
    return this->password;
}

void QtShanoirSettings::setPassword(const QString & password)
{
    this->password = password;
}

QString QtShanoirSettings::getHost()
{
    return this->host;
}

void QtShanoirSettings::setHost(const QString & host)
{
    this->host = host;
}

int QtShanoirSettings::getPort()
{
    return this->port;
}

void QtShanoirSettings::setPort(int port)
{
    this->port = port;
}

QString QtShanoirSettings::getTrustore()
{
    return this->truststore;
}

void QtShanoirSettings::setTrustore(const QString & truststore)
{
    this->truststore = truststore;
}
