#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H
#include<QtGui>
#include "ui_qtshanoirdetaislwidget.h"


namespace Ui
{
class QtShanoirDetailsWidget;
}
class QtShanoirDetailsWidget : public QWidget
{
    Q_OBJECT

public:
explicit QtShanoirDetailsWidget(QWidget *parent = 0);
public slots:
    void getStudyDetails(QString);
    void getSubjectDetails(int,int);
    void getExamDetails(int,int,int);
    void getDatasetDetails(int,int,int,int);
    void getProcessDetails(int,int,int,int,int);
    void getProcessedDatasetDetails(int,int,int,int,int,int);
private:
    Ui::QtShanoirDetailsWidget *ui;
};

#endif // DETAILSWIDGET_H
