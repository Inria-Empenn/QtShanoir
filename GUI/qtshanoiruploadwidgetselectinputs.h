#ifndef QTSHANOIRUPLOADWIDGETSELECTINPUTS_H
#define QTSHANOIRUPLOADWIDGETSELECTINPUTS_H

#include <QtGui>
#include <QWizard>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QMessageBox>
#include "qtshanoiruploadwidgetshowsteps.h"
#include "ui_qtshanoiruploadwidgetselectinputs.h"
#include "qtshanoirtreewidget.h"

namespace Ui
{
class QtShanoirUploadWidgetSelectInputs;
}

class QtShanoirUploadWidgetSelectInputs : public QWizardPage
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetSelectInputs(QWidget *parent = 0);
    void attchShowStepsWidget(QtShanoirUploadWidgetShowSteps* showsteps);
    void attachTreeWidget(QtShanoirTreeWidget * tree);
    void initConnections();
    bool validatePage();
public slots:
    void selectStudy(QString);
    void updateSelectedIds (QMap<int,QString>);
signals:
    void callUpdateSelectedInputsDataset(QMap<int,QString>);
private:
    Ui::QtShanoirUploadWidgetSelectInputs *ui;
    QtShanoirUploadWidgetShowSteps* showsteps;
    QtShanoirTreeWidget* tree;
    QString studySelected;
    QMap<int,QString> selectedInputsDatasetIds;
};

#endif // QTSHANOIRUPLOADWIDGETSELECTINPUTS_H
