#include "createcenterwindow.h"
#include "ui_createcenterwindow.h"

CreateCenterWindow::CreateCenterWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CreateCenterWindow)
{
    ui->setupUi(this);
    setCreateCenterWindowConfig();

}

CreateCenterWindow::~CreateCenterWindow()
{
    delete ui;

    if(this->validatorInteger != nullptr)
        delete validatorInteger;

    if(this->validatorCyrillic != nullptr)
        delete validatorCyrillic;
}

void CreateCenterWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToCenterWindowCloseEvent();

}

Center CreateCenterWindow::getCenter()
{

    this->center.setStreet(ui->streetLineEdit->text());
    this->center.setHouse(ui->houseLineEdit->text());
    this->center.setGeneralPlacesAmount(ui->generalPlacesLineEdit->text());
    this->center.setAvailablePlacesAmount(ui->generalPlacesLineEdit->text());

    setCreateCenterWindowConfig();

    return center;

}

void CreateCenterWindow::setCreateCenterWindowConfig()
{

    this->setWindowTitle("Створення центру переселенців");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window |  Qt::WindowCloseButtonHint);

    ui->applyPushButton->setEnabled(false);

    ui->streetLineEdit->setFocus();
    ui->streetLineEdit->clear();
    ui->houseLineEdit->clear();
    ui->generalPlacesLineEdit->clear();
    ui->generalPlacesLineEdit->clear();

    QRegularExpression regexInteger("^[0-9]{3}$");
    validatorInteger = new QRegularExpressionValidator(regexInteger);
    ui->houseLineEdit->setValidator(validatorInteger);
    ui->generalPlacesLineEdit->setValidator(validatorInteger);

    QRegularExpression regexCyrillic ("^[а-яА-яа-яА-яІіЇї.]{20}$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);
    validatorCyrillic  = new QRegularExpressionValidator(regexCyrillic);
    validatorCyrillic->setLocale(QLocale::AnyLanguage);
    ui->streetLineEdit->setValidator(validatorCyrillic);

}

void CreateCenterWindow::checkCorrectInput()
{

    if(ui->streetLineEdit->text().isEmpty() || ui->houseLineEdit->text().isEmpty() || ui->generalPlacesLineEdit->text().isEmpty()) { ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }
    if((ui->streetLineEdit->text().size() < 4 || ui->streetLineEdit->text().size() > 20) || (ui->generalPlacesLineEdit->text().toInt() < 50 || ui->generalPlacesLineEdit->text().toInt() > 300)){ ui->applyPushButton->setEnabled(false); return; } else{ ui->applyPushButton->setEnabled(true); }

}

void CreateCenterWindow::on_streetLineEdit_textChanged(const QString &arg1)
{
    checkCorrectInput();
}

void CreateCenterWindow::on_houseLineEdit_textChanged(const QString &arg1)
{
    checkCorrectInput();
}

void CreateCenterWindow::on_generalPlacesLineEdit_textChanged(const QString &arg1)
{
    checkCorrectInput();
}

void CreateCenterWindow::on_applyPushButton_clicked()
{
    emit sendSignalToCenterWindowApplyPushButtonClicked();
}
