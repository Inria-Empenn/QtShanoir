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
    QtShanoir::instance()->attachProgressWidget(progressWidget);
    QtShanoir::instance()->attachTreeWidget(treeWidget);
    QtShanoir::instance()->attachUploadWidget(uploadWidget);
    QtShanoir::instance()->init();

    QObject::connect(findButton, SIGNAL(clicked()), QtShanoir::instance(), SLOT(find()));
    QObject::connect(downloadButton, SIGNAL(clicked()), QtShanoir::instance(), SLOT(download()));

    QObject::connect(metadataCheckBox, SIGNAL(stateChanged(int)), QtShanoir::instance(), SLOT(setDownloadMetadata(int)));
}
