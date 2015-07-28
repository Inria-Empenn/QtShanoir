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

DAO_EXPORT QMap<int,QString>  findProcessList(int idStudy,int idSubject,int idExam, int idDataset)
{
    qDebug() << "findProcessList";
    if (tree->getProcessList(idStudy,idSubject,idExam,idDataset).isEmpty())
    {
        tree->acquireRefreshProcess_processedDatasetList(idStudy, idSubject, idExam, idDataset);
    }
    return tree->getProcessList(idStudy,idSubject,idExam,idDataset);
}

DAO_EXPORT QMap<int,QString>  findProcessedDatasetList(int idStudy,int idSubject,int idExam, int idDataset,int idProcess)
{
    qDebug() << "findProcessedDatasetList";
    if (tree->getProcessedDatasetList(idStudy,idSubject,idExam,idDataset,idProcess).isEmpty())
    {
        tree->acquireRefreshProcess_processedDatasetList(idStudy, idSubject, idExam, idDataset);
    }
    return tree->getProcessedDatasetList(idStudy,idSubject,idExam,idDataset,idProcess);
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

DAO_EXPORT struct Process* getProcessDetails(int idStudy, int idSubject, int idExam, int idDataset, int idProcess)
{
    struct Process* str_process = new struct Process;
    QtShanoirProcess cl_process = tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam).getDatasetById(idDataset).getProcessById(idProcess);
    str_process->name = cl_process.getName();
    str_process->creationDate = cl_process.getCreationDate();
    return str_process;
}

