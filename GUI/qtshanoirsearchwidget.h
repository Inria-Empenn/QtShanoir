#ifndef QTSHANOIRSEARCHWIDGET
#define QTSHANOIRSEARCHWIDGET

#include <QtGui>
#include <QtCore>
#include "ui_qtshanoirsearchwidget.h"


namespace Ui
{
class QtShanoirSearchWidget;
}

class QtShanoirSearchWidget : public QWidget
{
    Q_OBJECT


public:
    explicit QtShanoirSearchWidget(QWidget *parent = 0);
    void initConnections();
    void reset();
signals:
    void startFind(QString,QString,QDate,QString);

public slots:
    void studyTextChanged(QString);
    void patientTextChanged(QString);
    void examDateChanged(QDate);
    void datasetTextChanged(QString);
    void findValidation();

private:
    Ui::QtShanoirSearchWidget *ui;

};

#endif // QTSHANOIRSEARCHWIDGET

