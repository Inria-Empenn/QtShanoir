/*
 * QtShanoirUploadWidget.h
 *
 *  Created on: 21 mai 2011
 *      Author: aabadie
 */

#ifndef QTSHANOIRUPLOADWIDGET_H_
#define QTSHANOIRUPLOADWIDGET_H_

#include <QtGui>
#include "ui_qtshanoiruploadwidget.h"

class QtShanoirUploadWidgetPrivate;

class QtShanoirUploadWidget : public QWidget, public Ui::QtShanoirUpload
{
    Q_OBJECT

    public:
        QtShanoirUploadWidget(QWidget * parent = 0);
    private:
        void
        initConnections();

    public slots:
        void
        upload();

        void
        browseDataset();

        void
        datasetNameChanged(QString name);

        void
        datasetCommentChanged(QString comment);

        void
        addDataset(int id);

        void
        datasetProcessingChanged(int index);

        void
        processingCommentChanged(QString comment);

    private:
        QtShanoirUploadWidgetPrivate * d;
};

#endif /* QTSHANOIRUPLOADWIDGET_H_ */
