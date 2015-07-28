#include "qtshanoirstudy.h"

int QtShanoirStudy::getId()
{
    return this->id;
}

void QtShanoirStudy::setId(int id)
{
    this->id = id;
}

QString QtShanoirStudy::getName()
{
    return this->name;
}

void QtShanoirStudy::setName(QString name)
{
    this->name = name;
}

void QtShanoirStudy::insertSubject(QtShanoirSubject subject)
{
    qDebug()<<"I'm in insertSubject";
    qDebug()<<"size subjectList"<<subjectList.size();
    this->subjectList.append(subject);
    qDebug()<<"fin insertSubject";
}

void QtShanoirStudy::insertExam(QtShanoirExam exam,int idSubject)
{
    getSubjectById(idSubject).insertExam(exam);
}

void QtShanoirStudy::displaySubjectList()
{
    qDebug()<<"I'm in displaySubjectList";
    for (int i=0; i<subjectList.size();i++)
       qDebug()<<"Subject:"<<subjectList.value(i).getName();
    qDebug()<<"Fin displaySubjectList";
}

void QtShanoirStudy::displaySubjectList_exam()
{
    qDebug()<<"I'm in displaySubjectList_exam";
    for (int i=0; i<subjectList.size();i++)
    {

        qDebug()<<"Subject:"<<subjectList.value(i).getName();
        subjectList.value(i).displayExamList();
    }

    qDebug()<<"Fin displaySubjectList";
}

QMap<int,QString> QtShanoirStudy::getSubjectList(QString subjectFilter)
{
    QMap<int,QString> list;

    for (int i=0; i<subjectList.size();i++)
    {
        qDebug()<<subjectList.value(i).getName();
        if ((subjectFilter=="")||(subjectList.value(i).getName().contains(subjectFilter)))
           list.insert(subjectList.value(i).getId(),subjectList.value(i).getName());
    }

    return list;
}


QtShanoirSubject& QtShanoirStudy::getSubjectById(int id)
{

    for (int i=0; i<subjectList.size();i++)
        if(subjectList.value(i).getId()== id)
            return subjectList[i];
    //return hy;
}

QtShanoirSubject QtShanoirStudy::getSubjectByName(QString name)
{
    for (int i=0; i<subjectList.size();i++)
        if(subjectList.value(i).getName()== name)
            return subjectList.value(i);
}

void QtShanoirStudy::acquireRefreshExamListAllSubject()
{
    qDebug()<<"size"<<subjectList.size();
    for (int i=0; i<subjectList.size();i++)
        subjectList.value(i).acquireRefreshExamList();
}
