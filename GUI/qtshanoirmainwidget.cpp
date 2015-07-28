#include "qtshanoirmainwidget.h"


void QtShanoirMainWidget::initConnections()
{
    //if (tree)
        //shanoirmain = new QtShanoirMain();
        //qDebug()<<"C'est bon!!";
        QObject::connect(this, SIGNAL(startDownload()), this, SLOT(callDownload()));
        QObject::connect(this, SIGNAL(startUpload()), this, SLOT(upload()));
}

void QtShanoirMainWidget::attachTreeWidget(QtShanoirTreeWidget * widget)
{
    tree = widget;
    if (tree)
    {
        QObject::connect(tree, SIGNAL(mrExamQuery(QString)), this, SLOT(findExam(QString)));
        QObject::connect(tree, SIGNAL(datasetQuery(QString,QString)), this,SLOT(findDataset(QString,QString)));
        QObject::connect(tree, SIGNAL(processingQuery(QString)), this, SLOT(findProcessing(QString)));
        QObject::connect(tree, SIGNAL(id(int)), this, SLOT(currentId(int)));
        QObject::connect(tree, SIGNAL(selected(QMap<int,QString>)), this, SLOT(updateSelected(QMap<int,QString>)));
        QObject::connect(tree, SIGNAL(filename(QString)), this, SLOT (setDownloadFilename(QString)));
    }
}

void QtShanoirMainWidget::attachProgressWidget(QtShanoirProgressWidget * widget)
{
    qDebug()<<"I'm in ttachProgressWidget!!";
	progress = 0;
	bool test = progress == 0;
	emit progressHidden();
	qDebug()<<test;
	progress = widget;
	 test = progress == 0;
	qDebug()<<test;
    
}

void QtShanoirMainWidget::attachUploadWidget(QtShanoirUploadWidget * widget)
{
    upload = widget;
    if (upload && tree )
    {
        QObject::connect(tree, SIGNAL(selected(QMap<int,QString>)), upload, SLOT(updateInputDataset(QMap<int,QString>)));
        QObject::connect(tree, SIGNAL(studyMap(QMap<int,QString>)), upload, SLOT (updateStudyComboBox(QMap<int,QString>)));
        QObject::connect(this, SIGNAL(processingMap(QMap<int,QString>)), upload, SLOT(updateProcessingComboBox(QMap<int,QString>)));
        QObject::connect(upload, SIGNAL(uploadData(QMultiMap<QString,QString>)), this, SLOT(receiveUploadData(QMultiMap<QString,QString>)));
    }
}

void QtShanoirMainWidget::clearTree()
{
    shanoirmain.clearSelectedIds();
    //if (tree)
        //tree->treeWidget->clear();
}

void QtShanoirMainWidget::download()
{
    //if ((shanoirmain.selectedIds.size() != 0 ) || !downloadFileName.isEmpty())
    //{
        QFileDialog * dialog = new QFileDialog (tree);
        dialog->setFileMode(QFileDialog::Directory );
        dialog->setOption(QFileDialog::ShowDirsOnly, true);
        dialog->setDirectory(QDir::home().dirName());
        dialog->setWindowTitle ("Choose datasets download directory");
        QString directory;
        if (dialog->exec())
        {
            directory = dialog->selectedFiles() [0];
        }
        dialog->close();
        if (!directory.isEmpty()) // A file has been chosen
        {
            //download.setDownloadDir(directory);
            emit startDownload();
        }
        delete dialog;
    //}
}

void QtShanoirMainWidget::callDownload()
{
    qDebug() << "Start Download";
//    if (progress)
//    {
//        progress->download->setValue ( 0 );
//        progress->download->show();
//        emit progress->progressShown();
//    }
//    for (int i = 0; i < shanoirmain.selectedIds.size(); i++)
//    {
//        d->curId = d->selectedIds.at ( i );
//        this->downloadDataset (QString::number (d->curId));
//        if (d->progress)
//            d->progress->download->setValue ((int)(100.00*(i+1)/d->selectedIds.size()));
//    }
//    if (d->progress)
//    {
//        d->progress->download->hide();
//        emit progressHidden();
//    }
    qDebug() << "Download finished";
}

void QtShanoirMainWidget::updateSelected(QMap<int,QString> list)
{
	//shanoirmain.setSelectedIds(list.key());
}

void QtShanoirMainWidget::receiveUploadData(QMultiMap<QString, QString> mmap)
{
//    d->dataToUpload = mmap;
//    emit startUpload();
}

void QtShanoirMainWidget::find()
{
    this->clearTree();
    qDebug()<<"I'm here find";
    //shanoirmain.populate();
}

void QtShanoirMainWidget::findExam(QString)
{

}

void QtShanoirMainWidget::findDataset(QString, QString)
{

}

void QtShanoirMainWidget::findProcessing(QString datasetId)
{

}

void QtShanoirMainWidget::currentId(int id)
{
    shanoirmain.setCurrentId(id);
}

void QtShanoirMainWidget::setDownloadMetadata(int state)
{
	//bool status = state == Qt::Checked;
    //download.setDownloadMetadata( status );
}
