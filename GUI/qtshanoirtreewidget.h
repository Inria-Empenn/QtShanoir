#ifndef QTSHANOIRTREEWIDGET_H
#define QTSHANOIRTREEWIDGET_H


#include<QtGui>
#include "ui_qtshanoirtreewidget.h"
#include "qtshanoirtree.h"


namespace Ui
{
class QtShanoirTree;
}

class QtShanoirTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QtShanoirTreeWidget(QWidget *parent = 0);
    void initConnections();

    void extend(QTreeWidgetItem*item,int);
    void developTree(QString studyFilter,QTreeWidgetItem* item);
    void developStudy(QString study,QString subjectFilter,QTreeWidgetItem* item);
    void developSubject(QTreeWidgetItem* item);
    void developExam(QTreeWidgetItem* item);
    void developDataset(QTreeWidgetItem* item);
    void developProcess(QTreeWidgetItem* item);
    void clearTree();


signals:
    void mrExamQuery(QString);
    void datasetQuery(QString, QString);
    void processingQuery(QString);
    void id(int);
    void selected(QMap<int,QString>);
    void studyMap(QMap<int,QString>);
    void filename(QString);
    void queryFinished();
    void queryFailed(QString);
    void getStudyDetails(QString);
    void getSubjectDetails(int,int);
    void getExamDetails(int,int,int);
    void getDatasetDetails(int,int,int,int);
    void getProcessDetails(int,int,int,int,int);
    void getProcessedDatasetDetails(int,int,int,int,int,int);
    void callUpdateSelectedIds (QMap<int,QString>);


public slots:
    void buildTree();
    void itemClicked(QTreeWidgetItem*item, int);
    void updateCheckBoxes(QTreeWidgetItem*,int);
    void build(QString,QString,QDate,QString);

private:
    Ui::QtShanoirTree *ui;
    QTreeWidgetItem* tree;
    QMap<int,QString> selectedIds;
};

#endif // QTSHANOIRTREEWIDGET_H
