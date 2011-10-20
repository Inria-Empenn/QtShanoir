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

#ifndef QTSHANOIRSETTINGSWIDGET_H_
#define QTSHANOIRSETTINGSWIDGET_H_

#include <QtGui>
#include "ui_qtshanoirsettingswidget.h"

class QtShanoirSettingsWidget : public QWidget, private Ui::QtShanoirConfig
{
    Q_OBJECT
    public:
        QtShanoirSettingsWidget(QWidget * parent = 0);

    public slots:
        void
        loginTextChanged(QString text);
        void
        passwordTextChanged(QString text);
        void
        hostTextChanged(QString text);
        void
        portValueChanged(int value);
        void
        save();

    private:
        void
        initConnections();
};

#endif /* QTSHANOIRSETTINGSWIDGET_H_ */
