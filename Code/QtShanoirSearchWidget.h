/*
 * QtShanoirSearchWidget.h
 *
 *  Created on: May 4 2011
 *      Author: ocommowi
 */

#ifndef _QTSHANOIRSEARCHWIDGET_H_
#define _QTSHANOIRSEARCHWIDGET_H_

#include <QtGui>
#include "ui_qtshanoirsearchwidget.h"

class QtShanoirSearchWidget : public QWidget, private Ui::QtShanoirSearch
{
  Q_OBJECT

public:
  QtShanoirSearchWidget(QWidget * parent = 0);
  void reset();
  
  public slots:
  void studyNameTextChanged(QString text);
  void patientNameTextChanged(QString text);
  void examDateChanged(QString text);
  void datasetNameTextChanged(QString text);
  
private:
  void initConnections();
};

#endif /* QTSHANOIRSEARCHWIDGET_H_ */
