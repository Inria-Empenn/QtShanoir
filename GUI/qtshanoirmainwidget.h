#ifndef QTSHANOIRMAINWIDGET_H
#define QTSHANOIRMAINWIDGET_H

#include "qtshanoirtreewidget.h"
#include "qtshanoirprogresswidget.h"
#include "qtshanoiruploadwidget.h"
#include "qtshanoirmain.h"

class QtShanoirMainWidget : public QObject
{
    Q_OBJECT
private:
    QtShanoirTreeWidget * tree;
    QtShanoirProgressWidget * progress;
    QtShanoirUploadWidget * upload;
    QtShanoirMain shanoirmain;

public:
	QtShanoirMainWidget(  QObject * parent);
    void initConnections();
    void attachTreeWidget(QtShanoirTreeWidget * tree);
    void attachProgressWidget(QtShanoirProgressWidget * progress);
    void attachUploadWidget(QtShanoirUploadWidget * upload);
    void clearTree();

signals:
    void startDownload();
    void startUpload();
    void downloadFinished(QString fileName, QString xmlFileName);
    void processingMap(QMap<int, QString> map);
    void queryFailed(QString reason);
	void progressHidden();

public slots:
    void download();
    void callDownload();
    void updateSelected(QMap<int,QString> );
    void receiveUploadData(QMultiMap<QString, QString> mmap);
    void find();
    void findExam(QString);
    void findDataset(QString, QString);
    void findProcessing(QString datasetId);
    void currentId(int);
    void setDownloadMetadata(int state);
};

#endif // QTSHANOIRMAINWIDGET_H
