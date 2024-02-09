#include "functions.h"

void setApplicationConfig()
{

    qDebug() << QStyleFactory::keys();
    //app.setStyle(QStyleFactory::create("Fusion"));
    QApplication::setFont(QFont("Open Sans", 10, QFont::Bold));

}

void setMainStylesheet(QString path, QApplication &app)
{

    QFile styleFile(path);

    styleFile.open(QFile::ReadOnly);

    QString style(styleFile.readAll());
    app.setStyleSheet(style);

    styleFile.close();

}

void setWarningMessageBoxAuth()
{

    QMessageBox messageBox;
    messageBox.setWindowTitle("Ошибка авторизации!");
    messageBox.setText("Неверный пароль! Попробуйте снова!");
    messageBox.setWindowIcon(QIcon());
    messageBox.exec();

}

void checkAuthorizationCorrectInput(QLineEdit *&loginLineEdit, QLineEdit *&passwordLineEdit, QPushButton *&applyPushButton)
{

    if(loginLineEdit->text().isEmpty() || passwordLineEdit->text().isEmpty())
    {
        applyPushButton->setEnabled(false);
        return;
    }
    else
    {
        applyPushButton->setEnabled(true);
    }

    if((loginLineEdit->text().size() <= 5 || loginLineEdit->text().size() >= 21) || (passwordLineEdit->text().size() <= 7 || passwordLineEdit->text().size() >= 21))
    {
        applyPushButton->setEnabled(false);
        return;
    }
    else
    {
        applyPushButton->setEnabled(true);
    }

}

int setWarningMessageBoxDeleteRecord(QString text)
{

    int res = 0;

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon());
    msgBox.setWindowTitle(text);
    msgBox.setText("Підтвердіть видалення!");
    msgBox.setInformativeText("Ок - видалити\nCancel - скасувати");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setDefaultButton(QMessageBox::Ok);
    return res = msgBox.exec();

}
