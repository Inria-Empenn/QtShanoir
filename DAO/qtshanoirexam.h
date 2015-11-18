#ifndef QTSHANOIREXAM
#define QTSHANOIREXAM

#include <QtCore>
#include "qtshanoirdataset.h"


class   QtShanoirExam
{
private:
    int id;
    int idSubject;
    QString comment;
    QDate date;
    QList<QtShanoirDataset> datasetList;

public:
    int getId();
    void setId(int);
    int getIdSubject();
    void setIdSubject(int);
    QString getComment();
    void setComment(QString);
    QDate getDate();
    void setDate(QDate);
    QtShanoirDataset& getDatasetById(int id);
    void insertDataset(QtShanoirDataset);
    void displayDatasetList();
    QMap<int,QString> getDatasetList();
};

#endif // QTSHANOIREXAM

