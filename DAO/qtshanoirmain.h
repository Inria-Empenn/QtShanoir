#ifndef QTSHANOIRMAIN
#define QTSHANOIRMAIN

#include <QtCore>
#include "QtSoap.h"
#include "qtshanoirsettings.h"
#include "qtshanoirdownload.h"
#include "qtshanoirwebservice.h"
#include "parsetree.h"


namespace GlobalData
{

     extern  QtShanoirSettings settings;
}

class QtShanoirMain
{
private:
    
    int currentId;
    QtShanoirDownload download;
    QList<QString> selectedIds;
    QMultiMap<QString,QString> dataToUpload;
public:
    QString authentification(); //  à convertir à une session
    QtShanoirMain();
    QList<QString> getSelectedIds();
    void setSelectedIds(QList<QString>);
    void clearSelectedIds();
    QString acquireStudy_Subject();
    QString acquireExam(QString);
    QString acquireDataset(QString,QString);
    QString acquireDatasetProcessing(QString idDataset);

    //Download
    QByteArray downloadDataset(QString datasetId);
    void downloadMetadata(QString datasetId);
    QString getDownloadFilename(QString);

    void findProcessing();
    void upload();
    void getDatasetFilename(QString datasetId);
    void getProcessingListId();
    QString getErrorMessage(QString xmlserial);
    void queryFinished();
    int getCurrentId();
    void setCurrentId(int);

};

#endif //QTSHANOIRMAIN


