#ifndef PROHIL_H
#define PROHIL_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QPalette>
#include<QDebug>
#include <QCloseEvent>
namespace Ui {
class prohil;
}

class prohil : public QDialog
{
    Q_OBJECT

public:
    explicit prohil(QWidget *parent = nullptr, QString name = "", QString login = "", QString password = "", QString mail = "", QString telephoneNumber = "");
    ~prohil();

private slots:
    void on_pushButton_clicked();
    bool validateEmail();
    void closeEvent(QCloseEvent *event) override;

    void on_pushButton_exit_clicked();


signals:
    void sendDATA(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password);

private:
    Ui::prohil *ui;
    bool red = 0;
    QString old_name, old_password, old_login, old_mail, old_phone;
};

#endif // PROHIL_H
