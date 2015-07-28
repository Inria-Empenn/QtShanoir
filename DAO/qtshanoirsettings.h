#ifndef QTSHANOIRSETTINGS
#define QTSHANOIRSETTINGS

#include <QtCore>
#include <QSettings>
#include <QFile>



class  QtShanoirSettings
{
private:
    QString login;
    QString password;
    QString host;
    int port;
    QString truststore;

public:
    void loadSettings(QString);
    void initializeSettings(QString);
    void update(QString);

    QString getLogin();
    void setLogin(const QString &);
    QString getPassword();
    void setPassword(const QString &);
    QString getHost();
    void setHost(const QString &);
    int getPort();
    void setPort(int);
    QString getTrustore();
    void setTrustore(const QString &);
};

#endif // QTSHANOIRSETTINGS

