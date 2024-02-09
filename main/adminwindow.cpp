#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AdminWindow)
{

    ui->setupUi(this);
    setAdminWindowConfig();

    this->searchAdminWindow = new SearchAdminWindow();
    this->createAdminWindow = new CreateAdminWindow();
    this->editAdminWindow = new EditAdminWindow();

    queryModel = new QSqlQueryModel(this);
    model = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));
    model->setTable("admin");

    adminTableViewAction = new AdminTableViewAction(ui->adminTableView, model, queryModel);
    adminTableViewAction->setTableView();

    connect(this->searchAdminWindow, &SearchAdminWindow::sendSignalToAdminWindowCloseEvent, this, &AdminWindow::getSignalFromSearchAdminWindowCloseEvent);
    connect(this->searchAdminWindow, &SearchAdminWindow::sendSignalToAdminWindowApplyPushButtonClicked, this, &AdminWindow::getSignalFromSearchAdminWindowAppyPushButtonClicked);
    connect(this->createAdminWindow, &CreateAdminWindow::sendSignalToAdminWindowCloseEvent, this, &AdminWindow::getSignalFromCreateAdminWindowCloseEvent);
    connect(this->createAdminWindow, &CreateAdminWindow::sendSignalToAdminWindowApplyPushButtonClicked, this, &AdminWindow::getSignalFromCreateAdminWindowAppyPushButtonClicked);
    connect(this->editAdminWindow, &EditAdminWindow::sendSignalToAdminWindowCloseEvent, this, &AdminWindow::getSignalFromEditAdminWindowCloseEvent);
    connect(this->editAdminWindow, &EditAdminWindow::sendSignalToAdminWindowApplyPushButtonClicked, this, &AdminWindow::getSignalFromEditAdminWindowAppyPushButtonClicked);

}

AdminWindow::~AdminWindow()
{

    delete ui;
    delete searchAdminWindow;
    delete createAdminWindow;
    delete editAdminWindow;

    delete model;
    delete queryModel;
    delete adminTableViewAction;

}

void AdminWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToMainWindowCloseEvent();

}

void AdminWindow::setAdminWindowConfig()
{

    this->setWindowTitle("Адміністратори");

}

void AdminWindow::setCurrentAdminLogin(QString login)
{
    this->currentAdminLogin = login;
}

//search
void AdminWindow::getSignalFromSearchAdminWindowCloseEvent()
{

    this->searchAdminWindow->hide();
    this->show();

}

void AdminWindow::getSignalFromSearchAdminWindowAppyPushButtonClicked()
{

    this->searchAdminWindow->hide();
    this->show();

    this->admin = this->searchAdminWindow->getAdmin();
    this->adminTableViewAction->setAdmin(this->admin);
    this->adminTableViewAction->searchTableViewRecord(searchAdminWindow->getTypeSearch());

}

void AdminWindow::on_searchAdminPushButton_clicked()
{

    this->hide();
    this->searchAdminWindow->show();

}

//create
void AdminWindow::getSignalFromCreateAdminWindowCloseEvent()
{

    this->createAdminWindow->hide();
    this->show();

}

void AdminWindow::getSignalFromCreateAdminWindowAppyPushButtonClicked()
{

    this->createAdminWindow->hide();
    this->show();

    this->admin = this->createAdminWindow->getAdmin();
    this->adminTableViewAction->setAdmin(this->admin);
    this->adminTableViewAction->createTableViewRecord();

}

void AdminWindow::on_createAdminPushButton_clicked()
{
    this->hide();
    this->createAdminWindow->show();
}

//remove
void AdminWindow::on_removeAdminPushButton_clicked()
{

    this->adminTableViewAction->setMainWindowAdminLogin(this->currentAdminLogin);
    this->adminTableViewAction->removeTableViewRecord();

}

//edit
void AdminWindow::getSignalFromEditAdminWindowCloseEvent()
{
    this->editAdminWindow->hide();
    this->show();
}

void AdminWindow::getSignalFromEditAdminWindowAppyPushButtonClicked()
{

    this->editAdminWindow->hide();
    this->show();

    this->admin = this->editAdminWindow->getAdmin();

    this->adminTableViewAction->setMainWindowAdminLogin(this->currentAdminLogin);
    this->adminTableViewAction->setAdmin(admin);
    this->adminTableViewAction->editTableViewRecord();

}

void AdminWindow::on_editAdminPushButton_clicked()
{

    this->hide();
    this->editAdminWindow->show();

}

//reset
void AdminWindow::on_resetPushButton_clicked()
{

    this->adminTableViewAction->setTableView();

}
