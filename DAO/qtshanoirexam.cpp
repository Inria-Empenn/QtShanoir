#include "qtshanoirexam.h"

int QtShanoirExam::getId()
{
    return this->id;
}

void QtShanoirExam::setId(int id)
{
    this->id = id;
}

int QtShanoirExam::getIdSubject()
{
    return this->idSubject;
}

void QtShanoirExam::setIdSubject(int idSubject)
{
    this->idSubject = idSubject;
}

QString QtShanoirExam::getComment()
{
    return this->comment;
}

void QtShanoirExam::setComment(QString comment)
{
    this->comment = comment;
}

QDate QtShanoirExam::getDate()
{
    return this->date;
}

void QtShanoirExam::setDate(QDate date)
{
    this->date = date;
}

QtShanoirDataset& QtShanoirExam::getDatasetById(int id)
{

    for (int i=0; i<datasetList.size();i++)
        if(datasetList.value(i).getId()== id)
            return datasetList[i];
}


void QtShanoirExam::insertDataset(QtShanoirDataset dataset)
{
    this->datasetList.append(dataset);
}

void QtShanoirExam::displayDatasetList()
{
    qDebug()<<"I'm in displayDatasetList";
    for (int i=0; i<datasetList.size();i++)
      qDebug()<<"Dataset:"<<datasetList.value(i).getName();
    qDebug()<<"Fin displayDatasetList";
}

QMap<int,QString> QtShanoirExam::getDatasetList()
{
    QMap<int,QString> list;
    for (int i=0; i<datasetList.size();i++)
    {
       // if (filter.exactMatch(studyList.value(i).getName()))
           list.insert(datasetList.value(i).getId(),datasetList.value(i).getName());
    }
    return list;
}
