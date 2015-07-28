#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSPARAMETERQUANTIFICATIONDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSPARAMETERQUANTIFICATIONDATASET_H

#include <QtGui>
#include <QWidget>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui {
class QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent = 0);
    void fillComboBox();
    void buildTable();
    void fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    QString reduceFilenameToTwoDir(QString);
    void addCheckBox(int);
    void initConnections();

public slots:
    void rowSelectionChanged(int);
    void nameTextChanged(QString);
    void commentTextChanged(QString);
    void parameterQuantificationDatasetNatureComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateParameterQuantificationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsParameterQuantificationDataset *ui;
    QMap<int,QString> parameterQuantificationDatasetNatureList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSPARAMETERQUANTIFICATIONDATASET_H
