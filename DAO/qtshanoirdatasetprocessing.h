#ifndef QTSHANOIRDATASETPROCESSING_H
#define QTSHANOIRDATASETPROCESSING_H

#include <QtCore>



class  QtShanoirDatasetProcessing
{
private:
    int id;
    QString name;

public:

    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
};

#endif // QTSHNAOIRDATASETPROCESSING_H
