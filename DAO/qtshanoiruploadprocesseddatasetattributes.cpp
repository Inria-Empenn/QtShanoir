#include "qtshanoiruploadprocesseddatasetattributes.h"

QtShanoirUploadProcessedDatasetAttributes::QtShanoirUploadProcessedDatasetAttributes()
{

}

QString QtShanoirUploadProcessedDatasetAttributes::getFilename()
{
    return this->filename;
}

void QtShanoirUploadProcessedDatasetAttributes::setFilename(QString name)
{
    this->filename = name;
}

int QtShanoirUploadProcessedDatasetAttributes::getStudyId()
{
    return this->studyId;
}

void QtShanoirUploadProcessedDatasetAttributes::setStudyId(int id)
{
    this->studyId = id;
}

QList<int> QtShanoirUploadProcessedDatasetAttributes::getInputDatasetIdList()
{
    return this->inputDatasetIdList;
}

void QtShanoirUploadProcessedDatasetAttributes::setInputDatasetIdList(QList<int> list)
{
    this->inputDatasetIdList = list;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefDatasetProcessingId()
{
    return this->refDatasetProcessingId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefDatasetProcessingId(int id)
{
    this->refDatasetProcessingId = id;
}

QString QtShanoirUploadProcessedDatasetAttributes::getDatasetClass()
{
    return this->datasetClass;
}

void QtShanoirUploadProcessedDatasetAttributes::setDatasetClass(QString datasetType)
{
    this->datasetClass = datasetType;
}

QString QtShanoirUploadProcessedDatasetAttributes::getDatasetName()
{
    return this->datasetName;
}
void QtShanoirUploadProcessedDatasetAttributes::setDatasetName(QString name)
{
    this->datasetName = name;
}

QString QtShanoirUploadProcessedDatasetAttributes::getDatasetComment()
{
    return this->datasetComment;
}

void QtShanoirUploadProcessedDatasetAttributes::setDatasetComment(QString comment)
{
    this->datasetComment = comment;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefMrDatasetNatureId()
{
    return this->refMrDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefMrDatasetNatureId(int id)
{
    this->refMrDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefMrQualityProcedureTypeId()
{
    return this->refMrQualityProcedureTypeId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefMrQualityProcedureTypeId(int id)
{
    this->refMrQualityProcedureTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefCalibrationDatasetTypeId()
{
    return this->refCalibrationDatasetTypeId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefCalibrationDatasetTypeId(int id)
{
    this->refCalibrationDatasetTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefProcessedDatasetTypeId()
{
    return this->refProcessedDatasetTypeId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefProcessedDatasetTypeId(int id)
{
    this->refProcessedDatasetTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefParameterQuantificationDatasetNatureId()
{
    return this->refParameterQuantificationDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefParameterQuantificationDatasetNatureId(int id)
{
    this->refParameterQuantificationDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefSpectDatasetNatureId()
{
    return this->refSpectDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefSpectDatasetNatureId(int id)
{
    this->refSpectDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributes::getRefTemplateDatasetNatureId()
{
    return this->refTemplateDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributes::setRefTemplateDatasetNatureId(int id)
{
    this->refTemplateDatasetNatureId = id;
}
