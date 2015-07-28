#ifndef QTSHANOIRUPLOAD_H
#define QTSHANOIRUPLOAD_H

#include <QtCore>

class  QtShanoirUpload
{
private:
    int processingId;
    int studyId;
    QString datasetName;
    QString datasetPath;
    QString resultDatasetType;
    QStringList processingDatatype;
    QString datasetComment;
    QString processingComment;
    QList<int> inputDatasetList;
    QMultiMap<QString, QString> uploadData;
public:
    QtShanoirUpload();
    int getProcessingId();
    void setProcessingId(int);
    int getStudyId();
    void setStudyId(int);
    QString getDatasetName();
    void setDatasetName(QString);
    QString getDatasetPath();
    void setDatasetPath (QString);
    QString getResultDatasetType();
    void setResultDatasetType(QString);
    QString getDatasetComment();
    void setDatasetComment(QString);
    QString getProcessingComment();
    void setProcessingComment(QString);
};

#endif // QTSHANOIRUPLOAD_H
