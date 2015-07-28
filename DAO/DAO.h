#ifndef DAO
#define DAO

#include "qtshanoirtree.h"
#include "parsetree.h"
#include "qtshanoirmain.h"
#include "parsetree.h"

#ifdef WIN32
#   ifdef DAO
#       define DAO_EXPORT __declspec(dllexport)
#   else
#       define DAO_EXPORT __declspec(dllimport)
#   endif 
#else
#  define DAO_EXPORT 
#endif

extern "C"
{
typedef DAO_EXPORT struct Settings
{
    QString login;
    QString password;
    QString host;
    int port;
    QString truststore;
}Settings;

typedef DAO_EXPORT struct Study
{
    QString name;
}Study;

typedef DAO_EXPORT struct Subject
{
    QString name;
    QDate birthDate;
    QChar sexe;
}Subject;

typedef DAO_EXPORT struct Exam
{
    QString comment;
    QDate date;
}Exam;

typedef DAO_EXPORT struct Dataset
{
    QString name;
    QDate creationDate;
    QString comment;
    float repetitionTime;
    float flipAngle;
    float echoTime;
}Dataset;


    DAO_EXPORT void configureSettings(QString);
    DAO_EXPORT struct Settings* loadSettings();
    DAO_EXPORT void updateSettings(struct Settings*, QString);
    DAO_EXPORT QString authentification();
    DAO_EXPORT QMap<int,QString>  findStudyList(QString studyFilter);//QRegExp
    DAO_EXPORT QMap<int,QString>  findSubjectList(QString study,QString subjectFilter);//filter
    DAO_EXPORT QMap<int,QString>  findExamList(int,int);//filter
    DAO_EXPORT QMap<int,QString>  findDatasetList(int,int,int);
    DAO_EXPORT QMap<int,QString>  findDatasetProcessingList(int,int,int,int);
    DAO_EXPORT struct Study* getStudyDetails(QString);
    DAO_EXPORT struct Subject* getSubjectDetails(int,int);
    DAO_EXPORT struct Exam* getExamDetails(int,int,int);
    DAO_EXPORT struct Dataset* getDatasetDetails(int,int,int,int);
    DAO_EXPORT void downloadFile(QString,QString);
//    DAO_EXPORT QMap<int,QString> updateStudy();
//    DAO_EXPORT QMap<int,QString> updateSubject(int);
//    DAO_EXPORT QMap<int,QString> updateExam(int,int);
//    DAO_EXPORT QMap<int,QString> updateDataset(int,int,int);

}
//extern "C" DAO_EXPORT QtShanoirMain*  loadStudy(struct Subject* subject);

//QtShanoirTree* tree;

QtShanoirMain* servicePopulate ;
ParseTree* parse;

#endif 

