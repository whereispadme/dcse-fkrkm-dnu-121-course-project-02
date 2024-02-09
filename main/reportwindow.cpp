#include "reportwindow.h"
#include "ui_reportwindow.h"

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

ReportWindow::ReportWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ReportWindow)
{

    ui->setupUi(this);
    setReportWindowConfig();

}

ReportWindow::~ReportWindow()
{
    delete ui;
}

void ReportWindow::closeEvent(QCloseEvent *event)
{

    emit sendSignalToMainWindowCloseEvent();

}

void ReportWindow::setReportWindowConfig()
{

    setWindowTitle("Звітність");

    ui->startDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));
    ui->endDateEdit->setDate(QDate(QDateTime::currentDateTime().toString("yyyy").toInt(), QDateTime::currentDateTime().toString("MM").toInt(), QDateTime::currentDateTime().toString("dd").toInt()));

    ui->radioButton_2->setChecked(true);
    ui->groupBox_3->setEnabled(false);

}

void ReportWindow::on_pushButton_clicked()
{

    if(ui->radioButton_2->isChecked())
    {

        if(variable == 0)
        {

            QStringList adress;
            QStringList amount;

            QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));
            query->prepare("select center_street, center_house, count(*) as 'Кол-во людей зарегистрированных на эту дату' "
                           "from migrant inner join center on migrant_center_id = center_id where migrant_checkin >= :date1 and migrant_checkin <= :date2 group by center_street, center_house;");
            query->bindValue(":date1", ui->startDateEdit->text());
            query->bindValue(":date2", ui->endDateEdit->text());
            query->exec();

            QBarSet *set0 = new QBarSet("Кількість осіб");
            set0->setColor(Qt::green);
            set0->setPen(QPen(Qt::darkGreen, 2));

            while(query->next()) { adress.push_back("Вул. " + query->value(0).toString() + ", буд. " + query->value(1).toString()); set0->append(query->value(2).toInt()); }

            series = new QBarSeries();
            series->append(set0);

            chart = new QChart();
            chart->addSeries(series);
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setTitle("Гістограма за період з підрахунком кількості осіб за кожною адресою");

            axisX = new QBarCategoryAxis();
            axisX->append(adress);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            query->prepare("select count(*) from migrant;");
            query->exec();
            query->next();

            axisY = new QValueAxis();
            axisY->setRange(0, query->value(0).toInt());
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);

            chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            layout = new QHBoxLayout(ui->barChartFrame);
            layout->addWidget(chartView);

            ++variable;
            return;

        }
        else
        {

            QStringList adress;
            QStringList amount;

            QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));
            query->prepare("select center_street, center_house, count(*) as 'Кол-во людей зарегистрированных на эту дату' "
                           "from migrant inner join center on migrant_center_id = center_id where migrant_checkin >= :date1 and migrant_checkin <= :date2 group by center_street, center_house;");
            query->bindValue(":date1", ui->startDateEdit->text());
            query->bindValue(":date2", ui->endDateEdit->text());
            query->exec();

            QBarSet *set0 = new QBarSet("Кількість осіб");
            set0->setColor(Qt::green);
            set0->setPen(QPen(Qt::darkGreen, 2));

            while(query->next()) { adress.push_back("Вул. " + query->value(0).toString() + ", буд. " + query->value(1).toString()); set0->append(query->value(2).toInt()); }

            QBarSeries *series = new QBarSeries();
            series->append(set0);

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setTitle("Гістограма за період з підрахунком кількості осіб за кожною адресою");

            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(adress);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            query->prepare("select count(*) from migrant;");
            query->exec();
            query->next();

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(0, query->value(0).toInt());
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            QHBoxLayout *layout = new QHBoxLayout(ui->barChartFrame_2);
            layout->addWidget(chartView);

            ++variable;
            return;

        }

        return;

    }

    if(ui->documentRadioButton->isChecked())
    {

        QString global;
        QStringList adress;
        QStringList amount;

        QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("MyDatabase"));

        query->prepare("select center_street, center_house, count(*) as 'Кол-во людей зарегистрированных на эту дату' "
                       "from migrant inner join center on migrant_center_id = center_id where migrant_checkin >= :date1 and migrant_checkin <= :date2 group by center_street, center_house;");
        query->bindValue(":date1", ui->startDateEdit->text());
        query->bindValue(":date2", ui->endDateEdit->text());
        query->exec();

        while(query->next()) { adress.push_back("Вул. " + query->value(0).toString() + ", буд. " + query->value(1).toString()); amount.push_back(query->value(2).toString()); }

        for(int i = 0; i < adress.size(); ++i)
        {
            global.append("[" + QString::number(i+1) + "]" + " Адреса центру: " + adress[i] + "; Кількість поселень у центрі за даний період: " + amount[i] + ".\n\n");
        }

        QPixmap p = chartView->grab();
        p.save("D:\\report.png", "PNG");

        QString pdf =
        "<div align=right>"
           + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")  +
        "</div>"
        "<style> .img-right { transform: rotate(90deg); } </style>"
        "<div align=left>"
           "Адміністратор: <br>" + currentAdmin.getInitials().lastname + " " + currentAdmin.getInitials().firstname[0] + ". " + currentAdmin.getInitials().middlename[0] + ".<br>"
        "</div>"
        "<h3 align=center><br>Звіт з інформацією про кількість поселень по адресах за період з " + ui->startDateEdit->text() + " по " + ui->endDateEdit->text() + "</h3>"
        "<p align=justify><br><br>"
           + global +
        "</p>"
        "<div align=right>Підпис</div>";

        QTextDocument document;
        document.setHtml(pdf);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("D:\\reportfilepdf.pdf");
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        document.print(&printer);
        QDesktopServices::openUrl(QUrl::fromLocalFile("D:\\reportfilepdf.pdf"));

        QString html =
        "<div align=right>"
           + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")  +
        "</div>"
        "<div align=left>"
           "Адміністратор: <br>" + currentAdmin.getInitials().lastname + " " + currentAdmin.getInitials().firstname[0] + ". " + currentAdmin.getInitials().middlename[0] + ".<br>"
        "</div>"
        "<h3 align=center><br>Звіт з інформацією про кількість поселень по адресах за період з " + ui->startDateEdit->text() + " по " + ui->endDateEdit->text() + "</h3>"
        "<p align=justify><br><br>"
           + global +
                "<br><br><img src=""D:\\report.png"" alt="" class=""img-right"">"
        "</p>"
        "<div align=right>Підпис</div>";

        QFile file("D:\\reportfilehtml.html");

        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream writeStream(&file);
            writeStream << html;
            file.close();
        }

        QDesktopServices::openUrl(QUrl::fromLocalFile("D:\\reportfilehtml.html"));

        return;

    }

}

void ReportWindow::on_radioButton_2_clicked()
{
    ui->groupBox_3->setEnabled(true);
    (ui->startDateEdit->date() > ui->endDateEdit->date()) ? ui->pushButton->setEnabled(false) : ui->pushButton->setEnabled(true);
}

void ReportWindow::on_documentRadioButton_clicked()
{
    ui->groupBox_3->setEnabled(true);
}

void ReportWindow::setAdmin(Admin admin)
{
    this->currentAdmin = admin;
}

void ReportWindow::on_startDateEdit_userDateChanged(const QDate &date)
{
    (ui->startDateEdit->date() > ui->endDateEdit->date()) ? ui->pushButton->setEnabled(false) : ui->pushButton->setEnabled(true);
}

void ReportWindow::on_endDateEdit_userDateChanged(const QDate &date)
{
    (ui->startDateEdit->date() > ui->endDateEdit->date()) ? ui->pushButton->setEnabled(false) : ui->pushButton->setEnabled(true);
}
