#ifndef QTSHANOIRDOWNLOAD_H
#define QTSHANOIRDOWNLOAD_H

#include <QtCore>
#include <QDomDocument>
#include <quazip.h>
#include <quazipfile.h>

class QtShanoirDownload
{
public:
    QtShanoirDownload();
    void downloadDataset(QByteArray,QString,QString);
    void getFileName(QString);
    QString getDownloadFileName();
    void setDownloadFileName(QString);
private:
    QString downloadFileName;

};

#endif // QTSHANOIRDOWNLOAD_H
