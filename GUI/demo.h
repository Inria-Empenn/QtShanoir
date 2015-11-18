#ifndef DEMO_H
#define DEMO_H

#include "qtshanoirtreewidget.h"
#include "ui_demo.h"
#include "qtshanoiruploadwidget.h"
#include "qtshanoirmain.h"
#include "qtshanoirsearchwidget.h"
#include "qtshanoirdetailswidget.h"
#include "qtshanoirdownloadwidget.h"
#include "qtshanoirsettingswidget.h"
#include "qtshanoirerrorwidget.h"
#include "qtshanoiruploadwidgetintermediate.h"



class Demo : public QMainWindow, private Ui::Demo
{
private:
    QtShanoirTreeWidget * tree;
    QtShanoirSearchWidget* search;
    QtShanoirSettingsWidget* settings;
    QtShanoirDetailsWidget * details;
    QtShanoirUploadWidget * upload;
    QtShanoirUploadWidgetIntermediate* uploadIntermediate;
    QtShanoirDownloadWidget * download;
    QtShanoirErrorWidget * error;
    QMap<int,QString> selectedIds;

public:
   //QtShanoirMain shanoirmain;
    explicit Demo(QWidget * parent = 0);
    void initConnections();
    void attachTreeWidget(QtShanoirTreeWidget * tree);
    void attachSettingsWidget(QtShanoirSettingsWidget * settings);
    void attachSearchWidget(QtShanoirSearchWidget * search);
    void attachDetailsWidget(QtShanoirDetailsWidget * details);
    void attachDownloadWidget(QtShanoirDownloadWidget * download);
    void attachErrorWidget(QtShanoirErrorWidget * error);
    void clearTree();
	
signals:
    void startUpload();
    void downloadFinished(QString fileName, QString xmlFileName);
    void queryFailed(QString reason);
	//void progressHidden();

public slots:
    void setDownloadMetadata(int state);


};

#endif // DEMO_H
