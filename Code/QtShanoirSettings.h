/*
 * QtShanoirSettings.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
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
