#include "qtshanoirprocess.h"

QtShanoirProcess::QtShanoirProcess()
{

}

int QtShanoirProcess::getId()
{
    return this->id;
}

void QtShanoirProcess::setId(int id)
{
    this->id = id;
}

QString QtShanoirProcess::getName()
{
    return this->name;
}

void QtShanoirProcess::setName(QString name)
{
    this->name = name;
}

QDate QtShanoirProcess::getCreationDate()
{
    return this->creationDate;
}

void QtShanoirProcess::setCreationDate(QDate date)
{
    this->creationDate = date;
}

QtShanoirProcessedDataset& QtShanoirProcess::getProcessedDatasetById(int id)
{

    for (int i=0; i<processedDatasetList.size();i++)
        if(processedDatasetList.value(i).getId()== id)
            return processedDatasetList[i];
}

void QtShanoirProcess::insertProcessedDataset(QtShanoirProcessedDataset processedDataset)
{
    this->processedDatasetList.append(processedDataset);
}

void QtShanoirProcess::displayProcessedList()
{
    qDebug()<<"I'm in displayProcessedList";
    for (int i=0; i<processedDatasetList.size();i++)
      qDebug()<<"Process:"<<processedDatasetList.value(i).getName();
    qDebug()<<"Fin displayProcessedList";
}

QMap<int,QString> QtShanoirProcess::getProcessedDatasetList()
{
    QMap<int,QString> list;
    for (int i=0; i<processedDatasetList.size();i++)
    {
       // if (filter.exactMatch(studyList.value(i).getName()))
           list.insert(processedDatasetList.value(i).getId(),processedDatasetList.value(i).getName());
    }
    return list;
}

