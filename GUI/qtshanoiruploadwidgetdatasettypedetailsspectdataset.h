#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSPECTDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSPECTDATASET_H

#include <QWidget>
#include <QMap>
#include <QtGui>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetDatasettypeDetailsSpectDataset;
}

class QtShanoirUploadWidgetDatasettypeDetailsSpectDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasettypeDetailsSpectDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent = 0);
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
    void spectDatasetNatureComboBoxChanged(QString);
    void processedDatasetTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
    void callUpdateSpectDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasettypeDetailsSpectDataset *ui;
    QMap<int,QString> spectDatasetNatureList;
    QMap<int,QString> processedDatasetTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSSPECTDATASET_H
