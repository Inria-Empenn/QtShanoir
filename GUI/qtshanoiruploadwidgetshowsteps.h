#ifndef QTSHANOIRUPLOADWIDGETSHOWSTEPS_H
#define QTSHANOIRUPLOADWIDGETSHOWSTEPS_H
#include "ui_qtshanoiruploadwidgetshowsteps.h"
#include <QWidget>
#include <QtGui>
namespace Ui
{
class QtShanoirUploadWidgetShowSteps;
}
class QtShanoirUploadWidgetShowSteps: public QWidget, private Ui::QtShanoirUploadWidgetShowSteps
{
    Q_OBJECT
public:
    explicit QtShanoirUploadWidgetShowSteps(QWidget *parent = 0);
    void steps(int);
private:
    Ui::QtShanoirUploadWidgetShowSteps *ui;
};

#endif // QTSHANOIRUPLOADWIDGETSHOWSTEPS_H

