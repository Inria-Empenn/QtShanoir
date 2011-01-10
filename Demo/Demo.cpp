/*
 * Demo.cpp
 *
 *  Created on: 7 janv. 2011
 *      Author: aabadie
 */

#include <Demo.h>
#include <QtShanoir.h>

class DemoPrivate
{
    public:
        QtShanoir * controller;
};

Demo::Demo(QWidget * parent) :
    d(new DemoPrivate)
{
    setupUi(this);
    QObject::connect(findButton, SIGNAL(clicked()), this, SLOT(find()));

    d->controller = new QtShanoir;
    d->controller->attachTreeWidget(treeWidget);
    d->controller->initWS();
}

void
Demo::find()
{
    d->controller->doQuery("StudyFindId");
}
