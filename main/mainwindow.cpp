#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    databaseConnect();
    initializeMembers();
    setMainWindowConfig();

    authWindow->show();
    this->hide();

    connect(authWindow, &AuthWindow::sendSignalToMainWindowLoginPushButtonClicked, this, &MainWindow::getSignalFromAuthWindowLoginPushButtonClicked);
    connect(rootApplyWindow, &RootApplyWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromRootApplyWindowCloseEvent);
    connect(rootApplyWindow, &RootApplyWindow::sendSignalToMainWindowRootApplyPushButtonClicked, this, &MainWindow::getSignalFromRootApplyWindowRootApplyPushButtonClicked);
    connect(adminWindow, &AdminWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromAdminWindowCloseEvent);
    connect(centerWindow, &CenterWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromCenterWindowCloseEvent);
    connect(this, &MainWindow::sendSignalToCenterWindowOpen, centerWindow, &CenterWindow::getSignalFromMainWindowOpen);
    connect(settlementWindow, &SettlementWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromSettlementWindowCloseEvent);
    connect(evictWindow, &EvictWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromEvictWindowCloseEvent);
    connect(this, &MainWindow::sendSignalToEvictWindowOpen, evictWindow, &EvictWindow::getSignalFromMainWindowOpen);
    connect(moreInfoWindow, &MoreInfoWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromMoreInfoWindowCloseEvent);
    connect(reportWindow, &ReportWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromReportWindowCloseEvent);

    QAction *setllementAction = ui->menubar->addAction("Поселення | Реєстрація");
    connect(setllementAction, &QAction::triggered, settlementWindow, &SettlementWindow::getSignalFromMainWindow);
    connect(setllementAction, &QAction::triggered, this, &MainWindow::showSettlementWindow);

    QAction *evictAction = ui->menubar->addAction("Виселення");
    connect(evictAction, &QAction::triggered, this, &MainWindow::showEvictWindow);

    QAction *centerAction = ui->menubar->addAction("Центри поселення");
    connect(centerAction, &QAction::triggered, this, &MainWindow::showCenterWindow);

    QAction *adminAction = ui->menubar->addAction("Адміністратори");
    connect(adminAction, &QAction::triggered, this, &MainWindow::showRootApplyWindow);

    QAction *statsAction = ui->menubar->addAction("Звітність");
    connect(statsAction, &QAction::triggered, this, &MainWindow::showAdressReportWindow);

    QAction *quitAction = ui->menubar->addAction("Завершити роботу програми");
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);

}

MainWindow::~MainWindow()
{

    saveAdminConfigurationsToDatabase();

    delete ui;
    delete authWindow;
    delete moreInfoWindow;
    delete settlementWindow;
    delete evictWindow;
    delete centerWindow;
    delete adminWindow;
    delete rootApplyWindow;
    delete reportWindow;

    delete migrant;

    delete centerTableModel;
    delete centerQueryModel;

    delete migrantTableModel;
    delete migrantQueryModel;

    delete centerTableViewAction;
    delete migrantTableViewAction;

    delete myValidator;

}

void MainWindow::setMainWindowConfig()
{

    setWindowTitle("КущевськийАндрій, ПЗ-19-1");
    this->showMaximized();

    QList<QLineEdit *> listLineEdit;

    listLineEdit.push_back(ui->lastnameLineEdit);
    listLineEdit.push_back(ui->middlenameLineEdit);
    listLineEdit.push_back(ui->previousResidenceLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 20);

    listLineEdit.push_back(ui->firstnameLineEdit);
    myValidator->setCyrillicLineEditValidator(listLineEdit, 15);

    listLineEdit.push_back(ui->passportLineEdit);
    myValidator->setIntegerLineEditValidator(listLineEdit, 9);

    ui->checkinDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));
    ui->lastnameLineEdit->setFocus();

}

