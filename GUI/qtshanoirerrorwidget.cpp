#include "qtshanoirerrorwidget.h"


QtShanoirErrorWidget::QtShanoirErrorWidget(QWidget *parent) : QWidget(parent),ui (new Ui::QtShanoirErrorWidget)
{
    ui->setupUi(this);
    //ui->label->setStyleSheet("QLabel {color : red;}");
}



void QtShanoirErrorWidget::printMessage(QString text)
{
    qDebug()<<"message"<<text;

    //QLabel* label = new QLabel(text,this);
    ui->label->clear();
    ui->label->setText(text);
    ui->label->setStyleSheet("QLabel {color : red;}");
    ui->label->setVisible(true);
    //ui->lineEdit->setStyleSheet("QLabel {color : red;}");
//    ui->label->setVisible(true);
}
