#include "qtshanoiruploadwidget.h"



QtShanoirUploadWidget::QtShanoirUploadWidget(QWidget *parent): QWizard(parent)
{
    setWizardStyle(QWizard::ClassicStyle);
    dragFiles = new QtShanoirUploadWidgetDragFiles();
    addPage(dragFiles);

    selectInputs = new QtShanoirUploadWidgetSelectInputs();
    addPage(selectInputs);

    selectCoresFilesInputs = new QtShanoirUploadWidgetCoresFilesInputs();
    addPage(selectCoresFilesInputs);

    selectProcess = new QtShanoirUploadWidgetSelectProcess();
    addPage(selectProcess);

    selectCoresFilesProcessDataset = new QtShanoirUploadWidgetCoressFilesProcessDataset();
    addPage(selectCoresFilesProcessDataset);

    datasetTypeDetails = new QtShanoirUploadWidgetDatasetTypeDetails();
    addPage(datasetTypeDetails);

    adjustSize();
    setWindowTitle(tr("Upload"));
    initConnections();
}

void QtShanoirUploadWidget::initConnections()
{
    QObject::connect(dragFiles,SIGNAL(callUpdateFilesList(QStringList)),selectCoresFilesInputs, SLOT (updateFilesList(QStringList)));
    QObject::connect(dragFiles,SIGNAL(callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)),selectCoresFilesInputs, SLOT (updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));
    QObject::connect(dragFiles,SIGNAL(callSelectStudy(QString)),selectInputs, SLOT (selectStudy(QString)));
    QObject::connect(dragFiles,SIGNAL(callUpdateFilesList(QStringList)),selectCoresFilesProcessDataset, SLOT (updateFilesList(QStringList)));



    QObject::connect(selectInputs,SIGNAL(callUpdateSelectedInputsDataset(QMap<int,QString>)),selectCoresFilesInputs, SLOT (updateSelectedInputsDataset(QMap<int,QString>)));

    QObject::connect(selectCoresFilesInputs,SIGNAL(callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)),selectCoresFilesProcessDataset, SLOT (updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));

    QObject::connect(selectProcess,SIGNAL(callUpdateProcessList(QMap<int,QString>)),selectCoresFilesProcessDataset, SLOT (updateProcessList(QMap<int,QString>)));

    QObject::connect(selectCoresFilesProcessDataset,SIGNAL(callUpdateDatasetTypeSelectedList(QStringList)),datasetTypeDetails, SLOT (updateDatasetTypeSelectedList(QStringList)));
    QObject::connect(selectCoresFilesProcessDataset,SIGNAL(callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)),datasetTypeDetails, SLOT (updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>)));


}

void QtShanoirUploadWidget::buildUpload()
{


}