bool MainWindow::databaseConnect()
{

    this->database = QSqlDatabase::addDatabase("QODBC", "MyDatabase");

    QString connect = "DRIVER={MySQL ODBC 8.0 Unicode Driver};";

    connect.append("server = localhost, 3306;");
    connect.append("database = courseproject;");
    connect.append("user = root;");
    connect.append("password = 23kapkap;");
    connect.append("multi_host = 1;");
    database.setDatabaseName(connect);

    if(!database.open())
    {
        qDebug() << "Failed to database connnect!";
        return false;
    }

    return true;

}

void MainWindow::initializeMembers()
{

    this->reportWindow = new ReportWindow();
    this->authWindow = new AuthWindow();
    this->moreInfoWindow = new MoreInfoWindow();
    this->settlementWindow = new SettlementWindow();
    this->evictWindow = new EvictWindow();
    this->rootApplyWindow = new RootApplyWindow();
    this->adminWindow = new AdminWindow();
    this->centerWindow = new CenterWindow();

    this->query = new QSqlQuery(database);

    this->migrant = new Migrant();
    this->myValidator = new MyValidator();

    this->centerTableModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;
    this->centerQueryModel = new QSqlQueryModel(this);;
    this->centerTableModel->setTable("center");

    this->migrantTableModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;
    this->migrantQueryModel = new QSqlQueryModel(this);;
    this->migrantTableModel->setTable("migrant");

    this->centerTableViewAction = new CenterTableViewAction(ui->centerTableView, centerTableModel, centerQueryModel);
    this->migrantTableViewAction = new MigrantTableViewAction(ui->migrantTableView, migrantTableModel, migrantQueryModel);

    this->centerTableViewAction->setTableView();

}

void MainWindow::saveAdminConfigurationsToDatabase()
{

    QString str_t = "update config set config_posX = '%1', config_posY = '%2', config_width = '%3', config_length = '%4' where config_admin_id = (select admin_id from admin where admin_login = '%5');";
    this->queryString = str_t.arg(this->geometry().x()).arg(this->geometry().y()).arg(this->geometry().width()).arg(this->geometry().height()).arg(this->currentLogin);
    query->exec(queryString);

}

void MainWindow::setSearchParam()
{

    migrant = new Migrant(Personal(ui->passportLineEdit->text(), QString(), QString(), QString()), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), sex, ui->checkinDateEdit->text(), ui->previousResidenceLineEdit->text());
    migrantTableViewAction->setMigrant(*migrant);
    migrantTableViewAction->searchTableViewRecord();

}

void MainWindow::showEvictWindow()
{
    emit sendSignalToEvictWindowOpen();
    this->hide();
    this->evictWindow->showMaximized();
}

void MainWindow::showSettlementWindow()
{

    this->hide();
    this->settlementWindow->show();

}

void MainWindow::showCenterWindow()
{

    this->hide();
    emit sendSignalToCenterWindowOpen();
    this->centerWindow->showMaximized();

}

void MainWindow::showRootApplyWindow()
{

    this->hide();
    this->rootApplyWindow->show();

}

void MainWindow::showAdressReportWindow()
{

    this->hide();

    Admin setAdmin;

    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));
    query->prepare("select admin_lastname, admin_firstname, admin_middlename from admin where admin_login = '" + this->currentLogin + "';");
    query->exec();

    while(query->next()) setAdmin.setInitials(Initials(query->value(0).toString(), query->value(1).toString(), query->value(2).toString()));

    this->reportWindow->setAdmin(setAdmin);
    this->reportWindow->showMaximized();

}

void MainWindow::getSignalFromAuthWindowLoginPushButtonClicked()
{

    this->currentLogin = authWindow->getCurrentLogin();
    this->currentPassword = authWindow->getCurrentPassword();

    QString tempString = "select * from admin where admin_login = '%1';";

    this->queryString = tempString.arg(currentLogin);
    query->exec(queryString);

    record = query->record();
    query->next();

    if(this->currentLogin != query->value(record.indexOf("admin_login")).toString() || this->currentPassword != query->value(record.indexOf("admin_password")).toString())
    {

        qDebug() << "Invalid password!";
        authStatus = false;
        setWarningMessageBoxAuth();

    }
    else
    {
        authStatus = true;

        tempString = "select * from config where config_admin_id = (select admin_id from admin where admin_login = '%1');";

        query->clear();

        this->queryString = tempString.arg(currentLogin);
        query->exec(queryString);

        record = query->record();
        query->next();

        this->setGeometry(query->value(record.indexOf("config_posX")).toInt(), query->value(record.indexOf("config_posY")).toInt(),
                          query->value(record.indexOf("config_width")).toInt(), query->value(record.indexOf("config_length")).toInt());

        authWindow->hide();
        this->show();

        qDebug() << "Login successfull!";

    }

}

