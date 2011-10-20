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

#include <QtShanoirSettingsWidget.h>
#include <QtShanoirSettings.h>

QtShanoirSettingsWidget::QtShanoirSettingsWidget(QWidget * parent) :
    QWidget(parent)
{
    setupUi(this);
    loginEdit->setText(QtShanoirSettings::Instance()->login());
    passwordEdit->setText(QtShanoirSettings::Instance()->password());
    hostEdit->setText(QtShanoirSettings::Instance()->host());
    portSpinBox->setValue(QtShanoirSettings::Instance()->port().toInt());

    this->initConnections();
}

void
QtShanoirSettingsWidget::initConnections()
{
    QObject::connect(loginEdit, SIGNAL(textChanged(QString)), this, SLOT(loginTextChanged(QString)));
    QObject::connect(passwordEdit, SIGNAL(textChanged(QString)), this, SLOT(passwordTextChanged(QString)));
    QObject::connect(hostEdit, SIGNAL(textChanged(QString)), this, SLOT(hostTextChanged(QString)));
    QObject::connect(portSpinBox, SIGNAL(valueChanged(int)), this, SLOT(portValueChanged(int)));
//    QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(save()));
}

void
QtShanoirSettingsWidget::loginTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setLogin(text.trimmed());
    QtShanoirSettings::Instance()->update();
}

void
QtShanoirSettingsWidget::passwordTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setPassword(text.trimmed());
    QtShanoirSettings::Instance()->update();
}

void
QtShanoirSettingsWidget::hostTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setHost(text.trimmed());
    QtShanoirSettings::Instance()->update();
}

void
QtShanoirSettingsWidget::portValueChanged(int value)
{
    QtShanoirSettings::Instance()->setPort(QString::number(value));
    QtShanoirSettings::Instance()->update();
}

void
QtShanoirSettingsWidget::save()
{
    QtShanoirSettings::Instance()->update();
}
