/*
 * QtShanoirController.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRCONTROLLER_H_
#define QTSHANOIRCONTROLLER_H_

#include <QtGui>
#include <QNetworkRequest>

class QNetworkRequest;
class QtShanoirControllerPrivate;

class QtShanoirController : public QObject
{
    Q_OBJECT
    public:
        QtShanoirController();

        void
        doQuery(QString);

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
        void setDatasetQuery(QString key, QString id, QString exId);
    signals:
        void nextMessage();

    private slots:
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
        QtShanoirControllerPrivate * d;
};

#endif /* QTSHANOIRCONTROLLER_H_ */
