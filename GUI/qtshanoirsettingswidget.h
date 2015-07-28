#ifndef QTSHANOIRSETTINGSWIDGET
#define QTSHANOIRSETTINGSWIDGET

#include<QtGui>
#include "ui_qtshanoirsettingswidget.h"
#include "qtshanoirsettings.h"
#include "qtshanoirmain.h"

typedef struct Settings
{
    QString login;
    QString password;
    QString host;
    int port;
    QString truststore;
}Settings;

class  QtShanoirSettingsWidget : public QWidget, private Ui::QtShanoirSettings
{
    Q_OBJECT
public:
    explicit QtShanoirSettingsWidget(QWidget * parent = 0);
    void connectServer();

signals:
    void callServer();
    void queryFailed(QString);

public slots:
    void initConnections();
    void loginTextChanged(QString);
    void passwordTextChanged(QString);
    void hostTextChanged(QString);
    void portValueChanged(int);
    void connect();

};

#endif // QTSHANOIRSETTINGSWIDGET

