#include "qtshanoirprocess.h"

void QtShanoirProcess::setId(int id)
{
    this->id = id;
}

QString QtShanoirProcess::getName()
{
    return this->name;
}

void QtShanoirProcess::setName(QString name)
{
    this->name = name;
}

QDate QtShanoirProcess::getCreationDate()
{
    return this->creationDate;
}

void QtShanoirProcess::setCreationDate(QDate date)
{
    this->creationDate = date;
}
