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

        static QtShanoir*
        instance();
        void
        init();
        void
        attachTreeWidget(QtShanoirTreeWidget * tree);
        void
        attachProgressWidget(QtShanoirProgressWidget * progress);
        void
        clearTree();
        void
        downloadToDir(QString tmpDir);
        void
        setDownloadMetadata(bool meta);
        void setStudyNameFilter(QString text);
        void setPatientNameFilter(QString text);
        void setDatasetNameFilter(QString text);
        void setDateFilter(QString text);
    
 public slots:
        void
        setDownloadMetadata(int state);
        void
        download();
        void
        find();

    protected:
        // Create the Queries for a specific
        void
        populate();
        // Push the login stack for this ws.
        void
        downloadDataset(QString datasetId);
        void
        downloadMetadata(QString datasetId);
        void
        getDatasetFilename(QString datasetId);
    signals:
        void
        nextMessage();
        void
        startDownload();
        void
        downloadFinished(QString fileName);

    private slots:
        void
        callDownload();
        void
        getError(QString);
        void
        updateSelected(QList<int> );
        void
        setDownloadFilename(QString filename);
        void
        downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
        //        void uploadProgress ( qint64 bytesSent, qint64 bytesTotal );
        void
        findExam(QString);
        void
        findDataset(QString, QString);
        void
        currentId(int);
        void
        queryFinished();

    private:
        static QtShanoir * _instance;
        QtShanoirPrivate * d;
};

#endif /* QTSHANOIRCONTROLLER_H_ */
