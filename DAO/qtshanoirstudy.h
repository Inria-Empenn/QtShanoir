#ifndef QTSHANOIRSTUDY
#define QTSHANOIRSTUDY

#include <QtCore>
#include "qtshanoirsubject.h"
#include"qtshanoirexam.h"



class QtShanoirStudy
{
private:
    int id;
    QString name;
    QList<QtShanoirSubject> subjectList;

public:
    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    void insertSubject(QtShanoirSubject);
    void insertExam(QtShanoirExam,int);
    void displaySubjectList();
    void displaySubjectList_exam();
    QMap<int,QString> getSubjectList(QString);
    QtShanoirSubject& getSubjectById(int);
    QtShanoirSubject getSubjectByName(QString);
    void acquireRefreshExamListAllSubject();

};

#endif // QTSHANOIRSTUDY

