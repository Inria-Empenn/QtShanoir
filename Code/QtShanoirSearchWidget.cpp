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
  
  QRegExp regexp("([0-9]{,2})/([0-9]{,2})/([0-9]{,4})");
  QRegExpValidator * validator = new QRegExpValidator(regexp, this);
  examDateFilter->setValidator(validator);

  examDateFilter->setStyleSheet("color: rgb(138, 138, 138);");

  QFont font = examDateFilter->font();
  font.setItalic(true);
  examDateFilter->setFont(font);

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
  QFont font = examDateFilter->font();
  if(text.isEmpty())
  {
     font.setItalic(true);
     examDateFilter->setFont(font);
     examDateFilter->setStyleSheet("color: rgb(138, 138, 138);");
     examDateFilter->blockSignals(true);
     examDateFilter->setText("DD/MM/YYYY");
     examDateFilter->blockSignals(false);
     QtShanoir::instance()->setDateFilter("");
  }

  if (examDateFilter->text().startsWith("D") && (examDateFilter->text().size() < 10))
  {
    font.setItalic(false);
    examDateFilter->setFont(font);
    examDateFilter->setStyleSheet("color: rgb(0, 0, 0);");
    examDateFilter->blockSignals(true);
    examDateFilter->setText("");
    examDateFilter->blockSignals(false);
  }

  if (examDateFilter->text() != "DD/MM/YYYY")
  {
    font.setItalic(false);
    examDateFilter->setFont(font);
    examDateFilter->setStyleSheet("color: rgb(0, 0, 0);");
    QtShanoir::instance()->setDateFilter(text.trimmed());
  }
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
