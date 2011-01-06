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
class QListWidgetItem;
class QtShanoirTreeWidgetPrivate;

class QtShanoirTreeWidget : public QWidget
{
        Q_OBJECT
    public:
        QtShanoirTreeWidget(QWidget * parent = 0);

    private:
        QtShanoirTreeWidgetPrivate * d;
};

#endif /* QTSHANOIRTREEWIDGET_H_ */
