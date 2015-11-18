#include <QStandardItemModel>
#include <QTableView>
#include "ProxyModelWithHeaderModels.h"
#include "qtshanoiruploadwidgetcoressfilesprocessdataset.h"
#include <QtGui>
#include <QStyledItemDelegate>

class ItemDelegate : public QStyledItemDelegate
{
public:
    ItemDelegate(QObject *parent = 0): QStyledItemDelegate(parent)
    {
    }

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
    {
        QStyleOptionViewItemV4 viewItemOption(option);

        if (index.column() == 0) {
            const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
            QRect newRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                                QSize(option.decorationSize.width() + 5,option.decorationSize.height()),
                                                QRect(option.rect.x() + textMargin, option.rect.y(),
                                                      option.rect.width() - (2 * textMargin), option.rect.height()));
            viewItemOption.rect = newRect;
        }
        QStyledItemDelegate::paint(painter, viewItemOption, index);
    }

    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                             const QModelIndex &index)
    {
        Q_ASSERT(event);
        Q_ASSERT(model);

        // make sure that the item is checkable
        Qt::ItemFlags flags = model->flags(index);
        if (!(flags & Qt::ItemIsUserCheckable) || !(flags & Qt::ItemIsEnabled))
            return false;
        // make sure that we have a check state
        QVariant value = index.data(Qt::CheckStateRole);
        if (!value.isValid())
            return false;
        // make sure that we have the right event type
        if (event->type() == QEvent::MouseButtonRelease) {
            const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
            QRect checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                                  option.decorationSize,
                                                  QRect(option.rect.x() + (2 * textMargin), option.rect.y(),
                                                        option.rect.width() - (2 * textMargin),
                                                        option.rect.height()));
            if (!checkRect.contains(static_cast<QMouseEvent*>(event)->pos()))
                return false;
        } else if (event->type() == QEvent::KeyPress) {
            if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space&& static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
                return false;
        } else {
            return false;
        }
        Qt::CheckState state = (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked
                                ? Qt::Unchecked : Qt::Checked);
        return model->setData(index, state, Qt::CheckStateRole);
    }
};

