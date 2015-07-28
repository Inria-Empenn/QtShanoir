#ifndef QTSHANOIRTREE_H
#define QTSHANOIRTREE_H

#include "qtshanoirstudy.h"



class  QtShanoirTree
{
private:
    QMap<int,QString> selectedId;
    QMap<int,QString> studyIds;
    QString server;
    QList<QtShanoirStudy> studyList;

public:
	QtShanoirTree();
    QtShanoirTree* buildTree();
    QString getServer();
    void setServer(QString);
    void insert(QtShanoirStudy);
    void insertExam(QtShanoirExam exam,int idStudy, int idSubject);
    void displayAllTree();
    void displayStudyList();
    QMap<int,QString>getStudyList(QString);//QRegExp filter
    QMap<int,QString> getSubjectList(QString study,QString subjectFilter);
    QMap<int,QString> getExamList(int idStudy, int idSubject);
    QMap<int,QString> getDatasetList(int idStudy, int idSubject, int idExam);
    QMap<int,QString> getProcessList(int idStudy, int idSubject, int idExam, int idDataset);
    QMap<int,QString> getProcessedDatasetList(int idStudy, int idSubject, int idExam, int idDataset, int idProcess);
    QtShanoirStudy& getStudyById(int);
    QtShanoirStudy getStudyByName(QString);
    void getIdStudyIdSubject(int*,int*, QString);
    void acquireRefreshExamList(int idStudy,int idSubject);
    void acquireRefreshDatasetList(int idStudy, int idSubject, int idExam);
    void acquireRefreshProcess_processedDatasetList(int idStudy, int idSubject, int idExam, int idDataset);
    void replaceStudy(int idStudy,QtShanoirStudy study);


};

#endif // QTSHNOIRTREE_H
