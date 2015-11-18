#include "qtshanoiruploadprocesseddatasetattributestemp.h"

QtShanoirUploadProcessedDatasetAttributesTemp::QtShanoirUploadProcessedDatasetAttributesTemp()
{
    studyId = 0;
    refDatasetProcessingId = 0;
    refMrDatasetNatureId = 0;
    refMrQualityProcedureTypeId = 0;
    refCalibrationDatasetTypeId = 0;
    refProcessedDatasetTypeId = 0;
    refParameterQuantificationDatasetNatureId = 0;
    refSpectDatasetNatureId = 0;
    refTemplateDatasetNatureId = 0;

}

QString QtShanoirUploadProcessedDatasetAttributesTemp::getFilename()
{
    return this->filename;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setFilename(QString name)
{
    this->filename = name;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getStudyId()
{
    return this->studyId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setStudyId(int id)
{
    this->studyId = id;
}

QList<int> QtShanoirUploadProcessedDatasetAttributesTemp::getInputDatasetIdList()
{
    return this->inputDatasetIdList;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setInputDatasetIdList(QList<int> list)
{
    this->inputDatasetIdList = list;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefDatasetProcessingId()
{
    return this->refDatasetProcessingId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefDatasetProcessingId(int id)
{
    this->refDatasetProcessingId = id;
}

QString QtShanoirUploadProcessedDatasetAttributesTemp::getDatasetClass()
{
    return this->datasetClass;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setDatasetClass(QString datasetType)
{
    this->datasetClass = datasetType;
}

QString QtShanoirUploadProcessedDatasetAttributesTemp::getDatasetName()
{
    return this->datasetName;
}
void QtShanoirUploadProcessedDatasetAttributesTemp::setDatasetName(QString name)
{
    this->datasetName = name;
}

QString QtShanoirUploadProcessedDatasetAttributesTemp::getDatasetComment()
{
    return this->datasetComment;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setDatasetComment(QString comment)
{
    this->datasetComment = comment;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefMrDatasetNatureId()
{
    return this->refMrDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefMrDatasetNatureId(int id)
{
    this->refMrDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefMrQualityProcedureTypeId()
{
    return this->refMrQualityProcedureTypeId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefMrQualityProcedureTypeId(int id)
{
    this->refMrQualityProcedureTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefCalibrationDatasetTypeId()
{
    return this->refCalibrationDatasetTypeId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefCalibrationDatasetTypeId(int id)
{
    this->refCalibrationDatasetTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefProcessedDatasetTypeId()
{
    return this->refProcessedDatasetTypeId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefProcessedDatasetTypeId(int id)
{
    this->refProcessedDatasetTypeId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefParameterQuantificationDatasetNatureId()
{
    return this->refParameterQuantificationDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefParameterQuantificationDatasetNatureId(int id)
{
    this->refParameterQuantificationDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefSpectDatasetNatureId()
{
    return this->refSpectDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefSpectDatasetNatureId(int id)
{
    this->refSpectDatasetNatureId = id;
}

int QtShanoirUploadProcessedDatasetAttributesTemp::getRefTemplateDatasetNatureId()
{
    return this->refTemplateDatasetNatureId;
}

void QtShanoirUploadProcessedDatasetAttributesTemp::setRefTemplateDatasetNatureId(int id)
{
    this->refTemplateDatasetNatureId = id;
}
