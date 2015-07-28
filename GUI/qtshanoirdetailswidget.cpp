#include "qtshanoirdetailswidget.h"
#include "qtshanoirstudy.h"

QtShanoirDetailsWidget::QtShanoirDetailsWidget(QWidget *parent) : QWidget(parent),ui (new Ui::QtShanoirDetailsWidget)
{
    ui->setupUi(this);
    qDebug()<<"c'est bon";

}

void QtShanoirDetailsWidget::getStudyDetails(QString studyName)
{
    typedef struct Study
    {
        QString name;
    }Study;

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef struct Study* (* CallFunction)(QString);
    CallFunction cf = (CallFunction)library.resolve("getStudyDetails");
    if (cf)
    {
        struct Study* study = cf(studyName);

        //Clear GridLayout
        while(ui->gridLayout->count())
        {
            QWidget* widget = ui->gridLayout->itemAt(0)->widget();
            if(widget)
            {
                ui->gridLayout->removeWidget(widget);
                delete widget;
            }
        }

        QImage image;
        image.load(":Images/study.64x64.png");
        QLabel* imageLabel = new QLabel();
        imageLabel->setPixmap(QPixmap::fromImage(image));
        QLabel *studyNameLabel = new QLabel("Name :");
        QLabel *studyName = new QLabel(study->name);

        ui->gridLayout->addWidget(imageLabel,0,0);
        ui->gridLayout->addWidget(studyNameLabel,0,1);
        ui->gridLayout->addWidget(studyName,0,2);
        setLayout(ui->gridLayout);
    }
    else
        qDebug() << "could not call function";
}

void QtShanoirDetailsWidget::getSubjectDetails(int idStudy, int idSubject)
{
    typedef struct Subject
    {
        QString name;
        QDate birthDate;
        QChar sexe;
    }Subject;

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef  struct Subject* (* CallFunction)(int,int);
    CallFunction cf = (CallFunction)library.resolve("getSubjectDetails");
    if (cf)
    {
        struct Subject* subject = cf(idStudy,idSubject);

        //Clear GridLayout
        while(ui->gridLayout->count())
        {
            QWidget* widget = ui->gridLayout->itemAt(0)->widget();
            if(widget)
            {
                ui->gridLayout->removeWidget(widget);
                delete widget;
            }
        }

        QImage image;
        image.load(":Images/subject.64x64.png");
        QLabel* labelImage = new QLabel();
        labelImage->setPixmap(QPixmap::fromImage(image));

        QLabel *subjectNameLabel = new QLabel("Name :");
        QLabel *subjectName = new QLabel(subject->name);
        QLabel *subjectBirthLabel = new QLabel("Birth Date :");
        QLabel *subjectBirth = new QLabel(subject->birthDate.toString(Qt::ISODate));
        QLabel *subjectSexeLabel= new QLabel("Sexe :");
        QLabel *subjectSexe = new QLabel(subject->sexe);

        ui->gridLayout->addWidget(labelImage,0,0,3,0);
        ui->gridLayout->setColumnMinimumWidth(0,70);
        ui->gridLayout->addWidget(subjectNameLabel,0,1);
        ui->gridLayout->addWidget(subjectName,0,2);
        ui->gridLayout->addWidget(subjectBirthLabel,1,1);
        ui->gridLayout->addWidget(subjectBirth,1,2);
        ui->gridLayout->addWidget(subjectSexeLabel,2,1);
        ui->gridLayout->addWidget(subjectSexe,2,2);
    }
    else
        qDebug() << "could not call function";
}

