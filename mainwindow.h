#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <form.h>
#include <QTableView>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QModelIndexList>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QDebug>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QDate>
#include <QTextCharFormat>
#include <prohil.h>
#include <QTextEdit>
#include <QCompleter>
#include <QSqlQueryModel>
#include <QStyledItemDelegate>
#include <QPainter>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_revert_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_Reg_clicked();

    void receiveData(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password);

    void refreshData(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password);

    void on_pushButton_Vhod_clicked();

    bool authenticateUser(const QString &inputLogin, const QString &inputPassword);


    void on_radioButton_teacher_clicked();

    void on_radioButton_student_clicked();

    void on_pushButton_buy_clicked();

    void on_pushButton_raspis_clicked();

    void on_pushButton_ocenki_clicked();

    void on_pushButton_back_clicked();
    void buyButtonClicked(int row);

    void on_pushButton_otziv_clicked();

    void on_pushButton_profil_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_enter_clicked();

    void handleViewButtonClicked(int row);

    void ocenkaButtonClicked(int row);

    void on_pushButton_ocenka_clicked();

    void put_ocenkaButtonClicked(int row);

    void on_pushButton_red_tabl_clicked();

    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void on_pushButton_clicked();

    void on_comboBox_course_currentTextChanged(const QString &arg1);

    void on_pushButton_otziv_2_clicked();

    void on_radioButton_clicked();



private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    QSqlTableModel* model;
    QTableView *tableView;
    form *formDialog;
    QStandardItemModel *gradesModel;
    QStandardItemModel Model_otz;
    int student_id;
    QTextEdit *textEdit;
    QCalendarWidget *calendarWidget;
    prohil *prohilDialog;
    QString name, login, password, mail, telephoneNumber;
    int id_course = 0;
    int glob_row = 0;
};
#endif // MAINWINDOW_H
