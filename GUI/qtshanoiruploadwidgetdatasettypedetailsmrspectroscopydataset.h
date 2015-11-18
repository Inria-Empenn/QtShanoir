#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRSPECTROSCOPYDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRSPECTROSCOPYDATASET_H

#include "qtshanoiruploadprocesseddatasetattributestemp.h"
#include <QWidget>
#include <QtGui>

namespace Ui {
class QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files,QWidget *parent = 0);
    void fillComboBoxes();
    void buildTable();
    void fillTable(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
    QString reduceFilenameToTwoDir(QString);
    void addCheckBox(int);
    void initConnections();

public slots:
    void rowSelectionChanged(int);
    void nameTextChanged(QString);
    void commentTextChanged(QString);
    void mrSpectroscopyDatasetNatureComboBoxChanged(QString);
    void mrDatasetQualityProcedureTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateMrSpectroscopyDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsMrSpectroscopyDataset *ui;
    QMap<int,QString> mrSpectroscopyDatasetNatureList;
    QMap<int,QString> mrDatasetQualityProcedureTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRSPECTROSCOPYDATASET_H


