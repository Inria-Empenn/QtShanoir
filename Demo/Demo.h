/*
 * Demo.h
 *
 *  Created on: 7 janv. 2011
 *      Author: aabadie
 */

#ifndef DEMO_H_
#define DEMO_H_

#include <QtGui>
#include "ui_demo.h"

class Demo : public QMainWindow, public Ui::Demo
{
    Q_OBJECT
    public:
        Demo(QWidget * parent = 0);
};

#endif /* DEMO_H_ */