QtShanoirUploadWidgetCoressFilesProcessDataset::QtShanoirUploadWidgetCoressFilesProcessDataset(QWidget *parent):QWizardPage(parent),ui (new Ui::QtShanoirUploadWidgetCoressFilesProcessDataset)
{
    ui->setupUi(this);
    setButtonText(QWizard::NextButton,tr("Next >"));
    setButtonText(QWizard::BackButton,tr("< Back"));
    setButtonText(QWizard::CancelButton,tr("Cancel"));

    attachShowStepsWidget(ui->steps);
    showsteps->steps(5);

    //Explain step
    ui->detailsLabel->setText(tr("<b> Step 5 : </b> Match your files with the correct process and Datasets."));

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef QStringList (* CallFunction)();
    CallFunction cf = (CallFunction)library.resolve("getDatasetTypeList");
    if (cf)
    {
        QStringList list = cf();
        if (!list.isEmpty())
        {
            datasetTypeList=list;
        }
    }
    else
        qDebug() << "could not call function";
    datasetTypeSelectedList.clear();
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::attachShowStepsWidget(QtShanoirUploadWidgetShowSteps* widget)
{
    showsteps = widget;
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::updateFilesList(QStringList files)
{
    this->filesList = files;
    buildTable();
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::updateProcessList(QMap<int,QString> process)
{
    this->processList = process;
    buildTable();
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::clearTable()
{
    horizontalHeaderModel.clear();
    verticalHeaderModel.clear();
    dataModel.clear();
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::buildTable()
{
    clearTable();
    rowCount = filesList.size();
    columnCount = processList.size() + datasetTypeList.size();

    ui->filesProcessDatasetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    buildHorizontalHeaderModel(horizontalHeaderModel);
    buildVerticalHeaderModel(verticalHeaderModel);

    proxyModel.setHorizontalHeaderModel(&horizontalHeaderModel);
    proxyModel.setVerticalHeaderModel(&verticalHeaderModel);

    buildDataModel(dataModel);
    proxyModel.setSourceModel(&dataModel);

    HierarchicalHeaderView *horizontalHeaderView = new HierarchicalHeaderView(Qt::Horizontal, ui->filesProcessDatasetTable);
    HierarchicalHeaderView *verticalHeaderView = new HierarchicalHeaderView(Qt::Vertical, ui->filesProcessDatasetTable);
    ui->filesProcessDatasetTable->setHorizontalHeader(horizontalHeaderView);
    ui->filesProcessDatasetTable->setVerticalHeader(verticalHeaderView);

    ui->filesProcessDatasetTable->setModel(&proxyModel);

    //ui->filesProcessDatasetTable->setItemDelegate(new ItemDelegate(ui->filesProcessDatasetTable)); //center checkbox pr la premier olonne seulement

    initConnections();
}


void QtShanoirUploadWidgetCoressFilesProcessDataset::resetClicked()
{
    for(int i = 0; i< rowCount;i++)
        for (int j= 0 ;j<columnCount;j++)
        {
            QStandardItem* cell= dataModel.item(i,j);
            if (cell->checkState() == Qt::Checked)
            {
                cell->setCheckState(Qt::Unchecked);
                dataModel.setItem(i,j,cell);
            }
        }
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::initConnections()
{
    QObject::connect(ui->resetButton,SIGNAL(pressed()),this, SLOT (resetClicked()));
    QObject::connect(&dataModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(columnChanged(QStandardItem*)));
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::columnChanged(QStandardItem* item)
{
   // Detection of selected dataset type selected
    if ((item->column()>= columnCount-datasetTypeList.size()) && (item->column()<columnCount))
    { 
        QString datasetType = datasetTypeList.value(item->column()-processList.size());
        if (item->checkState() == Qt::Checked)
        {
            // uncheck others
            for(int j=columnCount-datasetTypeList.size(); j<columnCount; j++)
            {
                QStandardItem* cell= dataModel.item(item->row(),j);
                if ((j!= item->column()) && (cell->checkState() == Qt::Checked))
                {
                    cell->setCheckState(Qt::Unchecked);
                    dataModel.setItem(item->row(),j,cell);
                    break;
                }
            }
            qDebug()<<datasetTypeList.value(item->column()-processList.size());

            // selected dataset type
            if (!datasetTypeSelectedList.contains(datasetType))
            {
                datasetTypeSelectedList.append(datasetType);
            }
        }
        else
        {
            if (countCheckedCellsInColumn(item->column()) == 0)
            {
                qDebug()<<"occurence"<<countCheckedCellsInColumn(item->column());
                datasetTypeSelectedList.removeAll(datasetType);
            }
        }
        emit callUpdateDatasetTypeSelectedList(datasetTypeSelectedList);
    }
    // Select one process for each file
    else if ((item->column()>=0) && (item->column()<processList.size()))
    {
        if (item->checkState() == Qt::Checked)
        {
            // uncheck others
            for(int j=0;j<processList.size();j++ )
            {
                QStandardItem* cell= dataModel.item(item->row(),j);
                if ((j!= item->column()) && (cell->checkState() == Qt::Checked))
                {
                    cell->setCheckState(Qt::Unchecked);
                    dataModel.setItem(item->row(),j,cell);
                    break;
                }
            }
        }
    }
}

int QtShanoirUploadWidgetCoressFilesProcessDataset::countCheckedCellsInColumn(int column)
{
    int number = 0;
    for (int i=0; i<rowCount;i++)
    {
        QStandardItem* cell= dataModel.item(i,column);
        if (cell && (cell->checkState() == Qt::Checked))
        {
            number ++;
        }
    }
    return number;
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::buildDataModel(QStandardItemModel& model)
{
    for(int i=0;i<rowCount;i++)
    {
        QList<QStandardItem*> l;
        for(int j=0; j<columnCount;j++)
        {
            QStandardItem* cell=new QStandardItem(true);
            cell->setCheckable(true);
            cell->setCheckState(Qt::Unchecked);
            l.push_back(cell);
        }
        model.appendRow(l);
    }
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::buildHorizontalHeaderModel(QStandardItemModel& headerModel)
{
    QStandardItem *Header1 = new QStandardItem(QObject::tr("Process"));
    QStandardItem *Header2 = new QStandardItem(QObject::tr("Dataset type"));

    QList<QStandardItem *> l;
    for(int i=0; i<processList.size();i++)
    {
        l.push_back( new QStandardItem(processList.values().at(i)));
        Header1->appendColumn(l);
        l.clear();
    }

    foreach (QString value, datasetTypeList)
    {
        l.push_back( new QStandardItem(value));
        Header2->appendColumn(l);
        l.clear();
    }

    headerModel.setItem(0, 0, Header1);
    headerModel.setItem(0, 1, Header2);
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::buildVerticalHeaderModel(QStandardItemModel& headerModel)
{
    for(int i=0;i<filesList.size();i++)
    {
        QString header = reduceFilenameToTwoDir(filesList.value(i));
        headerModel.setItem(0, i, new QStandardItem(QObject::tr(header.toStdString().c_str())));
    }
}

QString QtShanoirUploadWidgetCoressFilesProcessDataset::reduceFilenameToTwoDir(QString filename)
{
    QString inter1 = filename.left(filename.lastIndexOf("/"));
    QString inter2 = inter1.left(inter1.lastIndexOf("/"));
    if (inter2.lastIndexOf("/") != -1)
    {
        return filename.right(filename.size()-inter2.lastIndexOf("/"));
    }
     else
        return filename;
}

bool QtShanoirUploadWidgetCoressFilesProcessDataset::validatePage()
{
    if (validationProcessDatasetType())
    {
        for(int i=0; i<filesToUpload.size();i++)
        {
            if (getMatchedProcessId(i) != -1)
                filesToUpload[i].setRefDatasetProcessingId(getMatchedProcessId(i));
            if (getMatchedDatasetClass(i) != "")
                filesToUpload[i].setDatasetClass(getMatchedDatasetClass(i));
        }
        emit callUpdateFilesToUpload(filesToUpload);
    }
    return (validationProcessDatasetType());
}

int QtShanoirUploadWidgetCoressFilesProcessDataset::getMatchedProcessId(int row)
{
    int pos = -1;
    for(int j=0; j<processList.size();j++)
    {
        QStandardItem* cell= dataModel.item(row,j);
        if (cell && (cell->checkState() == Qt::Checked))
        {
            pos =  processList.keys().at(j);
        }
    }
    return pos;
}

QString QtShanoirUploadWidgetCoressFilesProcessDataset::getMatchedDatasetClass(int row)
{
    QString datasetType = "";
    int k=0;
    for(int j= columnCount-datasetTypeList.size(); j<columnCount;j++)
    {
        QStandardItem* cell= dataModel.item(row,j);
        if (cell && (cell->checkState() == Qt::Checked))
        {
            datasetType =  datasetTypeList.value(k);
        }
        k++;
    }
    return datasetType;
}

bool QtShanoirUploadWidgetCoressFilesProcessDataset::validationProcessDatasetType()
{
    bool existProcess = true;
    bool exitDatasetType = true;
    for (int i=0; i<rowCount;i++)
    {
        existProcess = matchExist(i,0,processList.size());
        QString filename = reduceFilenameToTwoDir(filesList.value(i));
        if (!existProcess)
        {
            QString message = QString("Can not find match process for file << %1 >> in row %2.").arg(filename).arg(QString::number(i));
            QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
            break;
        }
        else
        {
            exitDatasetType = matchExist(i,columnCount-datasetTypeList.size(),columnCount);
            if(!exitDatasetType)
            {
                QString message = QString("Can not find match dataset type for file << %1 >> in row %2.").arg(filename).arg(QString::number(i));
                QMessageBox::critical(this,tr("Error Message"),tr(message.toStdString().c_str()),QMessageBox::Ok,0);
                break;
            }
        }
    }
    return (existProcess && exitDatasetType);
}

bool QtShanoirUploadWidgetCoressFilesProcessDataset::matchExist(int row, int start, int end)
{
    bool matchExist = false;
    for (int j=start; j<end;j++)
    {
        QStandardItem* cell= dataModel.item(row,j);
        if (cell && (cell->checkState() == Qt::Checked))
        {
            matchExist =true;
            break;
        }
    }
    return matchExist;
}

void QtShanoirUploadWidgetCoressFilesProcessDataset::updateFilesToUpload(QList<QtShanoirUploadProcessedDatasetAttributesTemp> files)
{
    this->filesToUpload = files;
}
