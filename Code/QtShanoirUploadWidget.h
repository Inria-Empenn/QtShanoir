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

        void
        print();
    private:
        void
        initConnections();

    public slots:
        void
        upload();

        void
        updateInputDataset(QMap<int, QString> );

        void
        updateProcessingComboBox(QMap<int, QString> );

        void
        updateStudyComboBox(QMap<int,QString>);

        void
        browseDataset();

        void
        datasetNameChanged(QString name);

        void
        datasetCommentChanged();

        void
        processingChanged(int index);

        void
        studyChanged(int index);

        void
        processingCommentChanged();

        void
        datasetTypeChanged(int index);

    signals:
        void
        uploadData(QMultiMap<QString, QString> mmap);

    private:
        QtShanoirUploadWidgetPrivate * d;
};

#endif /* QTSHANOIRUPLOADWIDGET_H_ */
