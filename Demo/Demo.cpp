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
    d->controller = new QtShanoir;
    d->controller->attachTreeWidget(treeWidget);
    d->controller->attachProgressWidget(progressWidget);
    d->controller->initWS();

    QObject::connect(findButton, SIGNAL(clicked()), this, SLOT(find()));
    QObject::connect(downloadButton, SIGNAL(clicked()), d->controller, SLOT(download()));
}

void
Demo::find()
{
    d->controller->clearTree();
    d->controller->doQuery("StudyFindId");
}
