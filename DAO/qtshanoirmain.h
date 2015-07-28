#ifndef QTSHANOIRMAIN
#define QTSHANOIRMAIN

#include <QtCore>
#include "QtSoap.h"
#include "qtshanoirsettings.h"
#include "qtshanoirdownload.h"
#include "qtshanoirwebservice.h"
#include "qtshanoiruploadprocesseddatasetattributes.h"

typedef struct ProcessedDatasetAttributes
{
    int studyId;
    QList<int> inputDatasetIdList;
    int refDatasetProcessingId;
    QString datasetClass;
    QString datasetName;
    QString datasetComment;
    int refMrDatasetNatureId;
    int refMrQualityProcedureTypeId;
    int refCalibrationDatasetTypeId;
    int refProcessedDatasetTypeId;
    int refParameterQuantificationDatasetNatureId;
    int refSpectDatasetNatureId;
    int refTemplateDatasetNatureId;
}ProcessedDatasetAttributes;

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
    QString acquireProcess_ProcessedDataset(QString idDataset);

    //for upload
    QString acquireProcessingList();
    QString acquireDatasetTypeList();
    QString acquireMrdatasetNatureList();
    QString acquireMrSpectroscopydatasetNatureList();
    QString acquireMrDatasetQualityProcedureTypeList();
    QString acquireCalibrationDatasetTypeList();
    QString acquireProcessedDatasetTypeList();
    QString acquireTemplateDatasetNatureList();
    QString acquireParameterQuantificationNatureList();
    QString acquireSpectNatureList();

    //Download
    QByteArray downloadDataset(QString datasetId);
    void downloadMetadata(QString datasetId);
    QString getDownloadFilename(QString);

    //Upload
    void uploadProcessedDatasetFile(QtShanoirUploadProcessedDatasetAttributes);

    void findProcessing();
    void getDatasetFilename(QString datasetId);
    void getProcessingListId();
    QString getErrorMessage(QString xmlserial);
    void queryFinished();
    int getCurrentId();
    void setCurrentId(int);

};

#endif //QTSHANOIRMAIN


