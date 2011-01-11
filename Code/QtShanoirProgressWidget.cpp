/*
 * QtShanoirProgressWidget.cpp
 *
 *  Created on: 11 janv. 2011
 *      Author: aabadie
 */

#include <QtShanoirProgressWidget.h>

class QtShanoirProgressWidgetPrivate
{
    public:
};

QtShanoirProgressWidget::QtShanoirProgressWidget(QWidget * parent) :
    d(new QtShanoirProgressWidgetPrivate)
{
    setupUi(this);
}
