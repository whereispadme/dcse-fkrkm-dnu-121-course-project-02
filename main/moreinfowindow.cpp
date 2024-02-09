#include "moreinfowindow.h"
#include "ui_moreinfowindow.h"

MoreInfoWindow::MoreInfoWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MoreInfoWindow)
{
    ui->setupUi(this);

    personalQueryModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;
    familyGroupQueryModel = new QSqlTableModel(this, QSqlDatabase::database("MyDatabase"));;

    setWindowTitle("Персональні дані вибраного переселенця");

}

MoreInfoWindow::~MoreInfoWindow()
{
    delete ui;
    delete personalQueryModel;
    delete familyGroupQueryModel;
}

void MoreInfoWindow::closeEvent(QCloseEvent *event)
{
    familyGroupQueryModel->clear();
    ui->familyGroupTableView->setModel(familyGroupQueryModel);
    emit sendSignalToMainWindowCloseEvent();
}

void MoreInfoWindow::setFamilyGroupTableViewHeadersData()
{

    familyGroupQueryModel->setHeaderData(0, Qt::Horizontal, ("migrant_id"));
    familyGroupQueryModel->setHeaderData(1, Qt::Horizontal, ("migrant_center_id"));
    familyGroupQueryModel->setHeaderData(2, Qt::Horizontal, ("migrant_family_id"));
    familyGroupQueryModel->setHeaderData(3, Qt::Horizontal, ("migrant_group_id"));
    familyGroupQueryModel->setHeaderData(4, Qt::Horizontal, ("Прізвище"));
    familyGroupQueryModel->setHeaderData(5, Qt::Horizontal, ("Ім'я"));
    familyGroupQueryModel->setHeaderData(6, Qt::Horizontal, ("По батькові"));
    familyGroupQueryModel->setHeaderData(7, Qt::Horizontal, ("Стать"));
    familyGroupQueryModel->setHeaderData(8, Qt::Horizontal, ("Дата реєстрації"));
    familyGroupQueryModel->setHeaderData(9, Qt::Horizontal, ("Поперереднє м.п."));

    ui->familyGroupTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->familyGroupTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->familyGroupTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->familyGroupTableView->setSortingEnabled(true);

    ui->familyGroupTableView->selectRow(0);

    ui->familyGroupTableView->setColumnHidden(0, true);
    ui->familyGroupTableView->setColumnHidden(1, true);
    ui->familyGroupTableView->setColumnHidden(2, true);
    ui->familyGroupTableView->setColumnHidden(3, true);
    ui->familyGroupTableView->setColumnHidden(10, true);
    ui->familyGroupTableView->setColumnHidden(11, true);
    ui->familyGroupTableView->setColumnHidden(12, true);
    ui->familyGroupTableView->setColumnHidden(13, true);
    ui->familyGroupTableView->setColumnHidden(14, true);
    ui->familyGroupTableView->setColumnHidden(14, true);

    int avarageSize = (ui->familyGroupTableView->geometry().width() / 6) - 4;

    ui->familyGroupTableView->setColumnWidth(4, avarageSize);
    ui->familyGroupTableView->setColumnWidth(5, avarageSize);
    ui->familyGroupTableView->setColumnWidth(6, avarageSize);
    ui->familyGroupTableView->setColumnWidth(7, avarageSize);
    ui->familyGroupTableView->setColumnWidth(8, avarageSize);
    ui->familyGroupTableView->setColumnWidth(9, avarageSize);

}

void MoreInfoWindow::setMigrantId(int migrant_id, int migrant_family_id, int migrant_group_id)
{

    QString sqlQuery;

    sqlQuery = "select * from personal where personal_migrant_id = " + QString::number(migrant_id) + ";";

    personalQueryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
    ui->personalTableView->setModel(personalQueryModel);

    personalQueryModel->setHeaderData(0, Qt::Horizontal, ("personal_id"));
    personalQueryModel->setHeaderData(1, Qt::Horizontal, ("Номер документу"));
    personalQueryModel->setHeaderData(2, Qt::Horizontal, ("Номер телефону"));
    personalQueryModel->setHeaderData(3, Qt::Horizontal, ("Дата народження"));
    personalQueryModel->setHeaderData(4, Qt::Horizontal, ("Особливі потреби"));

    ui->personalTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->personalTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->personalTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->personalTableView->setSortingEnabled(true);

    ui->personalTableView->setColumnHidden(0, true);
    int avarageSize = (ui->personalTableView->geometry().width() / 4) - 6;

    ui->personalTableView->setColumnWidth(1, avarageSize);
    ui->personalTableView->setColumnWidth(2, avarageSize);
    ui->personalTableView->setColumnWidth(3, avarageSize);
    ui->personalTableView->setColumnWidth(4, avarageSize);
\
    if(migrant_family_id != 0)
    {

        sqlQuery = "select * from migrant where migrant_family_id = " + QString::number(migrant_family_id) + ";";

        familyGroupQueryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
        ui->familyGroupTableView->setModel(familyGroupQueryModel);
        setFamilyGroupTableViewHeadersData();

        return;


    }

    if(migrant_group_id != 0)
    {

        sqlQuery = "select * from migrant where migrant_group_id = " + QString::number(migrant_group_id) + ";";

        familyGroupQueryModel->setQuery(sqlQuery, QSqlDatabase::database("MyDatabase"));
        ui->familyGroupTableView->setModel(familyGroupQueryModel);
        setFamilyGroupTableViewHeadersData();

        return;

    }

}
