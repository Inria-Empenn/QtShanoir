/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
