#ifndef EDITCENTERWINDOW_H
#define EDITCENTERWINDOW_H

#include "headers.h"
#include "center.h"
#include "myvalidator.h"

namespace Ui {
class EditCenterWindow;
}

class EditCenterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditCenterWindow(QWidget *parent = nullptr);
    ~EditCenterWindow();

    void closeEvent(QCloseEvent *event);

    Center getCenter();

    void setEditCenterWindowConfig();
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
    Ui::EditCenterWindow *ui;
    Center center;

    QValidator *validatorInteger;
    QValidator *validatorCyrillic;

};

#endif // EDITCENTERWINDOW_H
