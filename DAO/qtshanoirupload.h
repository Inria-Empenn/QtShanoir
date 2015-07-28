#ifndef QTSHANOIRUPLOAD_H
#define QTSHANOIRUPLOAD_H

#include <QMap>
#include <QStringList>
#include "qtshanoiruploadprocesseddatasetattributes.h"
#include "qtshanoirmain.h"

class QtShanoirUpload
{
private:
    QMap<int,QString> processingList;
    QStringList datasetTypeList;
    QMap<int,QString> mrdatasetNatureList;
    QMap<int,QString> mrSpectroscopydatasetNatureList;
    QMap<int,QString> mrDatasetQualityProcedureTypeList;
    QMap<int,QString> calibrationDatasetTypeList;
    QMap<int,QString> processedDatasetTypeList;
    QMap<int,QString> templateDatasetNatureList;
    QMap<int,QString> parameterQuantificationNatureList;
    QMap<int,QString> spectNatureList;

public:
    QtShanoirUpload();
    QMap<int,QString> getProcessingList();
    void setProcessingList(QMap<int,QString>);

    QStringList getDatasetTypeList();
    void setDatasetTypeList(QStringList);

    QMap<int,QString> getMrdatasetNatureList();
    void setMrdatasetNatureList(QMap<int,QString>);

    QMap<int,QString> getMrSpectroscopydatasetNatureList();
    void setMrSpectroscopydatasetNatureList(QMap<int,QString>);

    QMap<int,QString> getMrDatasetQualityProcedureTypeList();
    void setMrDatasetQualityProcedureTypeList(QMap<int,QString>);

    QMap<int,QString> getCalibrationDatasetTypeList();
    void setCalibrationDatasetTypeList(QMap<int,QString>);

    QMap<int,QString> getProcessedDatasetTypeList();
    void setProcessedDatasetTypeList(QMap<int,QString>);

    QMap<int,QString> getTemplateDatasetNatureList();
    void setTemplateDatasetNatureList(QMap<int,QString>);

    QMap<int,QString> getParameterQuantificationNatureList();
    void setParameterQuantificationNatureList(QMap<int,QString>);

    QMap<int,QString> getSpectNatureList();
    void setSpectNatureList(QMap<int,QString>);

    void uploadProcessedDatasetFiles(QList<QtShanoirUploadProcessedDatasetAttributes>);
};

#endif // QTSHANOIRUPLOAD_H


