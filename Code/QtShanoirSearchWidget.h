/*
    The QtShanoir library.
    Copyright (C) 2011  INRIA, Université de Rennes 1

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
  void eventExamDate(int oldpos, int newpos);
  
private:
  void initConnections();
};

#endif /* QTSHANOIRSEARCHWIDGET_H_ */
