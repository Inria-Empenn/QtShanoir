#ifndef QTSHANOIRSUBJECT	
#define QTSHANOIRSUBJECT

#include <QtCore>
#include "qtshanoirexam.h"


class QtShanoirSubject
{
private:
    int id;
    QString name;
    QDate birthDate;
    QChar sexe;
    int idStudy;
    QList<QtShanoirExam> examList;


public:
    //QtShanoirSubject(const QtShanoirSubject&);
    //QtShanoirSubject();
    int getId();
    void setId(int);
    int getIdStudy();
    void setIdStudy(int);
    QString getName();
    void setName(QString);
    QDate getBirthDate();
    void setBirthDate(QDate);
    QChar getSexe();
    void setSexe(QChar);
    QtShanoirExam& getExamById(int);
    void insertExam(QtShanoirExam);
    void displayExamList();
    QMap<int,QString> getExamList();
    void acquireRefreshExamList();
    int sizeExamList();
};

#endif // QTSHANOIRSUBJECT

