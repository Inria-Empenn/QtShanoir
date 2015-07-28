#include "qtshanoirprogresswidget.h"
#include <QDebug>
QtShanoirProgressWidget::QtShanoirProgressWidget(QWidget *parent): QWidget (parent),ui(new Ui::QtShanoirProgressWidget)
{
        ui->setupUi(this);
}

void QtShanoirProgressWidget::setDatasetName(QString text)
{
    ui->label->setText(text);
}

void QtShanoirProgressWidget::showProgressBar()
{
    ui->progressBar->setVisible(true);
}

void QtShanoirProgressWidget::hideProgressBar()
{
    ui->progressBar->setVisible(false);
}

void QtShanoirProgressWidget::setProgressBarValue(int value)
{
    ui->progressBar->setValue(value);
}

