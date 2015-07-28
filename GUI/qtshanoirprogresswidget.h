#ifndef QTSHANOIRPROGRESSWIDGET
#define QTSHANOIRPROGRESSWIDGET

#include "ui_qtshanoirprogresswidget.h"

namespace Ui
{
class QtShanoirProgressWidget;
}

class QtShanoirProgressWidget : public QWidget //private
{
    Q_OBJECT
public:
    explicit QtShanoirProgressWidget(QWidget * parent = 0);
    void setDatasetName(QString);
    void showProgressBar();
    void hideProgressBar();
    void setProgressBarValue(int);

signals:
    void progressShown();
    void progressHidden();
private:
    Ui::QtShanoirProgressWidget *ui;
};
#endif // QTSHANOIRPROGRESSWIDGET

