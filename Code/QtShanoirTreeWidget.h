/*
 * QtShanoirTreeWidget.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRTREEWIDGET_H_
#define QTSHANOIRTREEWIDGET_H_

#include <QtGui>
#include "ui_qtshanoirtreewidget.h"

class QTreeWidgetItem;
class QtShanoirTreeWidgetPrivate;

class QtShanoirTreeWidget : public QWidget, public Ui::QtShanoirTree
{
    Q_OBJECT
    public:
        QtShanoirTreeWidget(QWidget * parent = 0);;

    signals:
        void
        mrExamQuery(QString);
        void
        datasetQuery(QString, QString);
        void
        processingQuery(QString);
        void
        id(int);
        void
        selected(QMap<int,QString>);
        void
        studyMap(QMap<int,QString>);
        void
        filename(QString);
        void
        queryFinished();

    public slots:
        void itemDoubleClicked(QTreeWidgetItem* item, int column);
        void itemClicked(QTreeWidgetItem* item, int column);
        void parseAcquisition(QString xmlserial, QRegExp datasetNameFilter);
        void
        parseProcessingData(QString xmlserial);
        void parseStudy(QString xmlserial, QRegExp patientNameFilter);
        void parseMrExamination(QString xmlserial, QString dateFilter);
        void contextExportMenu( const QPoint point );

    private:
        void
        initConnections();
        QtShanoirTreeWidgetPrivate * d;
        void
        updateCheckBoxes(QTreeWidgetItem * item);
};

#endif /* QTSHANOIRTREEWIDGET_H_ */
