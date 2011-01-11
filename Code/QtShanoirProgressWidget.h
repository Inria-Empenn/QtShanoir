/*
 * QtShanoirProgressWidget.h
 *
 *  Created on: 11 janv. 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRPROGRESSWIDGET_H_
#define QTSHANOIRPROGRESSWIDGET_H_

#include <QtGui>
#include "ui_qtshanoirprogress.h"

class QtShanoirProgressWidgetPrivate;

class QtShanoirProgressWidget : public QWidget, public Ui::QtShanoirProgress
{
        Q_OBJECT
    public:
        QtShanoirProgressWidget(QWidget * parent = 0);


    private:
        QtShanoirProgressWidgetPrivate *d;
};

#endif /* QTSHANOIRPROGRESSWIDGET_H_ */
