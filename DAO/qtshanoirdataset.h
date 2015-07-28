#ifndef QTSHANOIRDATASET_H
#define QTSHANOIRDATASET_H

#include <QtCore>
#include "qtshanoirdatasetprocessing.h"


class  QtShanoirDataset
{
private:
    int id;
    QString name;
    QDate creationDate;
    QString comment;
    float repetitionTime;
    float flipAngle;
    float echoTime;
    QList<QtShanoirDatasetProcessing> datasetProcessingList;

public:
    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    QDate getCreationDate();
    void setCreationDate(QDate);
    QString getComment();
    void setComment(QString);
    float getRepetitionTime();
    void setRepetitionTime(float);
    float getFlipAngle();
    void setFlipAngle(float);
    float getEchoTime();
    void setEchoTime(float);
    void insertDatasetProcessing(QtShanoirDatasetProcessing);
    void displayDatasetProcessingList();
    QMap<int,QString> getDatasetProcessingList();
};

#endif // QTSHANOIRDATASET_H
