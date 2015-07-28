#ifndef QTSHANOIRUPLOADWIDGET_H
#define QTSHANOIRUPLOADWIDGET_H
#include <QWizard>
#include <QMessageBox>

#include "qtshanoiruploadwidgetdragfiles.h"
#include "qtshanoiruploadwidgetselectinputs.h"
#include "qtshanoiruploadwidgetcoresfilesinputs.h"
#include "qtshanoiruploadwidgetselectprocess.h"
#include "qtshanoiruploadwidgetcoressfilesprocessdataset.h"
#include "qtshanoiruploadwidgetdatasettypedetails.h"

class QtShanoirUploadWidget :public QWizard
{
    Q_OBJECT

public:
    QtShanoirUploadWidget(QWidget *parent = 0);
    void initConnections();
public slots:
    void buildUpload();


private:
    QtShanoirUploadWidgetDragFiles* dragFiles;
    QtShanoirUploadWidgetSelectInputs* selectInputs;
    QtShanoirUploadWidgetCoresFilesInputs* selectCoresFilesInputs;
    QtShanoirUploadWidgetSelectProcess* selectProcess;
    QtShanoirUploadWidgetCoressFilesProcessDataset* selectCoresFilesProcessDataset;
    QtShanoirUploadWidgetDatasetTypeDetails* datasetTypeDetails;

};


#endif // QTSHANOIRUPLOADWIDGET_H
