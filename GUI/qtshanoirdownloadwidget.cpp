#include "qtshanoirdownloadwidget.h"

QtShanoirDownloadWidget::QtShanoirDownloadWidget(QWidget *parent) : QWidget(parent),ui (new Ui::QtShanoirDownloadWidget)
{
    ui->setupUi(this);
    hideWidget();
    initConnections();

}

void QtShanoirDownloadWidget::initConnections()
{
    QObject::connect(this, SIGNAL(callDownload(QString)), this, SLOT(startDownload(QString)));
    QObject::connect(this, SIGNAL(callBuildTableDownload()), this, SLOT(buildTableDownload()));
}

void QtShanoirDownloadWidget::chooseDir()
{
    if (selectedIds.size() != 0)
    {
        QFileDialog * dialog = new QFileDialog();
        dialog->setFileMode(QFileDialog::Directory);
        dialog->setOption(QFileDialog::ShowDirsOnly, true);
        dialog->setDirectory(QDir::home().dirName());
        dialog->setWindowTitle ("Choose download directory");
        QString directory;
        if (dialog->exec())
        {
            directory = dialog->selectedFiles() [0];
        }
        dialog->close();
        if (!directory.isEmpty()) // A file has been chosen
        {
            emit callDownload(directory);
        }
        delete dialog;
    }
    else
        qDebug()<<"no Dataset selected";
}

void QtShanoirDownloadWidget::buildTableDownload()
{
    ui->tableWidget->setVisible(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headerLabels;
    headerLabels << "File name" << "Actions";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();

    int row = ui->tableWidget->rowCount();;
    QMap<int, QString>::Iterator iterator;
    for(iterator = selectedIds.begin(); iterator != selectedIds.end(); ++iterator)
    {
        qDebug()<<"key"<<iterator.key();
        qDebug()<<"row"<<row;
        mappingTable.insert(iterator.key(),row);


        row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QLineEdit* text = new QLineEdit();
        text->setText(iterator.value());
        text->setReadOnly(1);
        ui->tableWidget->setCellWidget(row, 0, text);


        QPushButton* removeButton = new QPushButton();
        removeButton->setIcon(QIcon(":Images/delete.16x16.png"));

        QSignalMapper* ButtonSignalMapper = new QSignalMapper( this );;
        ButtonSignalMapper->setMapping(removeButton,iterator.key());

        connect(removeButton, SIGNAL(clicked()), ButtonSignalMapper, SLOT(map()));

        connect(ButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(removeDatasetFromSelectedIds(int)));
        ui->tableWidget->setCellWidget(row,1,removeButton);

        row = ui->tableWidget->rowCount();
        ui->tableWidget->resizeColumnToContents(1);
        ui->tableWidget->resizeRowsToContents();

    }
}

void QtShanoirDownloadWidget::startDownload(QString directory)
{
    qDebug() << "Start Download";
    emit callBuildTableDownload();
    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef void (* CallFunction)(QString,QString);
    CallFunction cf = (CallFunction)library.resolve("downloadFile");
    if (cf)
    {
        qDebug()<<"size"<<selectedIds.size();
        for (int i=0; i<selectedIds.size(); i++)
        {

            QMap<int, int>::Iterator iterator = mappingTable.find(selectedIds.keys().at(i));

            cf(QString::number(selectedIds.keys().at(i)),directory);
            ui->progressBar->setVisible(true);
            ui->progressBar->setValue(( int ) ( 100.00 * ( i + 1 ) / selectedIds.size() ) );
            ui->tableWidget->removeCellWidget(iterator.value(), 1);
            ui->tableWidget->setItem(iterator.value(), 1, new QTableWidgetItem("finished"));
            ui->tableWidget->resizeColumnToContents(1);

            qDebug()<<"rowint"<<iterator.value();

            //(QtShanoirProgressWidget*)(ui->tableWidget->item(0,0))->setProgressBarValue(50);
           // modifyProgressBar((QtShanoirProgressWidget*)ui->tableWidget->item(0,0),50);







            //ajouter test

        }
    }
    else
        qDebug() << "could not call function";


//        if (d->progress)
//            d->progress->download->setValue ((int)(100.00*(i+1)/d->selectedIds.size()));

//    if (progress)
//    {
//        progress->download->setValue ( 0 );
//        progress->download->show();
//        emit progress->progressShown();
//    }

//    if (d->progress)
//    {
//        d->progress->download->hide();
//        emit progressHidden();
//    }
    qDebug() << "Download finished";
}


void QtShanoirDownloadWidget::updateSelectedIds (QMap<int, QString> listId )
{
    qDebug() << "updateSelectedIds";
    this->selectedIds = listId;
}

void QtShanoirDownloadWidget::removeDatasetFromSelectedIds(int datasetId)
{
    QMap<int, QString>::Iterator iterator;
    for(iterator = selectedIds.begin(); iterator != selectedIds.end(); ++iterator)
    {
        if(iterator.key() == datasetId)
        {
            iterator = selectedIds.erase(iterator);
            mappingTable.remove(iterator.key());
        }
    }
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void QtShanoirDownloadWidget::modifyRow(int row)
{

    //ui->tableWidget->item(0,0);
    qDebug()<<"nooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";

    //item->showProgressBar();
    //item->setProgressBarValue(value);
}



//void QtShanoirDownloadWidget::disableRemoveButton(QTableWidgetItem * item)
//{

//    ui->tableWidget->item(0,0);
//    qDebug()<<"nooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
//    qDebug()<<"value"<<value;
//    item->showProgressBar();
//    item->setProgressBarValue(value);
//}

void QtShanoirDownloadWidget::hideWidget()
{
    ui->tableWidget->setVisible(false);
    ui->label->setVisible(false);
    ui->progressBar->setVisible(false);
}

void QtShanoirDownloadWidget::showWidget()
{
    ui->tableWidget->setVisible(true);
    ui->label->setVisible(true);
    ui->progressBar->setVisible(true);
}
