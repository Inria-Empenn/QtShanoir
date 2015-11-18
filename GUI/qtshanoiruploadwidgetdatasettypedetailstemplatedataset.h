#ifndef QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSTEMPLATEDATASET_H
#define QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSTEMPLATEDATASET_H

#include <QtGui>
#include <QWidget>
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset;
}

class QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files, QWidget *parent = 0);
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
    void templateDatasetTypeComboBoxChanged(QString);
    void itemTableChanged(QTableWidgetItem*);
    void checkAllClicked();
    void uncheckAllClicked();
    void resetClicked();

signals:
void callUpdateTemplateDatasetFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);

private:
    Ui::QtShanoirUploadWidgetDatasetTypeDetailsTemplateDataset *ui;
    QMap<int,QString> templateDatasetTypeList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUploadInitial;
    QList<int> selectedRows;
};

#endif // QTSHANOIRUPLOADWIDGETDATASETTYPEDETAILSTEMPLATEDATASET_H
