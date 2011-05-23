/*
 * QtShanoirUploadWidget.cpp
 *
 *  Created on: 21 mai 2011
 *      Author: aabadie
 */

#include <QtShanoirUploadWidget.h>

class QtShanoirUploadWidgetPrivate
{
    public:
        int datasetId;
        int processingId;
        QString datasetName;
        QString datasetPath;
        QString datasetComment;
        QString processingComment;
        QList<int> inputDatasetList;

};

QtShanoirUploadWidget::QtShanoirUploadWidget(QWidget * parent) :
    d(new QtShanoirUploadWidgetPrivate)
{
    setupUi(this);
    initConnections();
    d->datasetId = 0;
    d->processingId = 0;
    d->datasetName = "";
    d->datasetPath = "";
    d->datasetComment = "";
    d->processingComment = "";
}

void
QtShanoirUploadWidget::initConnections()
{
    QObject::connect(uploadPushButton, SIGNAL(clicked()), this, SLOT(upload()));
    QObject::connect(browsePushButton, SIGNAL(clicked()), this, SLOT(browseDataset()));
    QObject::connect(datasetNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(datasetNameChanged(QString)));
    QObject::connect(datasetCommentTextEdit, SIGNAL(textChanged()), this, SLOT(datasetCommentChanged()));
    QObject::connect(processingCommentTextEdit, SIGNAL(textChanged()), this, SLOT(processingCommentChanged()));
    QObject::connect(addDatasetButton, SIGNAL(clicked()), this, SLOT(addDataset()));
    QObject::connect(processingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(processingChanged(int)));
}

void
QtShanoirUploadWidget::print()
{
    qDebug() << "Upload state : ";
    qDebug() << "      Dataset Id : " << d->datasetId;
    qDebug() << "      Processing Id : " << d->processingId;
    qDebug() << "      Dataset file : " << d->datasetPath;
    qDebug() << "      Dataset name : " << d->datasetName;
    qDebug() << "      Dataset comment : " << d->datasetComment;
    qDebug() << "      Processing comment : " << d->processingComment;
}

void
QtShanoirUploadWidget::upload()
{
    this->print();
}

void
QtShanoirUploadWidget::browseDataset()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::home().dirName());
    dialog.setWindowTitle("Open filename");
    dialog.setNameFilter(tr("Images (*.nii *.vtk)"));

    if (dialog.exec()) {
        d->datasetPath = dialog.selectedFiles()[0];
        datasetPathLineEdit->setText(d->datasetPath);
    }
    dialog.close();
}

void
QtShanoirUploadWidget::datasetNameChanged(QString name)
{
    d->datasetName = name;
}

void
QtShanoirUploadWidget::datasetCommentChanged()
{
    d->datasetComment = datasetCommentTextEdit->toPlainText();
}

void
QtShanoirUploadWidget::updateInputDatasetComboBox(QList<int> ids)
{
    datasetListComboBox->clear();
    for (int i = 0; i < ids.size(); i++)
        datasetListComboBox->addItem(QString::number(ids.at(i)));
}

void
QtShanoirUploadWidget::updateProcessingComboBox(QMap<int, QString> map)
{
    processingComboBox->clear();
    for (int i = 0; i < map.size(); i++)
        processingComboBox->insertItem(i, map[i]);
}

void
QtShanoirUploadWidget::addDataset()
{

}

void
QtShanoirUploadWidget::processingChanged(int index)
{
    d->processingId = index;
}

void
QtShanoirUploadWidget::processingCommentChanged()
{
    d->processingComment = processingCommentTextEdit->toPlainText();
}

