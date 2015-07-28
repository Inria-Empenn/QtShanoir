#ifndef DAO
#define DAO

#include "qtshanoirtree.h"
#include "qtshanoirupload.h"
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

typedef struct Process
{
    QString name;
    QDate creationDate;
}Process;

typedef DAO_EXPORT struct ProcessedDataset
{
    QString name;
    QString comment;
    QDate processedDatasetCreationDate;
}ProcessedDataset;

typedef DAO_EXPORT struct ProcessedDatasetFilesAndAttributes
{
    QString filename;
    int studyId;
    QList<int> inputDatasetIdList;
    int refDatasetProcessingId;
    QString datasetClass;
    QString datasetName;
    QString datasetComment;
    int refMrDatasetNatureId;
    int refMrQualityProcedureTypeId;
    int refCalibrationDatasetTypeId;
    int refProcessedDatasetTypeId;
    int refParameterQuantificationDatasetNatureId;
    int refSpectDatasetNatureId;
    int refTemplateDatasetNatureId;
}ProcessedDatasetFilesAndAttributes;

    DAO_EXPORT void configureSettings(QString);
    DAO_EXPORT struct Settings* loadSettings();
    DAO_EXPORT void updateSettings(struct Settings*, QString);
    DAO_EXPORT QString authentification();
    DAO_EXPORT QMap<int,QString>  findStudyList(QString studyFilter);//QRegExp
    DAO_EXPORT QMap<int,QString>  findSubjectList(QString study,QString subjectFilter);//filter
    DAO_EXPORT QMap<int,QString>  findExamList(int,int);//filter
    DAO_EXPORT QMap<int,QString>  findDatasetList(int,int,int);
    DAO_EXPORT QMap<int,QString>  findProcessList(int,int,int,int);
    DAO_EXPORT QMap<int,QString>  findProcessedDatasetList(int,int,int,int,int);
    DAO_EXPORT struct Study* getStudyDetails(QString);
    DAO_EXPORT struct Subject* getSubjectDetails(int,int);
    DAO_EXPORT struct Exam* getExamDetails(int,int,int);
    DAO_EXPORT struct Dataset* getDatasetDetails(int,int,int,int);
    DAO_EXPORT struct Process* getProcessDetails(int,int,int,int,int);
    DAO_EXPORT struct ProcessedDataset* getProcessedDatasetDetails(int,int,int,int,int,int);

    DAO_EXPORT void downloadFile(QString,QString);

    DAO_EXPORT QMap<int,QString> getProcessingList();
    DAO_EXPORT QStringList getDatasetTypeList();
    DAO_EXPORT QMap<int,QString> getMrdatasetNatureList();
    DAO_EXPORT QMap<int,QString> getMrSpectroscopydatasetNatureList();
    DAO_EXPORT QMap<int,QString> getMrDatasetQualityProcedureTypeList();
    DAO_EXPORT QMap<int,QString> getCalibrationDatasetTypeList();
    DAO_EXPORT QMap<int,QString> getProcessedDatasetTypeList();
    DAO_EXPORT QMap<int,QString> getTemplateDatasetNatureList();
    DAO_EXPORT QMap<int,QString> getParameterQuantificationNatureList();
    DAO_EXPORT QMap<int,QString> getSpectNatureList();

    DAO_EXPORT void uploadProcessedDatasetFiles(QList<struct ProcessedDatasetFilesAndAttributes*>);

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

