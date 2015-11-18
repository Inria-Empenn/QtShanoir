#include "qtshanoiruploadwidgetdragfiles.h"
#include <QMessageBox>

QtShanoirUploadWidgetDragFiles::QtShanoirUploadWidgetDragFiles(QWidget *parent):QWizardPage(parent),ui (new Ui::QtShanoirUploadWidgetDragFiles)

{
    ui->setupUi(this);
    setButtonText(QWizard::NextButton,tr("Next >"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));

    attachShowStepsWidget(ui->steps);
    showsteps->steps(1);

    //Explain step
    ui->detailsLabel->setText(tr("<b> Step 1 : </b> Select your study and add the files to upload"));

    //Study combo Box
    ui->selectStudyLabel->setText(tr("Select Study : <font color='red'>*</font>"));
    fillComboBox();


    //Files table
    ui->listFilesLabel->setText(tr("Files to upload : <font color='red'>*</font>"));
    QStringList labels;
    labels << tr("Name") << tr("Actions");
    ui->filesTable->setColumnCount(2);
    ui->filesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->filesTable->setHorizontalHeaderLabels(labels);
    ui->filesTable->horizontalHeader()->setStretchLastSection(true);
    ui->filesTable->setRowCount(0);
    setAcceptDrops(true);

    initConnections();
}
// Accept all actions, but deal with them separately later.

void QtShanoirUploadWidgetDragFiles::initConnections()
{
    QObject::connect(ui->add,SIGNAL(pressed()),this, SLOT (on_add_clicked()));
    QObject::connect(ui->clearAll,SIGNAL(pressed()),this, SLOT (clearAll()));
    QObject::connect(ui->selectStudyComboBox,SIGNAL(currentIndexChanged(QString)),this, SLOT (toCallSelectStudy(QString)));

}

void QtShanoirUploadWidgetDragFiles::deleteClicked(int row)
{
    QString filename = ui->filesTable->item(row,0)->text();
    filesList.removeAll(filename);
    emit callUpdateFilesList(filesList);
    ui->filesTable->removeRow(row);



}

void QtShanoirUploadWidgetDragFiles::toCallSelectStudy(QString study)
{
    this->studySelected = study;
    emit callSelectStudy(studySelected);
}

void QtShanoirUploadWidgetDragFiles::clearAll()
{
    filesList.clear();
    emit callUpdateFilesList(filesList);
    ui->filesTable->clearContents();
    ui->filesTable->setRowCount(0);
}

void QtShanoirUploadWidgetDragFiles::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
}

void QtShanoirUploadWidgetDragFiles::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void QtShanoirUploadWidgetDragFiles::dragMoveEvent(QDragMoveEvent* event)
{
    event->accept();
}

void QtShanoirUploadWidgetDragFiles::dropEvent(QDropEvent* event)
{
    QString nombreArch;
    QList<QUrl> urls;
    urls = event->mimeData()->urls();
    QFileInfo extension;
    QList<QUrl>::Iterator i;
    for (i = urls.begin();i!=urls.end();++i)
    {
        extension = (QString (urls.first().toLocalFile()) );
        if ((extension.suffix()== "nii")|| (extension.suffix()== "nii.gz")||(extension.suffix()== "vtk"))
        {
            qDebug()<<"ok";
            //qt5 change to i->fileName();
            nombreArch = i->path();
            addRow(nombreArch);
        }
    }
}

void QtShanoirUploadWidgetDragFiles::on_add_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setDirectory(QDir::home().dirName());
    dialog.setWindowTitle(tr("Open filename"));
    dialog.setNameFilter(tr("Images (*.nii *.nii.gz *.vtk)"));
    QStringList	 files;
    if (dialog.exec())
    {
         files = dialog.selectedFiles();
    }
    dialog.close();
    QString path;
    for (int i=0; i<files.size();i++)
    {
        path = files.value(i);
        addRow(path);

    }
}

void QtShanoirUploadWidgetDragFiles::addRow(QString& file)
{
    if (!filesList.contains(file))
    {
        filesList.append(file);
        isComplete();
        emit callUpdateFilesList(filesList);
        qDebug()<<"listSize"<<filesList.size();
        int row = ui->filesTable->rowCount();
        ui->filesTable->insertRow(row);
        ui->filesTable->setItem(row, 0, new QTableWidgetItem(file));
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setIcon(QIcon(":Images/delete.16x16.png"));

        QSignalMapper* ButtonSignalMapper = new QSignalMapper(this);
        ButtonSignalMapper->setMapping(deleteButton,row);
        QObject::connect(deleteButton, SIGNAL(clicked()), ButtonSignalMapper, SLOT(map()));
        QObject::connect(ButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(deleteClicked(int)));

        ui->filesTable->setCellWidget(row,1,deleteButton);

        ui->filesTable->resizeColumnToContents(0);
    }
    else
        QMessageBox::information(this, tr("Information message"), tr("File already exists."), QMessageBox::Ok, 0);
}

void QtShanoirUploadWidgetDragFiles::attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* widget)
{
    showsteps = widget;
}

bool QtShanoirUploadWidgetDragFiles::validatePage()
{
    if (studySelected == "" && filesList.isEmpty())
        QMessageBox::critical(this,tr("Error Message"),tr("You should select a study and at least one file to upload."),QMessageBox::Ok,0);
    else if (filesList.isEmpty())
        QMessageBox::critical(this,tr("Error Message"),tr("You should select at least one file to upload."),QMessageBox::Ok,0);
    else if (studySelected == "")
        QMessageBox::critical(this,tr("Error Message"),tr("You should select a study."),QMessageBox::Ok,0);

    // save information
    if (studySelected != "" && !filesList.isEmpty())
    {
        filesToUpload.clear();
        QList<QtShanoirUploadProcessedDatasetAttributesTemp> list;
        for (int i=0; i<filesList.size();i++)
        {
            QtShanoirUploadProcessedDatasetAttributesTemp processedDatasetFile;
            QList<int> studyId = studyList.keys(studySelected);
            processedDatasetFile.setStudyId(studyId.first());
            processedDatasetFile.setFilename(filesList[i]);
            filesToUpload.append(processedDatasetFile);
        }

        emit callUpdateFilesToUpload(filesToUpload);
    }
    return (!filesList.isEmpty()&&(studySelected != ""));
}


void QtShanoirUploadWidgetDragFiles::fillComboBox()
{
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QMap<int,QString> (* CallFunction)(QString);
    CallFunction cf = (CallFunction)library.resolve("findStudyList");
    if (cf)
    {
        studyList = cf("");
        if (!studyList.isEmpty())
        {
            ui->selectStudyComboBox->insertItem(0,"");
            for (int i=0; i<studyList.size();i++)
                ui->selectStudyComboBox->insertItem(i+1,studyList.values().at(i));
        }

    }
    else
        qDebug() << "could not call function";
}
