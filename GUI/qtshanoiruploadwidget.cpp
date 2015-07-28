#include "qtshanoiruploadwidget.h"

QtShanoirUploadWidget::QtShanoirUploadWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    //processingDatatype << "" << "MrDataset" << "MrSpectroscopyDataset" << "CalibrationDataset" << "EegDataset" << "MegDataset" << "MeshDataset" << "ParameterQuantificationDataset" << "PetDataset"
                //<< "RegistrationDataset" << "SpectDataset" << "StatisticalDataset" << "TemplateDataset" << "SegmentationDataset" << "CtDataset";
   // for (int i = 0; i < processingDatatype.size(); i++)
        //resultTypeComboBox->insertItem(i, processingDatatype.at(i));
    //data = new QtShanoirUpload();
    //inputDataTreeWidget->setColumnWidth(0, 40);
    initConnections();
}

void QtShanoirUploadWidget::initConnections()
{
    QObject::connect(uploadPushButton, SIGNAL(clicked()), this, SLOT(upload()));
    QObject::connect(browsePushButton, SIGNAL(clicked()), this, SLOT(browseDataset()));
    QObject::connect(datasetNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(datasetNameChanged(QString)));
    QObject::connect(datasetCommentTextEdit, SIGNAL(textChanged()), this, SLOT(datasetCommentChanged()));
    QObject::connect(processingCommentTextEdit, SIGNAL(textChanged()), this, SLOT(processingCommentChanged()));
    QObject::connect(processingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(processingChanged(int)));
    QObject::connect(studyComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(studyIdChanged(int)));
    QObject::connect(resultTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resultdatasetTypeChanged(int)));
}

void QtShanoirUploadWidget::updateInputDataset(QMap<int, QString> )
{
    /* data.inputDatasetList.clear();
    data.inputDatasetList = map.keys();
    inputDataTreeWidget->clear();
    QTreeWidgetItem *root = inputDataTreeWidget->invisibleRootItem();
    for (int i = 0; i < map.keys().size(); i++)
    {
        QTreeWidgetItem* input = new QTreeWidgetItem();
        root->addChild(input);
        input->setText(0, QString::number(map.keys().at(i)));
        input->setText(1, map[map.keys().at(i)]);
    } */
}

void QtShanoirUploadWidget::updateProcessingComboBox(QMap<int, QString> map )
{
    processingComboBox->clear();
    for (int i = 0; i < map.size(); i++)
        processingComboBox->insertItem(i, map[i]);
}

void QtShanoirUploadWidget::updateStudyComboBox(QMap<int,QString> map)
{
    studyComboBox->clear();
    for (int i = 0; i < map.size(); i++)
        studyComboBox->insertItem(i, map[i]);
}

void QtShanoirUploadWidget::browseDataset()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::home().dirName());
    dialog.setWindowTitle(tr("Open filename"));
    dialog.setNameFilter(tr("Images (*.nii *.nii.gz *.vtk)"));
    if (dialog.exec())
    {
        //data.setDatasetPath(dialog.selectedFiles()[0]);
        //datasetPathLineEdit->setText(d->datasetPath);
    }
    dialog.close();
}

void QtShanoirUploadWidget::datasetNameChanged(QString name)
{
    //data.setDatasetName(name);
}

void QtShanoirUploadWidget::datasetCommentChanged()
{
    //data.setDatasetComment(datasetCommentTextEdit->toPlainText());
}

void QtShanoirUploadWidget::processingChanged(int index)
{
    //data.setProcessingId(index);
}

void QtShanoirUploadWidget::studyIdChanged(int index)
{
    //data.setStudyId(index);
}

void QtShanoirUploadWidget::processingCommentChanged()
{
    //data.setProcessingComment(processingCommentTextEdit->toPlainText());
}

void QtShanoirUploadWidget::resultdatasetTypeChanged(int index)
{
    //data.setResultDatasetType(resultTypeComboBox->currentText());
}

void QtShanoirUploadWidget::upload() // a tester ( faire des tests sur les champs!!)
{
    /*data.uploadData.clear();
    data.uploadData.insert("datasetType", data.getResultDatasetType());
    data.uploadData.insert("datasetName", data.getDatasetName());
    data.uploadData.insert("datasetPath", data.getDatasetPath());
    data.uploadData.insert("datasetComment", data.getDatasetComment());
    data.uploadData.insert("processingId", QString::number(data.getProcessingId()));
    data.uploadData.insert("studyId", QString::number(data.getStudyId()));
    data.uploadData.insert("processingComment", data.getProcessingComment());
    for (int i = 0; i < data.inputDatasetList.size(); i++)
        data.uploadData.insert("inputDatasets", QString::number(data.inputDatasetList.at(i)));
    if (!(data.uploadData.values("inputDatasets").isEmpty() ||
          data.uploadData.value("datasetName").isEmpty() ||
          data.uploadData.value("datasetPath").isEmpty() ||
          data.uploadData.value("datasetType").isEmpty() ||
          ((data.uploadData.value("studyId").toInt()) == 0) ||
          ((data.uploadData.value("processingId").toInt()) == 0)))
        emit uploadData(data.uploadData);*/
}
