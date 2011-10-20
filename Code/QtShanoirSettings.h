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

#ifndef QTSHANOIRSETTINGS_H_
#define QTSHANOIRSETTINGS_H_

#include <QtGui>

class QtShanoirSettingsPrivate;

class QtShanoirSettings
{
    public:
        QtShanoirSettings();

        static QtShanoirSettings *
        Instance();

        const QString
        login();
        void
        setLogin(const QString & login);

        const QString
        password();
        void
        setPassword(const QString & password);

        const QString
        host();
        void
        setHost(const QString & host);

        const QString
        port();
        void
        setPort(const QString & port);

        const QString
        truststore();
        void
        setTruststore(const QString & trust);

        void
        update();

    private:
        void
        initializeSettings();

        void
        loadSettings();

        static QtShanoirSettings * instance; // QtShanoirSettings is a singleton
        QtShanoirSettingsPrivate * d;
};

#endif /* QTSHANOIRSETTINGS_H_ */
