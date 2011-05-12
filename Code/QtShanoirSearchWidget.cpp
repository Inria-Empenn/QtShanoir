/*
 * QtShanoirSearchWidget.h
 *
 *  Created on: May 4 2011
 *      Author: ocommowi
 */

#include <QtShanoirSearchWidget.h>
#include <QtShanoir.h>

QtShanoirSearchWidget::QtShanoirSearchWidget(QWidget * parent) : QWidget(parent)
{
  setupUi(this);
  this->reset();
  
  this->initConnections();
}

void QtShanoirSearchWidget::initConnections()
{
  QObject::connect(studyName, SIGNAL(textChanged(QString)), this, SLOT(studyNameTextChanged(QString)));
  QObject::connect(patientNameFilter, SIGNAL(textChanged(QString)), this, SLOT(patientNameTextChanged(QString)));
  QObject::connect(examDateFilter, SIGNAL(textChanged(QString)), this, SLOT(examDateChanged(QString)));
  QObject::connect(datasetNameFilter, SIGNAL(textChanged(QString)), this, SLOT(datasetNameTextChanged(QString)));
}

void QtShanoirSearchWidget::studyNameTextChanged(QString text)
{
  QtShanoir::instance()->setStudyNameFilter(text.trimmed());
}

void QtShanoirSearchWidget::patientNameTextChanged(QString text)
{
  QtShanoir::instance()->setPatientNameFilter(text.trimmed());
}

void QtShanoirSearchWidget::examDateChanged(QString text)
{
  if (text != "DD/MM/YYYY")
    QtShanoir::instance()->setDateFilter(text.trimmed());
}

void QtShanoirSearchWidget::datasetNameTextChanged(QString text)
{
  QtShanoir::instance()->setDatasetNameFilter(text.trimmed());
}

void QtShanoirSearchWidget::reset()
{
  studyName->setText("");
  this->studyNameTextChanged("");
  
  patientNameFilter->setText("");
  this->patientNameTextChanged("");
  
  examDateFilter->setText("DD/MM/YYYY");
  this->examDateChanged("");
  
  datasetNameFilter->setText("");
  this->datasetNameTextChanged("");
}
