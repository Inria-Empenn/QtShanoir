/*
 * QtShanoirSettingsWidget.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
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
    QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(save()));
}

void
QtShanoirSettingsWidget::loginTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setLogin(text.trimmed());
}

void
QtShanoirSettingsWidget::passwordTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setPassword(text.trimmed());
}

void
QtShanoirSettingsWidget::hostTextChanged(QString text)
{
    QtShanoirSettings::Instance()->setHost(text.trimmed());
}

void
QtShanoirSettingsWidget::portValueChanged(int value)
{
    QtShanoirSettings::Instance()->setPort(QString::number(value));
}

void
QtShanoirSettingsWidget::save()
{
    QtShanoirSettings::Instance()->update();
}
