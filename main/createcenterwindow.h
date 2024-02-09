#ifndef CREATECENTERWINDOW_H
#define CREATECENTERWINDOW_H

#include "headers.h"
#include "center.h"
#include "myvalidator.h"

namespace Ui {
class CreateCenterWindow;
}

class CreateCenterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateCenterWindow(QWidget *parent = nullptr);
    ~CreateCenterWindow();

    void closeEvent(QCloseEvent *event);

    Center getCenter();

    void setCreateCenterWindowConfig();
    void checkCorrectInput();

signals:
    void sendSignalToCenterWindowCloseEvent();
    void sendSignalToCenterWindowApplyPushButtonClicked();

private slots:

    void on_applyPushButton_clicked();

    void on_streetLineEdit_textChanged(const QString &arg1);

    void on_houseLineEdit_textChanged(const QString &arg1);

    void on_generalPlacesLineEdit_textChanged(const QString &arg1);

private:
    Ui::CreateCenterWindow *ui;
    Center center;

    QValidator *validatorInteger;
    QValidator *validatorCyrillic;

};
#endif // CREATECENTERWINDOW_H
