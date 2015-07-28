#ifndef QTSHANOIRDOWNLOADWIDGET_H
#define QTSHANOIRDOWNLOADWIDGET_H

#include<QtGui>
#include"qtshanoirprogresswidget.h"
#include "ui_qtshanoirdownloadwidget.h"
namespace Ui
{
class QtShanoirDownloadWidget;

}

class QtShanoirDownloadWidget: public QWidget
{
    Q_OBJECT
public:
    explicit QtShanoirDownloadWidget(QWidget *parent = 0);
    void initConnections();
    void modifyRow(int);
    void hideWidget();
    void showWidget();
signals:
    void callDownload(QString);
    void callBuildTableDownload();
public slots:
    void startDownload(QString);
    void chooseDir();
    void updateSelectedIds(QMap<int, QString>);
    void buildTableDownload();
    void removeDatasetFromSelectedIds(int);
private:
    Ui::QtShanoirDownloadWidget *ui;
    QMap<int,QString> selectedIds;
    QMap <int,int> mappingTable;


};

#endif // QTSHANOIRDOWNLOADWIDGET_H
