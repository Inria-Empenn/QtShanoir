#ifndef SHANOIRSERVERPARAMETERS_H
#define SHANOIRSERVERPARAMETERS_H

#include <QDialog>

namespace Ui {
    class QtShanoirConfig;
}

class ShanoirServerParameters : public QDialog {
    Q_OBJECT
public:
    ShanoirServerParameters(QWidget *parent = 0);
    ~ShanoirServerParameters();

    void getParameters(QString& user, QString& password, QString& host, QString& port);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtShanoirConfig *ui;
};

#endif // SHANOIRSERVERPARAMETERS_H