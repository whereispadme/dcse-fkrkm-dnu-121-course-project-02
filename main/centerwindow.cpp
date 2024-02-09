#include "centerwindow.h"
#include "ui_centerwindow.h"

CenterWindow::CenterWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CenterWindow)
{

    ui->setupUi(this);
    setCenterWindowConfig();

    this->createCenterWindow = new CreateCenterWindow();
    this->editCenterWindow = new EditCenterWindow();

    queryModel = new QSqlQueryModel(this);
    model = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));
    model->setTable("center");

    centerTableViewAction = new CenterTableViewAction(ui->centerTableView, model, queryModel);
    centerTableViewAction->setTableView();

    connect(this->createCenterWindow, &CreateCenterWindow::sendSignalToCenterWindowCloseEvent, this, &CenterWindow::getSignalFromCreateCenterWindowCloseEvent);
    connect(this->createCenterWindow, &CreateCenterWindow::sendSignalToCenterWindowApplyPushButtonClicked, this, &CenterWindow::getSignalFromCreateCenterWindowAppyPushButtonClicked);
    connect(this->editCenterWindow, &EditCenterWindow::sendSignalToCenterWindowCloseEvent, this, &CenterWindow::getSignalFromEditCenterWindowCloseEvent);
    connect(this->editCenterWindow, &EditCenterWindow::sendSignalToCenterWindowApplyPushButtonClicked, this, &CenterWindow::getSignalFromEditCenterWindowAppyPushButtonClicked);

}

CenterWindow::~CenterWindow()
{

    delete ui;
    delete createCenterWindow;
    delete editCenterWindow;

    delete model;
    delete queryModel;
    delete centerTableViewAction;

}

void CenterWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToMainWindowCloseEvent();

}

void CenterWindow::setCenterWindowConfig()
{

    this->setWindowTitle("Центри переселенців");

}

void CenterWindow::setSearchParam()
{

    center = new Center();
    centerTableViewAction->setCenter(center);

}

//create
void CenterWindow::getSignalFromCreateCenterWindowCloseEvent()
{

    this->createCenterWindow->hide();
    this->show();

}

void CenterWindow::getSignalFromCreateCenterWindowAppyPushButtonClicked()
{

    this->createCenterWindow->hide();
    this->show();

    this->center = this->createCenterWindow->getCenter();
    this->centerTableViewAction->setCenter(this->center);
    this->centerTableViewAction->createTableViewRecord();

}

void CenterWindow::on_createCenterPushButton_clicked()
{
    this->hide();
    this->createCenterWindow->show();
}

//edit
void CenterWindow::getSignalFromEditCenterWindowCloseEvent()
{
    this->editCenterWindow->hide();
    this->show();
}

void CenterWindow::getSignalFromEditCenterWindowAppyPushButtonClicked()
{
    this->editCenterWindow->hide();
    this->show();

    this->center = this->editCenterWindow->getCenter();
    this->centerTableViewAction->setCenter(center);
    this->centerTableViewAction->editTableViewRecord();

}

void CenterWindow::getSignalFromMainWindowOpen()
{
    if(this->centerTableViewAction != nullptr)
        this->centerTableViewAction->setTableView();
}

void CenterWindow::on_editCenterPushButton_clicked()
{
    this->editCenterWindow->show();
    this->hide();
}

//remove
void CenterWindow::on_removeCenterPushButton_clicked()
{

    this->centerTableViewAction->removeTableViewRecord();

}

void CenterWindow::on_resetPushButton_clicked()
{

    this->centerTableViewAction->setTableView();

}