DAO_EXPORT struct ProcessedDataset* getProcessedDatasetDetails(int idStudy, int idSubject, int idExam, int idDataset, int idProcess, int idProcessedDataset)
{
    struct ProcessedDataset* str_processedDataset = new struct ProcessedDataset;
    QtShanoirProcessedDataset cl_processedDataset = tree->getStudyById(idStudy).getSubjectById(idSubject).getExamById(idExam).getDatasetById(idDataset).getProcessById(idProcess).getProcessedDatasetById(idProcessedDataset);
    str_processedDataset->name = cl_processedDataset.getName();
    str_processedDataset->comment = cl_processedDataset.getComment();
    str_processedDataset->processedDatasetCreationDate = cl_processedDataset.getProcessedDatasetCreationDate();
    return str_processedDataset;
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

//DAO_EXPORT struct PreUploadLists* getPreUploadLists()
//{
//    struct PreUploadLists* str_preUploadLists = new struct PreUploadLists;
//    QtShanoirUpload* upload = new QtShanoirUpload();
//    str_preUploadLists->processingList = upload->getProcessingList();
//    str_preUploadLists->datasetTypeList = upload->getDatasetTypeList();
//    str_preUploadLists->mrdatasetNatureList = upload->getMrdatasetNatureList();
//    str_preUploadLists->mrSpectroscopydatasetNatureList = upload->getMrSpectroscopydatasetNatureList();
//    str_preUploadLists->mrDatasetQualityProcedureTypeList = upload->getMrDatasetQualityProcedureTypeList();
//    str_preUploadLists->calibrationDatasetTypeList = upload->getCalibrationDatasetTypeList();
//    str_preUploadLists->templateDatasetNatureList = upload->getTemplateDatasetNatureList();
//    str_preUploadLists->parameterQuantificationNatureList = upload->getParameterQuantificationNatureList();
//    str_preUploadLists->spectNatureList = upload->getSpectNatureList();
//    return str_preUploadLists;
//}


QtShanoirUpload* upload = new QtShanoirUpload();

DAO_EXPORT QMap<int,QString> getProcessingList()
{
    if (upload->getProcessingList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireProcessingList();
        parse->parseProcessingList(xmlSerializer,upload);

    }
   return upload->getProcessingList();
}

DAO_EXPORT QStringList getDatasetTypeList()
{
    if (upload->getDatasetTypeList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireDatasetTypeList();
        parse->parseDatasetTypeList(xmlSerializer,upload);

    }
    return upload->getDatasetTypeList();
}

DAO_EXPORT QMap<int,QString> getMrdatasetNatureList()
{
    if (upload->getMrdatasetNatureList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireMrdatasetNatureList();
        parse->parseMrdatasetNatureList(xmlSerializer,upload);

    }
    return upload->getMrdatasetNatureList();
}

DAO_EXPORT QMap<int,QString> getMrSpectroscopydatasetNatureList()
{
    if (upload->getMrSpectroscopydatasetNatureList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireMrSpectroscopydatasetNatureList();
        parse->parseMrSpectroscopydatasetNatureList(xmlSerializer,upload);
    }
    return upload->getMrSpectroscopydatasetNatureList();
}

DAO_EXPORT QMap<int,QString> getMrDatasetQualityProcedureTypeList()
{
    if (upload->getMrDatasetQualityProcedureTypeList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireMrDatasetQualityProcedureTypeList();
        parse->parseMrDatasetQualityProcedureTypeList(xmlSerializer,upload);
    }
    return upload->getMrDatasetQualityProcedureTypeList();
}

DAO_EXPORT QMap<int,QString> getCalibrationDatasetTypeList()
{
    if (upload->getCalibrationDatasetTypeList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireCalibrationDatasetTypeList();
        parse->parseCalibrationDatasetTypeList(xmlSerializer,upload);
    }
    return upload->getCalibrationDatasetTypeList();
}

DAO_EXPORT QMap<int,QString> getProcessedDatasetTypeList()
{
    if (upload->getProcessedDatasetTypeList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireProcessedDatasetTypeList();
        parse->parseProcessedDatasetTypeList(xmlSerializer,upload);
    }
    return upload->getProcessedDatasetTypeList();
}

DAO_EXPORT QMap<int,QString> getTemplateDatasetNatureList()
{
    if (upload->getTemplateDatasetNatureList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireTemplateDatasetNatureList();
        parse->parseTemplateDatasetNatureList(xmlSerializer,upload);
    }
    return upload->getTemplateDatasetNatureList();
}

DAO_EXPORT QMap<int,QString> getParameterQuantificationNatureList()
{
    if (upload->getParameterQuantificationNatureList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireParameterQuantificationNatureList();
        parse->parseParameterQuantificationNatureList(xmlSerializer,upload);
    }
    return upload->getParameterQuantificationNatureList();
}

DAO_EXPORT QMap<int,QString> getSpectNatureList()
{
    if (upload->getSpectNatureList().isEmpty())
    {
        QtShanoirMain* service = new QtShanoirMain();
        ParseTree* parse = new ParseTree();
        QString xmlSerializer = service->acquireSpectNatureList();
        parse->parseSpectNatureList(xmlSerializer,upload);
    }
    return upload->getSpectNatureList();
}

DAO_EXPORT void uploadProcessedDatasetFiles(QList<struct ProcessedDatasetFilesAndAttributes*> filesList)
{
    QList<QtShanoirUploadProcessedDatasetAttributes> filesListToUpload;
    for(int i=0; i<filesList.size();i++)
    {
        QtShanoirUploadProcessedDatasetAttributes processedDatasetFile;
        processedDatasetFile.setFilename(filesList[i]->filename);
        processedDatasetFile.setStudyId(filesList[i]->studyId);
        processedDatasetFile.setInputDatasetIdList(filesList[i]->inputDatasetIdList);
        processedDatasetFile.setRefDatasetProcessingId(filesList[i]->refDatasetProcessingId);
        processedDatasetFile.setDatasetClass(filesList[i]->datasetClass);
        processedDatasetFile.setDatasetName(filesList[i]->datasetName);
        processedDatasetFile.setDatasetComment(filesList[i]->datasetComment);
        processedDatasetFile.setRefMrDatasetNatureId(filesList[i]->refMrDatasetNatureId);
        processedDatasetFile.setRefMrQualityProcedureTypeId(filesList[i]->refMrQualityProcedureTypeId);
        processedDatasetFile.setRefCalibrationDatasetTypeId(filesList[i]->refCalibrationDatasetTypeId);
        processedDatasetFile.setRefProcessedDatasetTypeId(filesList[i]->refProcessedDatasetTypeId);
        processedDatasetFile.setRefParameterQuantificationDatasetNatureId(filesList[i]->refParameterQuantificationDatasetNatureId);
        processedDatasetFile.setRefSpectDatasetNatureId(filesList[i]->refSpectDatasetNatureId);
        processedDatasetFile.setRefTemplateDatasetNatureId(filesList[i]->refTemplateDatasetNatureId);

        filesListToUpload.append(processedDatasetFile);
    }
    upload->uploadProcessedDatasetFiles(filesListToUpload);

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
