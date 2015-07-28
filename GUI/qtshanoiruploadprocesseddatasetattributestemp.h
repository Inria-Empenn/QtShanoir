#ifndef QTSHANOIRUPLOADPROCESSEDDATASETATTRIBUTESTEMP_H
#define QTSHANOIRUPLOADPROCESSEDDATASETATTRIBUTESTEMP_H

#include <QtCore>

class QtShanoirUploadProcessedDatasetAttributesTemp
{

private:
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

public:
    QtShanoirUploadProcessedDatasetAttributesTemp();

    QString getFilename();
    void setFilename(QString);

    int getStudyId();
    void setStudyId(int);

    QList<int> getInputDatasetIdList();
    void setInputDatasetIdList(QList<int>);

    int getRefDatasetProcessingId();
    void setRefDatasetProcessingId(int);

    QString getDatasetClass();
    void setDatasetClass(QString);

    QString getDatasetName();
    void setDatasetName(QString);

    QString getDatasetComment();
    void setDatasetComment(QString);

    int getRefMrDatasetNatureId();
    void setRefMrDatasetNatureId(int);

    int getRefMrQualityProcedureTypeId();
    void setRefMrQualityProcedureTypeId(int);

    int getRefCalibrationDatasetTypeId();
    void setRefCalibrationDatasetTypeId(int);

    int getRefProcessedDatasetTypeId();
    void setRefProcessedDatasetTypeId(int);

    int getRefParameterQuantificationDatasetNatureId();
    void setRefParameterQuantificationDatasetNatureId(int);

    int getRefSpectDatasetNatureId();
    void setRefSpectDatasetNatureId(int);

    int getRefTemplateDatasetNatureId();
    void setRefTemplateDatasetNatureId(int);


};

#endif // QTSHANOIRUPLOADPROCESSEDDATASETATTRIBUTESTEMP_H
