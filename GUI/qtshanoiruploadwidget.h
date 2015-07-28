#ifndef QTSHANOIRUPLOADWIDGET_H
#define QTSHANOIRUPLOADWIDGET_H

#include <QtGui>
#include "qtshanoirupload.h"
#include "ui_qtshanoiruploadwidget.h"


class  QtShanoirUploadWidget : public QWidget, private Ui::QtShanoirUpload
{
    Q_OBJECT
private:
    QtShanoirUpload data;
public:
    explicit QtShanoirUploadWidget(QWidget *parent = 0);
    void initConnections();
    void updateInputDataset(QMap<int, QString> );
    void updateProcessingComboBox(QMap<int, QString> );
    void updateStudyComboBox(QMap<int,QString>);

    

signals:
    void uploadData(QMultiMap<QString, QString> mmap);

public slots:
    void upload();
	void browseDataset();
	void datasetNameChanged(QString name);
    void datasetCommentChanged(); //a revoir
    void processingChanged(int index);
    void studyIdChanged(int index);
    void processingCommentChanged(); // a revoir
    void resultdatasetTypeChanged(int index);
};

#endif // QTSHANOIRUPLOADWIDGET_H
