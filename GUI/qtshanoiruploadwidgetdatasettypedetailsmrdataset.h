#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRDATASET_H

#include <QWidget>
#include <QMap>
#include <QtGui>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
    class QtShanoirUploadWidgetDatasetTypeDetailsMrDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsMrDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsMrDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files,QWidget *parent = 0);
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
    void mrDatasetNatureComboBoxChanged(QString);
    void mrDatasetQualityProcedureTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();
signals:
    void callUpdateMrDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsMrDataset *ui;
    QMap<int,QString> mrDatasetNatureList;
    QMap<int,QString> mrDatasetQualityProcedureTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSMRDATASET_H
