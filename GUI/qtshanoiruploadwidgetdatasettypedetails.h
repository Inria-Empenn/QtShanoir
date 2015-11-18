#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILS_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILS_H

#include <QtGui>
#include <QWizard>
#include "qtshanoiruploadwidgetshowstepsdatasettypedetails.h"
#include "ui_qtshanoiruploadwidgetdatasettypedetails.h"
#include "qtshanoiruploadprocesseddatasetattributestemp.h"
#include "qtshanoiruploadwidgetdatasettypedetailsmrdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailsmrspectroscopydataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailscalibrationdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailseegmegpetdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailstemplatedataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailsparameterquantificationdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailsspectdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetailsstandarddataset.h"


typedef struct ProcessedDatasetFilesAndAttributes
{
    QString filename;
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
}ProcessedDatasetFilesAndAttributes;

namespace Ui
{
class QtShanoirUploadWidgetDatasetTypeDetails;
}


class QtShanoirUploadWidgetDatasetTypeDetails: public QWizardPage
{
    Q_OBJECT
public:
    QtShanoirUploadWidgetDatasetTypeDetails(QWidget *parent = 0);
    void attachShowStepsWidget(QtShanoirUploadWidgetShowStepsDatasetTypeDetails* showsteps);
    void attachMrDatasetWidget(QtShanoirUploadWidgetDatasetTypeDetailsMrDataset* widget);
    void initConnections();
    void fillComboBox();
    void clearWidget();
    QString reduceFilenameToTwoDir(QString);
    void submitFilesToUpload();
    bool validatePage();

    bool validationMrDataset();
    bool validationMrSpectroscopyDataset();
    bool validationCalibrationDataset();
    bool validationEegMegPetDataset();
    bool validationTemplateDataset();
    bool validationParameterQuantificationDataset();
    bool validationSpectDataset();
    bool validationStandardDataset();

    bool validationMrDatasetWithoutErrorMessage();
    bool validationMrSpectroscopyDatasetWithoutErrorMessage();
    bool validationCalibrationDatasetWithoutErrorMessage();
    bool validationEegMegPetDatasetWithoutErrorMessage();
    bool validationTemplateDatasetWithoutErrorMessage();
    bool validationParameterQuantificationDatasetWithoutErrorMessage();
    bool validationSpectDatasetWithoutErrorMessage();


public slots:
    void updateDatasetTypeSelectedList(QStringList);
    void updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void showWidget(QString);
    void updateMrDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateMrSpectroscopyDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateCalibrationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateParameterQuantificationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateSpectDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateTemplateDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void updateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void clearIntermediateLists();
    void fillUpdateIntermediateLists();
    void updateShowStepsList();

signals:
    void callBuildUpdateSteps(QMap<QString, int>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetails *ui;
    QStringList datasetTypeSelectedList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> mrDatasetFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> mrSpectroscopyDatasetFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> calibrationFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> eegFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> megFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> petFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> templateFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> parameterQuantificationFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> spectFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> meshFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> registrationFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> statisticalFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> ctFilesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> segmentationFilesToUpload;
    QList<int> mrDatasetFilesToUploadPositions;
    QList<int> mrSpectroscopyDatasetFilesToUploadPositions;
    QList<int> calibrationFilesToUploadPositions;
    QList<int> eegFilesToUploadPositions;
    QList<int> megFilesToUploadPositions;
    QList<int> petFilesToUploadPositions;
    QList<int> templateFilesToUploadPositions;
    QList<int> parameterQuantificationFilesToUploadPositions;
    QList<int> spectFilesToUploadPositions;
    QList<int> meshFilesToUploadPositions;
    QList<int> registrationFilesToUploadPositions;
    QList<int> statisticalFilesToUploadPositions;
    QList<int> ctFilesToUploadPositions;
    QList<int> segmentationFilesToUploadPositions;
    QMap<QString,int> showStepsList;

    QtShanoirUploadWidgetShowStepsDatasetTypeDetails* showsteps;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILS_H


