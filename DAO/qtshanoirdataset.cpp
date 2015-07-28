#include "qtshanoirdataset.h"

int QtShanoirDataset::getId()
{
    return this->id;
}

void QtShanoirDataset::setId(int id)
{
    this->id = id;
}

QString QtShanoirDataset::getName()
{
    return this->name;
}

void QtShanoirDataset::setName(QString name)
{
    this->name = name;
}

QDate QtShanoirDataset::getCreationDate()
{
    return this->creationDate;
}

void QtShanoirDataset::setCreationDate(QDate date)
{
    this->creationDate = date;
}

QString QtShanoirDataset::getComment()
{
    return this->comment;
}

void QtShanoirDataset::setComment(QString comment)
{
    this->comment = comment;
}

float QtShanoirDataset::getRepetitionTime()
{
    return this->repetitionTime;
}

void QtShanoirDataset::setRepetitionTime(float occurence)
{
    this->repetitionTime = occurence;
}

float QtShanoirDataset::getFlipAngle()
{
    return this->flipAngle;
}

void QtShanoirDataset::setFlipAngle(float angle)
{
    this->flipAngle = angle;
}

float QtShanoirDataset::getEchoTime()
{
    return this->echoTime;
}

void QtShanoirDataset::setEchoTime(float echo)
{
    this->echoTime = echo;
}

void QtShanoirDataset::insertDatasetProcessing(QtShanoirDatasetProcessing datasetProcessing)
{
    this->datasetProcessingList.append(datasetProcessing);
}

void QtShanoirDataset::displayDatasetProcessingList()
{
    qDebug()<<"I'm in displayDatasetProcessingList";
    for (int i=0; i<datasetProcessingList.size();i++)
      qDebug()<<"DatasetProcessing:"<<datasetProcessingList.value(i).getName();
    qDebug()<<"Fin displayDatasetProcessingList";
}

QMap<int,QString> QtShanoirDataset::getDatasetProcessingList()
{
    QMap<int,QString> list;
    for (int i=0; i<datasetProcessingList.size();i++)
    {
       // if (filter.exactMatch(studyList.value(i).getName()))
           list.insert(datasetProcessingList.value(i).getId(),datasetProcessingList.value(i).getName());
    }
    return list;
}
