#ifndef PARSETREE_H
#define PARSETREE_H
#include "qtshanoirtree.h"
#include "qtshanoirupload.h"


class  ParseTree
{
private:
    QtShanoirTree* tree;

public:
    ParseTree();
    void parseStudy_Subject(QString xmlserializer, QtShanoirTree* tree);
    //void parseExam(QString xmlserializer,QtShanoirSubject& subject);
    void parseExam(QString xmlserializer,int idStudy, int idSubject, QtShanoirTree* tree);
    void parseDataset(QString xmlserializer, int idStudy, int idSubject, int idExam, QtShanoirTree* tree);
    void parseProcess_ProcessedDataset(QString xmlserializer, int idStudy, int idSubject, int idExam, int idDataset,QtShanoirTree* tree);

    void parseProcessingList(QString xmlserializer,QtShanoirUpload* upload);
    void parseDatasetTypeList(QString xmlserializer,QtShanoirUpload* upload);
    void parseMrdatasetNatureList(QString xmlserializer, QtShanoirUpload* upload);
    void parseMrSpectroscopydatasetNatureList(QString xmlserializer, QtShanoirUpload* upload);
    void parseMrDatasetQualityProcedureTypeList(QString xmlserializer, QtShanoirUpload* upload);
    void parseCalibrationDatasetTypeList(QString xmlserializer, QtShanoirUpload* upload);
    void parseProcessedDatasetTypeList(QString xmlserializer, QtShanoirUpload* upload);
    void parseTemplateDatasetNatureList(QString xmlserializer, QtShanoirUpload* upload);
    void parseParameterQuantificationNatureList(QString xmlserializer, QtShanoirUpload* upload);
    void parseSpectNatureList(QString xmlserializer, QtShanoirUpload* upload);
    void RemoveEnveloppe();

};

#endif // PARSETREE_H
