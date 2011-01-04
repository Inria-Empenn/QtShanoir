#ifndef QT_SHANOIR_H
#define QT_SHANOIR_H

#include <QDialog>
#include <QtSoap.h>
#include <QNetworkRequest>

namespace Ui {
    class QtShanoir;
}


struct WsQuery: public QObject
{
    Q_OBJECT
public:
    WsQuery(): displayResult(false) {}
    WsQuery(QString ws) : WebService(ws), displayResult(false) {}
    WsQuery(QString ws, QString im) : WebService(ws), WsImpl(im), displayResult(false) {}

    QString WebService;
    QString WsImpl; // WebService implementation
    bool displayResult;

    QString WsMethod;
    QList<QPair<QString,QString> > WsMethodarg;

    void answer(QString string) const;
signals:
    void response(QString string) const;
};

class QTreeWidgetItem;
class QListWidgetItem;
class QNetworkRequest;
class QIcon;

class QtShanoir : public QDialog {
    Q_OBJECT
public:
    QtShanoir(QWidget *parent = 0);
    ~QtShanoir();

    void doQuery(QString);

protected:
    void changeEvent(QEvent *e);
    void prepareMessage();
    // Create the Queries for a specific
    void populateQueries();
    // Push the login stack for this ws.
    void setLogin(QString key, QString ws, QString impl = "http://finder.impl.webservices.shanoir.org");
    void setMrExamQuery(QString key, QString id);
    void setDownload(QString key, QString id);
    void setDatasetQuery(QString key, QString id, QString exId);
signals:
    void nextMessage();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void on_toolButton_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);
    void on_actionQuit_triggered();
    void getResponse();
    void sslErrors ( const QList<QSslError> & errors );
    void sendMessage();
    void parseStudy(QString xmlserial);
    void parseMrExamination(QString xmlserial);
    void parseAcquisition(QString xmlserial);
    void download(QString xmlserial);
    void getError(QString);
    void setConfiguration();
    void downloadProgress ( qint64 bytesReceived, qint64 bytesTotal );
    void uploadProgress ( qint64 bytesSent, qint64 bytesTotal );
private:
    int num_message;
    Ui::QtShanoir *ui;
    QtSoapHttpTransport http;
    QString user, password, host, port, truststore;
    QNetworkRequest req;
    QIcon *ico_shanoir, *ico_study, *ico_subject, *ico_exam, *ico_acq;

    // the server, the namespace of the ws and the ws name
    QString wsimpl, ws;

    const WsQuery* query;

    // Fill the following map with the properly set up query
    QMap<QString, QList<WsQuery*> > perWsQuery;
    int curId;

//    QString WsMethod;
//    QList<QPair<QString,QString> > WsMethodarg;
};



#endif // QT_SHANOIR_H
