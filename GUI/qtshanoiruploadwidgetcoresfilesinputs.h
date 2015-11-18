#ifndef QTSHANOIRUPLOADWIDGETCORESFILESINPUTS_H
#define QTSHANOIRUPLOADWIDGETCORESFILESINPUTS_H
#include <QtGui>
#include <QWizard>
#include <QTableWidget>
#include "qtshanoiruploadwidgetshowsteps.h"
#include "ui_qtshanoiruploadwidgetcoresfilesinputs.h"
#include "qtshanoiruploadprocesseddatasetattributestemp.h"


namespace Ui
{
class QtShanoirUploadWidgetCoresFilesInputs;
}

class QtShanoirUploadWidgetCoresFilesInputs: public QWizardPage
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetCoresFilesInputs(QWidget *parent = 0 );
    void attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* );
    void buildTable();
    void initConnections();
    void addCheckBox(int,int);
    bool validatePage();
    bool matchExist(int);
    QString reduceFilenameToTwoDir(QString);
    QList<int> getInputsDatasetIds(int);
public slots:
    void updateFilesList(QStringList);
    void resetClicked();
    void updateSelectedInputsDataset(QMap<int,QString>);
    void updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    void cellCheckBoxChanged(QString);
    void checkAllClicked();
signals:
    void callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetCoresFilesInputs *ui;
    QtShanoirUploadWidgetShowSteps* showsteps;
    QStringList filesList;
    QMap<int,QString> selectedInputsDatasetIds;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QStringList verticalLabels;

};

#endif // QTSHANOIRUPLOADWIDGETCORESFILESINPUTS_H
