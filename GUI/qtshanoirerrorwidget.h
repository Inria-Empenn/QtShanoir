#ifndef QTSHANOIRERRORWIDGET
#define QTSHANOIRERRORWIDGET

#include <QtGui>
#include <QtCore>
#include "ui_qtshanoirerrorwidget.h"

namespace Ui
{
class QtShanoirErrorWidget;
}

class QtShanoirErrorWidget : public QWidget
{
    Q_OBJECT


public:
    explicit QtShanoirErrorWidget(QWidget *parent = 0);
public slots:
    void printMessage(QString);
private:
    Ui::QtShanoirErrorWidget *ui;


};

#endif // QTSHANOIRERRORWIDGET

