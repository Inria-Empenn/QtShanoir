#include "qtshanoirupload.h"

QtShanoirUpload::QtShanoirUpload()
{
    processingId = 0;
    studyId = 0;
    datasetName = "";
    datasetPath = "";
    datasetComment = "";
    processingComment = "";
    resultDatasetType = "";
}

int QtShanoirUpload::getProcessingId()
{
    return this->processingId;
}

void QtShanoirUpload::setProcessingId(int id)
{
    this->processingId = id;
}

int QtShanoirUpload::getStudyId()
{
    return this->studyId;
}

void QtShanoirUpload::setStudyId(int id)
{
    this->studyId = id;
}

QString QtShanoirUpload::getDatasetName()
{
    return this->datasetName;
}

void QtShanoirUpload::setDatasetName(QString name)
{
    this->datasetName = name;
}

QString QtShanoirUpload::getDatasetPath()
{
    return this->datasetPath;
}

void QtShanoirUpload::setDatasetPath (QString path)
{
    this->datasetPath = path;
}

QString QtShanoirUpload::getResultDatasetType()
{
    return this->resultDatasetType;
}

void QtShanoirUpload::setResultDatasetType(QString result)
{
    this->resultDatasetType = result;
}

QString QtShanoirUpload::getDatasetComment()
{
    return this->datasetComment;
}

void QtShanoirUpload::setDatasetComment(QString comment)
{
    this->datasetComment = comment;
}

QString QtShanoirUpload::getProcessingComment()
{
    return this->processingComment;
}

void QtShanoirUpload::setProcessingComment(QString comment)
{
    this->processingComment = comment;
}
