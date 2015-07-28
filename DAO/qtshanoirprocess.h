#ifndef QTSHANOIRPROCESS_H
#define QTSHANOIRPROCESS_H

#include <QtCore>



class  QtShanoirProcess
{
private:
    int id;
    QString name;
    QDate creationDate;

public:
    QtShanoirProcess();
    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    QDate getCreationDate();
    void setCreationDate(QDate);
};

#endif // QTSHANOIRPROCESS_H
