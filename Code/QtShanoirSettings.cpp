/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <QtShanoirSettings.h>
#include <QSettings>

class QtShanoirSettingsPrivate
{
    public:
        QString login, password, host, port, truststore;
        QSettings settings;
        QString iniFile;

};

QtShanoirSettings * QtShanoirSettings::instance = 0;

QtShanoirSettings::QtShanoirSettings() :
    d(new QtShanoirSettingsPrivate)
{
    QDir iniDir(QDir::homePath() + QDir::separator() + ".shanoir");
    if (!iniDir.exists())
        QDir(QDir::homePath()).mkdir(".shanoir");

    d->iniFile = iniDir.absolutePath() + QDir::separator() + "properties";
    this->loadSettings();
}

void
QtShanoirSettings::loadSettings()
{
    if (!QFile(d->iniFile).exists())
        this->initializeSettings();
    else {
        QSettings prefs(d->iniFile, QSettings::IniFormat);
        prefs.beginGroup("User");
        d->login = prefs.value("login").toString();
        d->password = prefs.value("password").toString();
        prefs.endGroup();
        prefs.beginGroup("Server");
        d->host = prefs.value("host").toString();
        d->port = prefs.value("port").toString();
        prefs.endGroup();
        prefs.beginGroup("Security");
        d->truststore = prefs.value("truststore").toString();
        prefs.endGroup();
    }
}

void
QtShanoirSettings::initializeSettings()
{
    d->login = "guest";
    d->password = "guest";
    d->host = "shanoir.org";
    d->port = "8443";
    d->truststore = "";
    this->update();
}

void
QtShanoirSettings::update()
{
    QFile ini(d->iniFile);
    ini.remove();
    QSettings prefs(d->iniFile, QSettings::IniFormat);
    prefs.beginGroup("User");
    prefs.setValue("login", d->login);
    prefs.setValue("password", d->password);
    prefs.endGroup();
    prefs.beginGroup("Server");
    prefs.setValue("host", d->host);
    prefs.setValue("port", d->port);
    prefs.endGroup();
    prefs.beginGroup("Security");
    prefs.setValue("truststore", d->truststore);
    prefs.endGroup();
}

const QString
QtShanoirSettings::login()
{
    return d->login;
}

void
QtShanoirSettings::setLogin(const QString & login)
{
    d->login = login;
}

const QString
QtShanoirSettings::password()
{
    return d->password;
}

void
QtShanoirSettings::setPassword(const QString & pass)
{
    d->password = pass;
}

const QString
QtShanoirSettings::port()
{
    return d->port;
}

void
QtShanoirSettings::setPort(const QString & port)
{
    d->port = port;
}

const QString
QtShanoirSettings::host()
{
    return d->host;
}

void
QtShanoirSettings::setHost(const QString & host)
{
    d->host = host;
}

const QString
QtShanoirSettings::truststore()
{
    return d->truststore;
}

void
QtShanoirSettings::setTruststore(const QString & trust)
{
    d->truststore = trust;
}

QtShanoirSettings *
QtShanoirSettings::Instance()
{
    if (instance == 0)
        instance = new QtShanoirSettings();
    return instance;
}
