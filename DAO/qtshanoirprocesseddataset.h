#ifndef QTSHANOIRPROCESSEDDATASET_H
#define QTSHANOIRPROCESSEDDATASET_H

#include <QtCore>



class  QtShanoirProcessedDataset
{
private:
    int id;
    QString name;
    QString comment;
    QDate processedDatasetCreationDate;
	
public:

    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    QString getComment();
    void setComment(QString);
    QDate getProcessedDatasetCreationDate();
    void setProcessedDatasetCreationDate(QDate);
};

#endif // QTSHANOIRPROCESSEDDATASET_H
