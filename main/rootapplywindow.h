#ifndef ROOTAPPLYWINDOW_H
#define ROOTAPPLYWINDOW_H

#include "headers.h"
#include "functions.h"
#include "myvalidator.h"

namespace Ui {
class RootApplyWindow;
}

class RootApplyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RootApplyWindow(QWidget *parent = nullptr);
    ~RootApplyWindow();

    void closeEvent(QCloseEvent *event);
    void setRootApplyWindowConfig();

signals:
    void sendSignalToMainWindowCloseEvent();
    void sendSignalToMainWindowRootApplyPushButtonClicked(QString, QString);

private slots:
    void on_rootLoginLineEdit_textEdited(const QString &arg1);

    void on_rootPasswordLineEdit_textEdited(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_rootApplyPushButton_clicked();

    void on_visibleIconPushButton_clicked();

    void on_hiddenIconPushButton_clicked();

private:
    Ui::RootApplyWindow *ui;

    MyValidator *myValidator;

};

#endif
