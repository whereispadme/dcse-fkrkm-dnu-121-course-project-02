#include "rootapplywindow.h"
#include "ui_rootapplywindow.h"

RootApplyWindow::RootApplyWindow(QWidget *parent) : QWidget(parent), ui(new Ui::RootApplyWindow)
{

    ui->setupUi(this);
    this->myValidator = new MyValidator();

    setRootApplyWindowConfig();

}

RootApplyWindow::~RootApplyWindow()
{

    delete ui;
    delete myValidator;

}

void RootApplyWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToMainWindowCloseEvent();

}

void RootApplyWindow::setRootApplyWindowConfig()
{

    this->setWindowTitle("Root Access");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowCloseButtonHint);

    myValidator->setLoginLineEditValidator(ui->rootLoginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->rootPasswordLineEdit);

    ui->rootLoginLineEdit->setFocus();
    ui->rootLoginLineEdit->clear();
    ui->rootPasswordLineEdit->clear();
    ui->rootPasswordLineEdit->setEchoMode(QLineEdit::Password);

    ui->rootApplyPushButton->setEnabled(false);

    ui->visibleIconPushButton->setIcon(QIcon(":/icons/visible_eye.png"));
    ui->hiddenIconPushButton->setIcon(QIcon(":/icons/hide_eye.png"));
    ui->visibleIconPushButton->setGeometry(380, 46, 21, 31);
    ui->hiddenIconPushButton->setGeometry(380, 46, 21, 31);
    ui->visibleIconPushButton->show();
    ui->hiddenIconPushButton->hide();

}

void RootApplyWindow::on_rootLoginLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput(ui->rootLoginLineEdit, ui->rootPasswordLineEdit, ui->rootApplyPushButton);
}

void RootApplyWindow::on_rootPasswordLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput(ui->rootLoginLineEdit, ui->rootPasswordLineEdit, ui->rootApplyPushButton);
}

void RootApplyWindow::on_checkBox_stateChanged(int arg1)
{

    if(ui->checkBox->isChecked())
    {
       ui->rootPasswordLineEdit->setEchoMode(QLineEdit::Normal);
       ui->visibleIconPushButton->hide();
       ui->hiddenIconPushButton->show();
    }
    else
    {
        ui->rootPasswordLineEdit->setEchoMode(QLineEdit::Password);
        ui->visibleIconPushButton->show();
        ui->hiddenIconPushButton->hide();
    }

}

void RootApplyWindow::on_visibleIconPushButton_clicked()
{

    ui->rootPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->visibleIconPushButton->hide();
    ui->hiddenIconPushButton->show();

    ui->checkBox->setChecked(true);

}

void RootApplyWindow::on_hiddenIconPushButton_clicked()
{

    ui->rootPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->hiddenIconPushButton->hide();
    ui->visibleIconPushButton->show();

    ui->checkBox->setChecked(false);

}

void RootApplyWindow::on_rootApplyPushButton_clicked()
{
    emit sendSignalToMainWindowRootApplyPushButtonClicked(ui->rootLoginLineEdit->text(), ui->rootPasswordLineEdit->text());
    setRootApplyWindowConfig();
}
