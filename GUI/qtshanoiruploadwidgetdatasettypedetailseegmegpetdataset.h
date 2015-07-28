#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSEEGMEGPETDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSEEGMEGPETDATASET_H
#include <QtGui>
#include <QWidget>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent = 0);
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
    void processedDatasetTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateEegMegPetDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsEegMegPetDataset *ui;
    QMap<int,QString> processedDatasetTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSEEGMEGPETDATASET_H


