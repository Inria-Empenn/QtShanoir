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
        int processingId;
        int studyId;
        QString datasetName;
        QString datasetPath;
        QString resultDatasetType;
        QStringList processingDatatype;
        QString datasetComment;
        QString processingComment;
        QList<int> inputDatasetList;
        QMultiMap<QString, QString> uploadData;

};

QtShanoirUploadWidget::QtShanoirUploadWidget(QWidget * parent) :
    d(new QtShanoirUploadWidgetPrivate)
{
    setupUi(this);
    d->processingDatatype << "" << "MrDataset" << "MrSpectroscopyDataset" << "CalibrationDataset" << "EegDataset" << "MegDataset" << "MeshDataset" << "ParameterQuantificationDataset" << "PetDataset"
            << "RegistrationDataset" << "SpectDataset" << "StatisticalDataset" << "TemplateDataset" << "SegmentationDataset" << "CtDataset";
    for (int i = 0; i < d->processingDatatype.size(); i++)
        resultTypeComboBox->insertItem(i, d->processingDatatype.at(i));
    d->processingId = 0;
    d->studyId = 0;
    d->datasetName = "";
    d->datasetPath = "";
    d->datasetComment = "";
    d->processingComment = "";
    d->resultDatasetType = "";

    inputDataTreeWidget->setColumnWidth(0, 40);

    initConnections();
}

void
QtShanoirUploadWidget::initConnections()
{
    QObject::connect(uploadPushButton, SIGNAL(clicked()), this, SLOT(upload()));
    QObject::connect(browsePushButton, SIGNAL(clicked()), this, SLOT(browseDataset()));
    QObject::connect(datasetNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(datasetNameChanged(QString)));
    QObject::connect(datasetCommentTextEdit, SIGNAL(textChanged()), this, SLOT(datasetCommentChanged()));
    QObject::connect(processingCommentTextEdit, SIGNAL(textChanged()), this, SLOT(processingCommentChanged()));
    QObject::connect(processingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(processingChanged(int)));
    QObject::connect(studyComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(studyChanged(int)));
    QObject::connect(resultTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(datasetTypeChanged(int)));
}

void
QtShanoirUploadWidget::print()
{
    qDebug() << "Upload state : ";
    qDebug() << "      Processing Id : " << d->processingId;
    qDebug() << "      Dataset file : " << d->datasetPath;
    qDebug() << "      Dataset name : " << d->datasetName;
    qDebug() << "      Dataset comment : " << d->datasetComment;
    qDebug() << "      Processing comment : " << d->processingComment;
}

void
QtShanoirUploadWidget::upload()
{
    //    this->print();
    d->uploadData.clear();
    d->uploadData.insert("datasetType", d->resultDatasetType);
    d->uploadData.insert("datasetName", d->datasetName);
    d->uploadData.insert("datasetPath", d->datasetPath);
    d->uploadData.insert("datasetComment", d->datasetComment);
    d->uploadData.insert("processingId", QString::number(d->processingId));
    d->uploadData.insert("studyId", QString::number(d->studyId));
    d->uploadData.insert("processingComment", d->processingComment);
    for (int i = 0; i < d->inputDatasetList.size(); i++)
        d->uploadData.insert("inputDatasets", QString::number(d->inputDatasetList.at(i)));
    
    if (!(d->uploadData.values("inputDatasets").isEmpty() ||
            d->uploadData.value("datasetName").isEmpty() ||
            d->uploadData.value("datasetPath").isEmpty() ||
            d->uploadData.value("datasetType").isEmpty() ||
            ((d->uploadData.value("studyId").toInt()) == 0) ||
            ((d->uploadData.value("processingId").toInt()) == 0)))
        emit uploadData(d->uploadData);
}

void
QtShanoirUploadWidget::browseDataset()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::home().dirName());
    dialog.setWindowTitle("Open filename");
    dialog.setNameFilter(tr("Images (*.nii *.nii.gz *.vtk)"));

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
QtShanoirUploadWidget::updateInputDataset(QMap<int, QString> map)
{
    d->inputDatasetList.clear();
    d->inputDatasetList = map.keys();
    inputDataTreeWidget->clear();
    QTreeWidgetItem *root = inputDataTreeWidget->invisibleRootItem();
    for (int i = 0; i < map.keys().size(); i++) {
        QTreeWidgetItem* input = new QTreeWidgetItem();
        root->addChild(input);
        input->setText(0, QString::number(map.keys().at(i)));
        input->setText(1, map[map.keys().at(i)]);
    }
}

void
QtShanoirUploadWidget::updateProcessingComboBox(QMap<int, QString> map)
{
    processingComboBox->clear();
    for (int i = 0; i < map.size(); i++)
        processingComboBox->insertItem(i, map[i]);
}

void
QtShanoirUploadWidget::updateStudyComboBox(QMap<int, QString> map)
{
    studyComboBox->clear();
    for (int i = 0; i < map.size(); i++)
        studyComboBox->insertItem(i, map[i]);
}

void
QtShanoirUploadWidget::datasetTypeChanged(int index)
{
    d->resultDatasetType = resultTypeComboBox->currentText();
}

void
QtShanoirUploadWidget::processingChanged(int index)
{
    d->processingId = index;
}

void
QtShanoirUploadWidget::studyChanged(int index)
{
    d->studyId = index;
}

void
QtShanoirUploadWidget::processingCommentChanged()
{
    d->processingComment = processingCommentTextEdit->toPlainText();
}

