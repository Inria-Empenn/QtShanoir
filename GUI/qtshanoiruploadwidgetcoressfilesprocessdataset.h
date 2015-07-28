#ifndef QTSHANOIRUPLOADWIDGETCORESSFILESPROCESSDATASET_H
#define QTSHANOIRUPLOADWIDGETCORESSFILESPROCESSDATASET_H


#include <QtGui>
#include <QWizard>
#include <QTableWidget>
#include <QCheckBox>
#include <QMessageBox>
#include "qtshanoiruploadwidgetshowsteps.h"
#include "ProxyModelWithHeaderModels.h"
#include "ui_qtshanoiruploadwidgetcoressfilesprocessdataset.h"
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetCoressFilesProcessDataset;
}

class QtShanoirUploadWidgetCoressFilesProcessDataset: public QWizardPage
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetCoressFilesProcessDataset(QWidget *parent = 0);
    void attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* showsteps);
    void buildTable();
    void clearTable();
    void initConnections();
    void buildDataModel(QStandardItemModel& headerModel);
    void buildHorizontalHeaderModel(QStandardItemModel& model);
    void buildVerticalHeaderModel(QStandardItemModel& model);
    QString reduceFilenameToTwoDir(QString);
    bool validatePage();
    bool validationProcessDatasetType();
    bool matchExist(int,int,int);
    int getMatchedProcessId(int);
    QString getMatchedDatasetClass(int);
    int countCheckedCellsInColumn(int);


public slots:
    void updateProcessList(QMap<int,QString>);
    void updateFilesList(QStringList);
    void updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void resetClicked();
    void columnChanged(QStandardItem*);
signals:
    void callUpdateDatasetTypeSelectedList(QStringList);
    void callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
private:
    Ui::QtShanoirUploadWidgetCoressFilesProcessDataset *ui;
    QtShanoirUploadWidgetShowSteps* showsteps;
    QMap<int,QString> processList;
    QStringList filesList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QStringList datasetTypeList;
    QStringList datasetTypeSelectedList;
    QStandardItemModel horizontalHeaderModel;
    QStandardItemModel verticalHeaderModel;
    QStandardItemModel dataModel;
    ProxyModelWithHeaderModels proxyModel;
    int columnCount;
    int rowCount;
};
#endif // QTSHANOIRUPLOADWIDGETCORESSFILESPROCESSDATASET_H



