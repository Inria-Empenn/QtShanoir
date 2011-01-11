/*
 * QtShanoirController.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRCONTROLLER_H_
#define QTSHANOIRCONTROLLER_H_

#include <QtGui>
#include <QtSoap.h>

class QNetworkRequest;
class QtShanoirTreeWidget;
class QtShanoirProgressWidget;
class QtShanoirPrivate;

class QtShanoir : public QObject
{
    Q_OBJECT
    public:
        QtShanoir();

        void
        initWS();
        void
        doQuery(QString);
        void
        attachTreeWidget(QtShanoirTreeWidget * tree);
        void
        attachProgressWidget(QtShanoirProgressWidget * progress);
        void clearTree();

    public slots:
        void download();

    protected:
        void
        prepareMessage();
        // Create the Queries for a specific
        void
        populateQueries();
        // Push the login stack for this ws.
        void setLogin(QString key, QString ws, QString impl = "http://finder.impl.webservices.shanoir.org");
        void setMrExamQuery(QString key, QString id);
        void setDownload(QString key, QString id);
        void setFilename(QString key, QString id);
        void setDatasetQuery(QString key, QString id, QString exId);
    signals:
        void nextMessage();
        void startDownload();
        void getFileName();

    private slots:
        void getResponse();
        void sslErrors ( const QList<QSslError> & errors );
        void sendMessage();
        void download(QString xmlserial);
        void callDownloadWS();
        void callGetFileNameWS();
        void getFileName(QString xmlserial);
        void getError(QString);
        void updateSelected(QList<int>);
        void setDownloadFilename(QString filename);
        void downloadProgress ( qint64 bytesReceived, qint64 bytesTotal );
//        void uploadProgress ( qint64 bytesSent, qint64 bytesTotal );
        void
        mrExamQuery(QString);
        void
        datasetQuery(QString, QString);
        void
        currentId(int);
        void
        queryFinished();



    private:
        QtShanoirPrivate * d;
};

#endif /* QTSHANOIRCONTROLLER_H_ */
