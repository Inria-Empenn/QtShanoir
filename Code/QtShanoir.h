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

#ifndef QTSHANOIRCONTROLLER_H_
#define QTSHANOIRCONTROLLER_H_

#include <QtGui>
#include <QtSoap.h>

class QNetworkRequest;
class QtShanoirTreeWidget;
class QtShanoirProgressWidget;
class QtShanoirUploadWidget;
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
        attachUploadWidget(QtShanoirUploadWidget * upload);
        void
        clearTree();
        void
        downloadToDir(QString tmpDir);
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
        void
        upload();

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
        void
        getProcessingListId();

        QString getErrorMessage(QString xmlserial);

    signals:
        void
        nextMessage();
        void
        startDownload();
        void
        startUpload();
        void
        downloadFinished(QString fileName, QString xmlFileName);
        void
        processingMap(QMap<int, QString> map);
        void progressShown();
        void progressHidden();

        void queryFailed(QString reason);

    private slots:
        void
        callDownload();
        void
        callUpload();
        void
        updateSelected(QMap<int,QString> );
        void
        receiveUploadData(QMultiMap<QString, QString> mmap);
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
        findProcessing(QString datasetId);
    
        void
        currentId(int);
        void
        queryFinished();

    private:
        static QtShanoir * _instance;
        QtShanoirPrivate * d;
};

#endif /* QTSHANOIRCONTROLLER_H_ */
