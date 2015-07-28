#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSTANDARDDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSTANDARDDATASET_H

#include <QtGui>
#include <QWidget>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent = 0);
    void buildTable();
    void fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    QString reduceFilenameToTwoDir(QString);
    void addCheckBox(int);
    void initConnections();

public slots:
    void rowSelectionChanged(int);
    void nameTextChanged(QString);
    void commentTextChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateStandardDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsStandardDataset *ui;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSTANDARDDATASET_H
