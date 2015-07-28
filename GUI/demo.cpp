#include "demo.h"

Demo::Demo(QWidget * parent)
{
    setupUi(this);

    attachTreeWidget(treeWidget);
    qDebug()<<"treeWidget";
    attachDetailsWidget(detailsWidget);
    qDebug()<<"detailsWidget";
    attachSearchWidget(searchWidget);
    qDebug()<<"searchWidget";
    attachSettingsWidget(settingsWidget);
    qDebug()<<"settingsWidget";
    attachDownloadWidget(downloadWidget);
    qDebug()<<"downloadWidget";
    attachErrorWidget(errorWidget);
    qDebug()<<"errorWidget";
    error = new QtShanoirErrorWidget();
    uploadIntermediate = new QtShanoirUploadWidgetIntermediate();
    //attachUploadWidget(uploadWidget);
    qDebug()<<"uploadWidget";
    initConnections();
    qDebug()<<"finish";

}

void Demo::initConnections()
{

    findButton->setDefault(true);
    QObject::connect(findButton, SIGNAL(clicked()), search, SLOT(findValidation()));


    QObject::connect(settings, SIGNAL(callServer()), tree, SLOT(buildTree()));  //settings enable build tree and build upload



    QObject::connect(downloadButton, SIGNAL(clicked()), download, SLOT(chooseDir()));
    QObject::connect(uploadButton, SIGNAL(clicked()), uploadIntermediate, SLOT(buildUpload()));

    QObject::connect(search, SIGNAL(startFind(QString,QString,QDate,QString)), tree, SLOT(build(QString,QString,QDate,QString)));
    QObject::connect(tree,SIGNAL(getStudyDetails(QString)),details, SLOT(getStudyDetails(QString)));
    QObject::connect(tree,SIGNAL(getSubjectDetails(int,int)),details, SLOT(getSubjectDetails(int,int)));
    QObject::connect(tree,SIGNAL(getExamDetails(int,int,int)),details, SLOT(getExamDetails(int,int,int)));
    QObject::connect(tree,SIGNAL(getDatasetDetails(int,int,int,int)),details, SLOT(getDatasetDetails(int,int,int,int)));
    QObject::connect(tree,SIGNAL(getProcessDetails(int,int,int,int,int)),details, SLOT(getProcessDetails(int,int,int,int,int)));
    QObject::connect(tree,SIGNAL(getProcessedDatasetDetails(int,int,int,int,int,int)),details, SLOT(getProcessedDatasetDetails(int,int,int,int,int,int)));
    QObject::connect(tree, SIGNAL(callUpdateSelectedIds(QMap<int,QString>)), download, SLOT (updateSelectedIds(QMap<int,QString>)));
    QObject::connect(settings, SIGNAL(queryFailed(QString)), error, SLOT (printMessage(QString)));
    QObject::connect(tree, SIGNAL(queryFailed(QString)), error, SLOT (printMessage(QString)));



}

void Demo::attachTreeWidget(QtShanoirTreeWidget * widget)
{
    tree = widget;
    if (tree)
    {
//        QObject::connect(tree, SIGNAL(mrExamQuery(QString)), this, SLOT(findExam(QString)));
//        QObject::connect(tree, SIGNAL(datasetQuery(QString,QString)), this,SLOT(findDataset(QString,QString)));
//        QObject::connect(tree, SIGNAL(processingQuery(QString)), this, SLOT(findProcessing(QString)));
//        QObject::connect(tree, SIGNAL(id(int)), this, SLOT(currentId(int)));
//        QObject::connect(tree, SIGNAL(selected(QMap<int,QString>)), this, SLOT(updateSelected(QMap<int,QString>)));
//        QObject::connect(tree, SIGNAL(filename(QString)), this, SLOT (setDownloadFilename(QString)));
    }
}

void Demo::attachSearchWidget(QtShanoirSearchWidget * widget)
{
    search = widget;
    if (search)
    {

    }
}

void Demo::attachSettingsWidget(QtShanoirSettingsWidget * widget)
{
    settings = widget;
    if (settings)
    {

    }
}

void Demo::attachDetailsWidget(QtShanoirDetailsWidget * widget)
{
    details = widget;
    if (details)
    {

    }

}

void Demo::attachDownloadWidget(QtShanoirDownloadWidget * widget)
{
    download = widget;
    if (download)
    {

    }

}

void Demo::attachErrorWidget(QtShanoirErrorWidget * widget)
{
    error = widget;
    //if (error);

}



void Demo::clearTree()
{
    //shanoirmain.clearSelectedIds();
    //if (tree)
        //tree->treeWidget->clear();
}











void Demo::setDownloadMetadata(int state)
{
	//bool status = state == Qt::Checked;
    //download.setDownloadMetadata( status );
}
