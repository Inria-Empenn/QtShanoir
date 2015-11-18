#ifndef QTSHANOIRUPLOADWIDGETDRAGFILES_H
#define QTSHANOIRUPLOADWIDGETDRAGFILES_H

#include <QtGui>
#include <QWizard>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include "ui_qtshanoiruploadwidgetdragfiles.h"
#include "qtshanoiruploadwidgetshowsteps.h"
#include "qtshanoiruploadprocesseddatasetattributestemp.h"

namespace Ui
{
class QtShanoirUploadWidgetDragFiles;
}

class QtShanoirUploadWidgetDragFiles : public QWizardPage
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetDragFiles(QWidget *parent = 0);
    void addRow(QString& file);
    void attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* showsteps);
    void initConnections();
    bool validatePage();
    void fillComboBox();
protected:
     void dragEnterEvent(QDragEnterEvent* event);
     void dragLeaveEvent(QDragLeaveEvent* event);
     void dragMoveEvent(QDragMoveEvent* event);
     void dropEvent(QDropEvent* event);
public slots:
    void deleteClicked(int);
    void on_add_clicked();
    void clearAll();
    void toCallSelectStudy(QString);
signals:
    void callUpdateFilesList(QStringList);
    void callSelectStudy(QString);
    void callUpdateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp>);
private:
    Ui::QtShanoirUploadWidgetDragFiles *ui;
    QtShanoirUploadWidgetShowSteps* showsteps;

    QStringList filesList;
    QString studySelected;
    QMap<int,QString> studyList;
    QList<QtShanoirUploadProcessedDatasetAttributesTemp> filesToUpload;
    //QTableWidget * filesTable;
};

#endif // QTSHANOIRUPLOADWIDGETDRAGFILES_H
