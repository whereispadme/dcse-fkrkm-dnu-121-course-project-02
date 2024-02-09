#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include "functions.h"
#include "headers.h"

#include "admin.h"

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow();

    void closeEvent(QCloseEvent *event);

    void setReportWindowConfig();

    void setAdmin(Admin admin);

signals:
    void sendSignalToMainWindowCloseEvent();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_documentRadioButton_clicked();

    void on_startDateEdit_userDateChanged(const QDate &date);

    void on_endDateEdit_userDateChanged(const QDate &date);

private:
    Ui::ReportWindow *ui;

    QBarSeries *series;
    QChart *chart;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    QHBoxLayout *layout;

    Admin currentAdmin;
    int variable = 0;

};

#endif
