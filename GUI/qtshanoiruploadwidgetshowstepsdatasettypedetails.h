#ifndef QTSHANOIRUPLOADWIDGETSHOWSTEPSDATASETTYPEDETAILS_H
#define QTSHANOIRUPLOADWIDGETSHOWSTEPSDATASETTYPEDETAILS_H

#include <QWidget>
#include <QtGui>

namespace Ui
{
class QtShanoirUploadWidgetShowStepsDatasetTypeDetails;
}

class QtShanoirUploadWidgetShowStepsDatasetTypeDetails : public QWidget
{
    Q_OBJECT

public:
    explicit QtShanoirUploadWidgetShowStepsDatasetTypeDetails(QWidget *parent = 0);
    void clearWidget();
public slots:
    void buildUpdateSteps(QMap<QString, int>);

private:
    Ui::QtShanoirUploadWidgetShowStepsDatasetTypeDetails *ui;
};

#endif // QTSHANOIRUPLOADWIDGETSHOWSTEPSDATASETTYPEDETAILS_H