void QtShanoirDetailsWidget::getExamDetails(int idStudy, int idSubject, int idExam)
{
    typedef struct Exam
    {
        QString comment;
        QDate date;
    }Exam;

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef  struct Exam* (* CallFunction)(int,int,int);
    CallFunction cf = (CallFunction)library.resolve("getExamDetails");
    if (cf)
    {
        struct Exam* exam = cf(idStudy,idSubject,idExam);

        //Clear GridLayout
        while(ui->gridLayout->count())
        {
            QWidget* widget = ui->gridLayout->itemAt(0)->widget();
            if(widget)
            {
                ui->gridLayout->removeWidget(widget);
                delete widget;
            }
        }

        QImage image;
        image.load(":Images/examination.64x64.png");
        QLabel* labelImage = new QLabel();
        labelImage->setPixmap(QPixmap::fromImage(image));

        QLabel *examNameLabel = new QLabel("Name :");
        QLabel *examName = new QLabel(exam->comment);
        QLabel *examDateLabel = new QLabel("Date :");
        QLabel *examDate = new QLabel(exam->date.toString(Qt::ISODate));

        ui->gridLayout->addWidget(labelImage,0,0,2,0);
        ui->gridLayout->setColumnMinimumWidth(0,70);
        ui->gridLayout->addWidget(examNameLabel,0,1);
        ui->gridLayout->addWidget(examName,0,2);
        ui->gridLayout->addWidget(examDateLabel,1,1);
        ui->gridLayout->addWidget(examDate,1,2);
    }
    else
        qDebug() << "could not call function";
}

void QtShanoirDetailsWidget::getDatasetDetails(int idStudy, int idSubject, int idExam, int idDataset)
{
    typedef struct Dataset
    {
        QString name;
        QDate creationDate;
        QString comment;
        float repetitionTime;
        float flipAngle;
        float echoTime;
    }Dataset;

    QLibrary library("DAO.dll");
    if (!library.load())
            qDebug() << library.errorString();
    else
            qDebug() << "library loaded";
    typedef  struct Dataset* (* CallFunction)(int,int,int,int);
    CallFunction cf = (CallFunction)library.resolve("getDatasetDetails");
    if (cf)
    {
        struct Dataset* dataset = cf(idStudy,idSubject,idExam,idDataset);

        //Clear GridLayout
        while(ui->gridLayout->count())
        {
            QWidget* widget = ui->gridLayout->itemAt(0)->widget();
            if(widget)
            {
                ui->gridLayout->removeWidget(widget);
                delete widget;
            }
        }

        QImage image;
        image.load(":Images/dataset.64x64.png");
        QLabel* labelImage = new QLabel();
        labelImage->setPixmap(QPixmap::fromImage(image));

        QLabel *datasetNameLabel = new QLabel("Name :");
        QLabel *datasetName = new QLabel(dataset->name);
        QLabel *datasetCreationDateLabel = new QLabel("Creation Date :");
        QLabel *datasetCreationDate = new QLabel(dataset->creationDate.toString(Qt::ISODate));
        QLabel *datasetCommentLabel = new QLabel("Comment :");
        QLabel *datasetComment = new QLabel(dataset->comment);
        QLabel *datasetRepetitionTimeLabel = new QLabel("Repetition Time :");
        QLabel *datasetRepetitionTime = new QLabel(QString::number(dataset->repetitionTime));
        QLabel *datasetFlipAngleLabel = new QLabel("Flip Angle :");
        QLabel *datasetFlipAngle = new QLabel(QString::number(dataset->flipAngle));
        QLabel *datasetEchoTimeLabel = new QLabel("Echo Time :");
        QLabel *datasetEchoTime = new QLabel(QString::number(dataset->echoTime));

        ui->gridLayout->addWidget(labelImage,0,0,6,0);
        ui->gridLayout->setColumnMinimumWidth(0,70);
        ui->gridLayout->addWidget(datasetNameLabel,0,1);
        ui->gridLayout->addWidget(datasetName,0,2);
        ui->gridLayout->addWidget(datasetCreationDateLabel,1,1);
        ui->gridLayout->addWidget(datasetCreationDate,1,2);
        ui->gridLayout->addWidget(datasetCommentLabel,2,1);
        ui->gridLayout->addWidget(datasetComment,2,2);
        ui->gridLayout->addWidget(datasetRepetitionTimeLabel,3,1);
        ui->gridLayout->addWidget(datasetRepetitionTime,3,2);
        ui->gridLayout->addWidget(datasetFlipAngleLabel,4,1);
        ui->gridLayout->addWidget(datasetFlipAngle,4,2);
        ui->gridLayout->addWidget(datasetEchoTimeLabel,5,1);
        ui->gridLayout->addWidget(datasetEchoTime,5,2);
    }
    else
        qDebug() << "could not call function";
}
