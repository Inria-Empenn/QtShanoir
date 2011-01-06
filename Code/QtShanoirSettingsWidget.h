/*
 * QtShanoirSettingsWidget.h
 *
 *  Created on: 6 janv. 2011
 *      Author: aabadie
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
