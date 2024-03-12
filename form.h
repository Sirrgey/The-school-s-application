#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>


namespace Ui {
class form;
}

class form : public QDialog
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr);
    ~form();

private slots:
    void on_pushButton_clicked();
    bool validateEmail();
signals:
    void sendData(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password);

private:
    Ui::form *ui;
};

#endif // FORM_H
