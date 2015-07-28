#ifndef UPLOADINTERMEDIATE_H
#define UPLOADINTERMEDIATE_H

#include "qtshanoiruploadwidget.h"

class QtShanoirUploadWidgetIntermediate: public QObject
{
    Q_OBJECT
public:
    QtShanoirUploadWidgetIntermediate();
public slots:
    void buildUpload();
private:
    QtShanoirUploadWidget* upload;

};

#endif // UPLOADINTERMEDIATE_H
