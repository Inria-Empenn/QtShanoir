#ifndef PARSETREE_H
#define PARSETREE_H
#include "qtshanoirtree.h"
#include "qtshanoirdatasetprocessing.h"


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
    void parseDatasetProcesing(QString xmlserializer, int idStudy, int idSubject, int idExam, int idDataset,QtShanoirTree* tree);
    void RemoveEnveloppe();

};

#endif // PARSETREE_H
