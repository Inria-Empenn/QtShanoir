#include "qtshanoiruploadwidgetintermediate.h"

QtShanoirUploadWidgetIntermediate::QtShanoirUploadWidgetIntermediate()
{


}

void QtShanoirUploadWidgetIntermediate::buildUpload()
{
    upload = new QtShanoirUploadWidget();
    upload->resize(900,600);
    upload->show();
}