void MainWindow::getSignalFromRootApplyWindowCloseEvent()
{

    this->rootApplyWindow->hide();
    this->show();

}

void MainWindow::getSignalFromRootApplyWindowRootApplyPushButtonClicked(QString rootLogin, QString rootPassword)
{

    if(rootLogin == this->mainRootLogin && rootPassword == this->mainRootPassword)
    {
        this->hide();
        this->rootApplyWindow->hide();
        this->adminWindow->setCurrentAdminLogin(this->currentLogin);
        this->adminWindow->showMaximized();
    }
    else
    {
        QMessageBox::warning(this, "Помилка авторизації!", "Невірний логін або пароль! Спробуйте ще раз!");
        this->show();

    }

}

void MainWindow::getSignalFromAdminWindowCloseEvent()
{
    this->adminWindow->hide();
    this->show();
}

void MainWindow::getSignalFromCenterWindowCloseEvent()
{
    this->centerTableViewAction->setTableView();
    this->centerWindow->hide();
    this->show();
}

void MainWindow::getSignalFromSettlementWindowCloseEvent()
{
    this->centerTableViewAction->setTableView();
    this->settlementWindow->hide();
    this->show();
}

void MainWindow::getSignalFromEvictWindowCloseEvent()
{

    QModelIndex myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
    QVariant center_id = ui->centerTableView->model()->data(myIndex);

    QString query = "select * from migrant where migrant_center_id = " + center_id.toString() + ";";

    this->migrantQueryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    ui->migrantTableView->setModel(migrantQueryModel);
    migrantTableViewAction->setSqlQueryModelHeadersData();

    this->centerTableViewAction->setTableView();
    this->evictWindow->hide();
    this->show();

}

void MainWindow::getSignalFromMoreInfoWindowCloseEvent()
{
    this->moreInfoWindow->hide();
    this->show();
}

void MainWindow::getSignalFromReportWindowCloseEvent()
{
    this->reportWindow->hide();
    this->show();
}

void MainWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void MainWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void MainWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void MainWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void MainWindow::on_checkinDateEdit_dateChanged(const QDate &date)
{
    setSearchParam();
}

void MainWindow::on_previousResidenceLineEdit_textEdited(const QString &arg1)
{
    setSearchParam();
}

void MainWindow::on_centerTableView_doubleClicked(const QModelIndex &index)
{

    QModelIndex myIndex = ui->centerTableView->model()->index(ui->centerTableView->currentIndex().row(), 0, QModelIndex());
    QVariant center_id = ui->centerTableView->model()->data(myIndex);

    QString query = "select * from migrant where migrant_center_id = " + center_id.toString() + ";";

    this->migrantQueryModel->setQuery(query, QSqlDatabase::database("MyDatabase"));
    ui->migrantTableView->setModel(migrantQueryModel);
    migrantTableViewAction->setSqlQueryModelHeadersData();

}

void MainWindow::on_migrantTableView_doubleClicked(const QModelIndex &index)
{

    QModelIndex myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 0, QModelIndex());
    QVariant migrant_id = ui->migrantTableView->model()->data(myIndex);

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 2, QModelIndex());
    QVariant migrant_family_id = ui->migrantTableView->model()->data(myIndex);

    myIndex = ui->migrantTableView->model()->index(ui->migrantTableView->currentIndex().row(), 3, QModelIndex());
    QVariant migrant_group_id = ui->migrantTableView->model()->data(myIndex);

    this->moreInfoWindow->setMigrantId(migrant_id.toInt(), migrant_family_id.toInt(), migrant_group_id.toInt());
    this->hide();
    this->moreInfoWindow->show();

}
