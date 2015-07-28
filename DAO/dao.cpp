#include "dao.h"

DAO_EXPORT void configureSettings(QString filename)
{
    GlobalData::settings.loadSettings(filename);

}

DAO_EXPORT struct Settings* loadSettings()
{
    struct Settings* settings = new struct Settings ;
    settings->login = GlobalData::settings.getLogin();
    settings->password = GlobalData::settings.getPassword();
    settings->host = GlobalData::settings.getHost();
    settings->port = GlobalData::settings.getPort();
    settings->truststore = GlobalData::settings.getTrustore();
    return settings;
}

DAO_EXPORT void updateSettings(struct Settings* settings, QString iniFile)
{
    GlobalData::settings.setLogin(settings->login);
    GlobalData::settings.setPassword(settings->password);
    GlobalData::settings.setHost(settings->host);
    GlobalData::settings.setPort(settings->port);
    GlobalData::settings.update(iniFile);
}

/**
 * \fn QString authentification()
 * \brief This function connects to the web service to ping and test if the server settings entered are correct or not.
 * \return This message returns a QString. If its value is NULL, the configuration server are valid, if not a detailed error message is returned.
 */
DAO_EXPORT QString authentification()
{
    QtShanoirMain* serviceAuthentification = new QtShanoirMain();
    return serviceAuthentification->authentification();
}

QtShanoirTree* tree = new QtShanoirTree();
DAO_EXPORT QMap<int,QString>  findStudyList(QString studyFilter )//QRegExp studyfilter
{
    if (tree->getStudyList(studyFilter).isEmpty())
    {
        QtShanoirMain* servicePopulate = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer;

        //Build Study_Subject
        xmlSerializer = servicePopulate->acquireStudy_Subject();
        parse->parseStudy_Subject(xmlSerializer,tree);

    }
    return tree->getStudyList(studyFilter);
}

DAO_EXPORT QMap<int,QString> findSubjectList(QString study, QString subjectFilter)
{
    return tree->getSubjectList(study,subjectFilter);
}

DAO_EXPORT QMap<int,QString> findExamList(int idStudy, int idSubject)
{
    qDebug() << "findExamList";
    if (tree->getExamList(idStudy,idSubject).isEmpty())
    {
         tree->acquireRefreshExamList(idStudy,idSubject);
    }
    return tree->getExamList(idStudy, idSubject);
}


DAO_EXPORT QMap<int,QString> findDatasetList(int idStudy,int idSubject,int idExam)
{
    qDebug() << "findDatasetList";
    if (tree->getDatasetList(idStudy,idSubject,idExam).isEmpty())
    {
        tree->acquireRefreshDatasetList(idStudy, idSubject, idExam);
    }
    return tree->getDatasetList(idStudy,idSubject,idExam);
}

DAO_EXPORT QMap<int,QString>  findDatasetProcessingList(int idStudy,int idSubject,int idExam, int idDataset)
{
    QMap<int,QString> list;
//    qDebug() << "findDatasetProcessingList";
//    if (tree->getDatasetProcessingList(idStudy,idSubject,idExam,idDataset).isEmpty())
//    {
//        tree->acquireRefreshDatasetProcessingList(idStudy, idSubject, idExam,idDataset);
//    }
//    return tree->getDatasetProcessingList(idStudy,idSubject,idExam,idDataset);
    return list;
}

DAO_EXPORT struct Study* getStudyDetails(QString study)
{
    struct Study* str_study = new struct Study ;
    QtShanoirStudy cl_study = tree->getStudyByName(study);
    str_study->name = cl_study.getName();
    return str_study;
}

DAO_EXPORT struct Subject* getSubjectDetails(int idStudy,int idSubject)
{
    struct Subject* str_subject = new struct Subject;
    QtShanoirSubject cl_subject = tree->getStudyById(idStudy).getSubjectById(idSubject);
    str_subject->name = cl_subject.getName();
    str_subject->birthDate = cl_subject.getBirthDate();
    str_subject->sexe = cl_subject.getSexe();
    return str_subject;
}

DAO_EXPORT struct Exam* getExamDetails(int idStudy, int idSubject, int idExam)
{
    struct Exam* str_exam = new struct Exam;
    QtShanoirExam cl_exam = tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam);
    str_exam->comment = cl_exam.getComment();
    str_exam->date = cl_exam.getDate();
    return str_exam;
}

DAO_EXPORT struct Dataset* getDatasetDetails(int idStudy, int idSubject, int idExam, int idDataset)
{
    struct Dataset* str_dataset = new struct Dataset;
    QtShanoirDataset cl_dataset = tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam).getDatasetById(idDataset);
    str_dataset->name = cl_dataset.getName();
    str_dataset->creationDate = cl_dataset.getCreationDate();
    str_dataset->comment = cl_dataset.getComment();
    str_dataset->repetitionTime = cl_dataset.getRepetitionTime();
    str_dataset->flipAngle = cl_dataset.getFlipAngle();
    str_dataset->echoTime = cl_dataset.getEchoTime();
    return str_dataset;
}

DAO_EXPORT void downloadFile(QString datasetId,QString directory)
{
    qDebug()<<"downloadFile";
    qDebug()<<"datasetId"<<datasetId;
    qDebug()<<"directory"<<directory;
    QtShanoirDownload* download = new QtShanoirDownload();
    QtShanoirMain* serviceDownload = new QtShanoirMain();
    download->getFileName(serviceDownload->getDownloadFilename(datasetId));
    QByteArray bin = serviceDownload->downloadDataset(datasetId);
    download->downloadDataset(bin,datasetId,directory);
}

//DAO_EXPORT QMap<int,QString> updateStudy()
//{

//}

//DAO_EXPORT QMap<int,QString> updateSubject(int)
//{

//}

//DAO_EXPORT QMap<int,QString> updateExam(int,int)
//{

//}

//DAO_EXPORT QMap<int,QString> updateDataset(int,int,int)
//{

//}
