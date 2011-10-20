/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
