#include "qtshanoirupload.h"



QtShanoirUpload::QtShanoirUpload()
{

}

QMap<int,QString> QtShanoirUpload::getProcessingList()
{
    return this->processingList;
}

void QtShanoirUpload::setProcessingList(QMap<int,QString> list)
{
    this->processingList = list;
}

QStringList QtShanoirUpload::getDatasetTypeList()
{
    return this->datasetTypeList;
}

void QtShanoirUpload::setDatasetTypeList(QStringList list)
{
    this->datasetTypeList = list;
}

QMap<int,QString> QtShanoirUpload::getMrdatasetNatureList()
{
    return this->mrdatasetNatureList;
}

void QtShanoirUpload::setMrdatasetNatureList(QMap<int,QString> list)
{
    this->mrdatasetNatureList = list;
}

QMap<int,QString> QtShanoirUpload::getMrSpectroscopydatasetNatureList()
{
    return this->mrSpectroscopydatasetNatureList;
}

void QtShanoirUpload::setMrSpectroscopydatasetNatureList(QMap<int,QString> list)
{
    this->mrSpectroscopydatasetNatureList = list;
}

QMap<int,QString> QtShanoirUpload::getMrDatasetQualityProcedureTypeList()
{
    return this->mrDatasetQualityProcedureTypeList;
}

void QtShanoirUpload::setMrDatasetQualityProcedureTypeList(QMap<int,QString> list)
{
    this->mrDatasetQualityProcedureTypeList = list;
}

QMap<int,QString> QtShanoirUpload::getCalibrationDatasetTypeList()
{
    return this->calibrationDatasetTypeList;
}

void QtShanoirUpload::setCalibrationDatasetTypeList(QMap<int,QString> list)
{
    this->calibrationDatasetTypeList = list;
}

QMap<int,QString> QtShanoirUpload::getProcessedDatasetTypeList()
{
    return this->processedDatasetTypeList;
}

void QtShanoirUpload::setProcessedDatasetTypeList(QMap<int,QString> list)
{
    this->processedDatasetTypeList = list;
}

QMap<int,QString> QtShanoirUpload::getTemplateDatasetNatureList()
{
    return this->templateDatasetNatureList;
}

void QtShanoirUpload::setTemplateDatasetNatureList(QMap<int,QString> list)
{
    this->templateDatasetNatureList = list;
}

QMap<int,QString> QtShanoirUpload::getParameterQuantificationNatureList()
{
    return this->parameterQuantificationNatureList;
}

void QtShanoirUpload::setParameterQuantificationNatureList(QMap<int,QString> list)
{
    this->parameterQuantificationNatureList = list;
}

QMap<int,QString> QtShanoirUpload::getSpectNatureList()
{
    return this->spectNatureList;
}

void QtShanoirUpload::setSpectNatureList(QMap<int,QString> list)
{
    this->spectNatureList = list;
}

void QtShanoirUpload::uploadProcessedDatasetFiles(QList<QtShanoirUploadProcessedDatasetAttributes> filesList)
{
    QtShanoirMain* serviceUpload = new QtShanoirMain();
    for(int i=0; i<filesList.size();i++)
    {
        serviceUpload->uploadProcessedDatasetFile(filesList[i]);
    }
}
