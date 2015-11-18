#include "qtshanoirprocesseddataset.h"

int QtShanoirProcessedDataset::getId()
{
    return this->id;
}

void QtShanoirProcessedDataset::setId(int id)
{
    this->id = id;
}

QString QtShanoirProcessedDataset::getName()
{
    return this->name;
}

void QtShanoirProcessedDataset::setName(QString name)
{
    this->name = name;
}

QString QtShanoirProcessedDataset::getComment()
{
    return this->comment;
}

void QtShanoirProcessedDataset::setComment(QString comment)
{
    this->comment = comment;
}

QDate QtShanoirProcessedDataset::getProcessedDatasetCreationDate()
{
    return this->processedDatasetCreationDate;
}

void QtShanoirProcessedDataset::setProcessedDatasetCreationDate(QDate date)
{
    this->processedDatasetCreationDate = date;
}
