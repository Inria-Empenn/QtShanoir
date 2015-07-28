#ifndef QTSHANOIRUPLOADWIDGETSELECTPROCESS_H
#define QTSHANOIRUPLOADWIDGETSELECTPROCESS_H

#include<QWizard>
#include"qtshanoiruploadwidgetshowsteps.h"
#include "ui_qtshanoiruploadwidgetselectprocess.h"

namespace Ui
{
class QtShanoirUploadWidgetSelectProcess;
}
class QtShanoirUploadWidgetSelectProcess: public QWizardPage
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetSelectProcess(QWidget *parent = 0);
    void attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* showsteps);
    void initConnections();
    bool validatePage();
public slots:
    void selectAllClicked();
    void unselectAllClicked();
    void updateCheckBoxes(QListWidgetItem*);
signals:
    void callUpdateProcessList(QMap<int,QString>);
private:
    Ui::QtShanoirUploadWidgetSelectProcess *ui;
    QtShanoirUploadWidgetShowSteps* showsteps;
    QMap<int,QString> processList;
    QMap<int,QString> selectedProcessList;
};

#endif // QTSHANOIRUPLOADWIDGETSELECTPROCESS_H

