#ifndef QTSHANOIRPROCESS_H
#define QTSHANOIRPROCESS_H

#include <QtCore>
#include "qtshanoirprocesseddataset.h"


class  QtShanoirProcess
{
private:
    int id;
    QString name;
    QDate creationDate;
    QList<QtShanoirProcessedDataset> processedDatasetList;

public:
    QtShanoirProcess();
    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    QDate getCreationDate();
    void setCreationDate(QDate);
    QtShanoirProcessedDataset& getProcessedDatasetById(int id);
    void insertProcessedDataset(QtShanoirProcessedDataset);
    void displayProcessedList();
    QMap<int,QString> getProcessedDatasetList();
};

#endif // QTSHANOIRPROCESS_H
