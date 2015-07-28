#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSCALIBRATIONDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSCALIBRATIONDATASET_H

#include <QtGui>
#include <QWidget>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui {
class QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files,QWidget *parent = 0);
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
    void calibrationDatasetTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateCalibrationDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsCalibrationDataset *ui;
    QMap<int,QString> calibrationDatasetTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSCALIBRATIONDATASET_H
