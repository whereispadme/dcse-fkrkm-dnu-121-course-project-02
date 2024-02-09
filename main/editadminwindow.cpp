#include "editadminwindow.h"
#include "ui_editadminwindow.h"

EditAdminWindow::EditAdminWindow(QWidget *parent) :  QWidget(parent), ui(new Ui::EditAdminWindow)
{
    ui->setupUi(this);
    setEditAdminWindowConfig();
}

EditAdminWindow::~EditAdminWindow()
{
    delete ui;
    delete admin;
}

void EditAdminWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToAdminWindowCloseEvent();

}

Admin EditAdminWindow::getAdmin()
{

    Initials initials;
    initials.lastname = ui->lastnameLineEdit->text();
    initials.firstname = ui->firstnameLineEdit->text();
    initials.middlename = ui->middlenameLineEdit->text();

    admin = new Admin(ui->loginLineEdit->text(), ui->passwordLineEdit->text(), &initials);

    setEditAdminWindowConfig();

    return admin;

}

void EditAdminWindow::setEditAdminWindowConfig()
{

    this->setWindowTitle("Редагування адміністратора");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window |  Qt::WindowCloseButtonHint);

    ui->applyPushButton->setEnabled(false);

    ui->loginLineEdit->setFocus();
    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->lastnameLineEdit->clear();
    ui->firstnameLineEdit->clear();
    ui->middlenameLineEdit->clear();

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->firstnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);

    MyValidator *myValidator = new MyValidator();
    myValidator->setCyrillicLineEditValidator(listLineEdit);

    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->passwordLineEdit);

    delete myValidator;

}

void EditAdminWindow::checkCorrectInput()
{

    if(ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    if((ui->loginLineEdit->text().size() <= 5 || ui->loginLineEdit->text().size() >= 21) || (ui->passwordLineEdit->text().size() <= 7 || ui->passwordLineEdit->text().size() >= 21)){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }

    if(ui->lastnameLineEdit->text().isEmpty() || ui->firstnameLineEdit->text().isEmpty() || ui->middlenameLineEdit->text().isEmpty()){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    if(ui->lastnameLineEdit->text().size() >= 21 || ui->firstnameLineEdit->text().size() >= 16 || ui->middlenameLineEdit->text().size() >= 21){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }

}

void EditAdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void EditAdminWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void EditAdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void EditAdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void EditAdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    checkCorrectInput();
}

void EditAdminWindow::on_applyPushButton_clicked()
{
    emit sendSignalToAdminWindowApplyPushButtonClicked();
}
