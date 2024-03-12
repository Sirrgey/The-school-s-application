#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include "prohil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);
    db = nullptr;
    if (db != nullptr) {
        db->close();
        QMessageBox::information(this, "Ошибка", "База данных не открыта", QMessageBox::Ok);
    }
    else {
        db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
        QString dbName("postgres");
        QString host("127.0.0.1");
        QString user("postgres");
        QString password("AAAADDDD");
        db->setDatabaseName(dbName);
        db->setHostName(host);
        db->setUserName(user);
        db->setPassword(password);
        db->setPort(5432); // 5433
    }
    if (!db->open()) {
        QMessageBox::warning(this, "Ошибка!", "База данных не открылась!", QMessageBox::Ok);
        delete db;
        db = nullptr;
        return;
    }
    gradesModel = new QStandardItemModel(this);
    ui->pushButton_add->setText("Добавить студента");
    ui->pushButton_remove->setText("Удалить студента");
    ui->frame->hide();


    ui->radioButton_student->setChecked(true);
    model = new QSqlTableModel(this, *db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("students");

    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Игрок"), QHeaderView::ResizeToContents);
    model->setHeaderData(1, Qt::Horizontal, tr("Киллы"), QHeaderView::ResizeToContents);
    model->setHeaderData(2, Qt::Horizontal, tr("Смерти"), QHeaderView::ResizeToContents);
    model->setHeaderData(3, Qt::Horizontal, tr("Помощь"), QHeaderView::ResizeToContents);
    model->setHeaderData(4, Qt::Horizontal, tr("Очки"), QHeaderView::ResizeToContents);
    model->setHeaderData(5, Qt::Horizontal, tr("Очки"), QHeaderView::ResizeToContents);
    ui->tableView->setModel(model);

    prohilDialog = new prohil(this, name, login, password, mail, telephoneNumber);
    formDialog = new form(this);
    //    prohilDialog = new prohil(this);

    ui->lineEdit_login->setText("anna1");
    ui->lineEdit_password->setText("123456");

    calendarWidget = new QCalendarWidget(this);
    calendarWidget->hide();
    ui->tableView_2->hide();


    if (model)
    {
        // Получение количества строк в модели данных
        int rowCount = model->rowCount();

        // Проверка, что количество строк больше 0
        if (rowCount > 0)
        {
            // Вычисление индекса последней строки
            QModelIndex lastIndex = model->index(rowCount - 1, 0);

            // Выбор последней строки в TableView
            ui->tableView->setCurrentIndex(lastIndex);
        }
    }
    ui->tableView->model()->sort(0, Qt::AscendingOrder);
    connect(prohilDialog, &prohil::sendDATA, this, &MainWindow::refreshData);
    connect(formDialog, &form::sendData, this, &MainWindow::receiveData);

    //    connect(prohilDialog, &form::sendData, this, &MainWindow::receiveData);
    ui->pushButton_add->hide();
    ui->pushButton_remove->hide();

    ui->pushButton_save->hide();
    ui->tableView->hide();
    ui->comboBox->hide();
    ui->pushButton_back->hide();
    ui->pushButton_profil->hide();
    ui->textEdit->hide();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
    ui->pushButton_ocenka->hide();
    ui->pushButton_red_tabl->hide();


    ui->groupBox->move(360, 1);
    ui->label_login->move(370, 160);
    ui->label_password->move(370,210);
    ui->lineEdit_login->move(490,160);
    ui->lineEdit_password->move(490,210);
    ui->pushButton_Vhod->move(370, 260);
    ui->pushButton_Reg->move(370, 310);

    ui->label->setStyleSheet("background-color: red; color: white;");
    ui->label_4->setStyleSheet("background-color: blue; color: white;");
    ui->label_6->setStyleSheet("background-color: yellow; color: white;");
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();


    ui->pushButton_buy->hide();
    ui->pushButton_ocenki->hide();
    ui->pushButton_otziv->hide();
    ui->pushButton_otziv_2->hide();
    ui->pushButton_raspis->hide();

    ui->pushButton_raspis->setStyleSheet("QPushButton {"
                                         "    background-color: #4CAF50;"
                                         "    border: none;"
                                         "    color: white;"
                                         "    text-align: center;"
                                         "    text-decoration: none;"
                                         "    font-size: 16px;"
                                         "    border-radius: 12px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "    background-color: white;"
                                         "    color: black;"
                                         "    border: 2px solid #4CAF50;"
                                         "}");
    ui->pushButton_ocenki->setStyleSheet("QPushButton {"
                                         "    background-color: #4CAF50;"
                                         "    border: none;"
                                         "    color: white;"
                                         "    text-align: center;"
                                         "    text-decoration: none;"
                                         "    font-size: 16px;"
                                         "    border-radius: 12px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "    background-color: white;"
                                         "    color: black;"
                                         "    border: 2px solid #4CAF50;"
                                         "}");
    ui->pushButton_otziv->setStyleSheet("QPushButton {"
                                        "    background-color: #4CAF50;"
                                        "    border: none;"
                                        "    color: white;"
                                        "    text-align: center;"
                                        "    text-decoration: none;"
                                        "    font-size: 16px;"
                                        "    border-radius: 12px;"
                                        "}"
                                        "QPushButton:hover {"
                                        "    background-color: white;"
                                        "    color: black;"
                                        "    border: 2px solid #4CAF50;"
                                        "}");
    ui->pushButton_otziv_2->setStyleSheet("QPushButton {"
                                        "    background-color: #4CAF50;"
                                        "    border: none;"
                                        "    color: white;"
                                        "    text-align: center;"
                                        "    text-decoration: none;"
                                        "    font-size: 16px;"
                                        "    border-radius: 12px;"
                                        "}"
                                        "QPushButton:hover {"
                                        "    background-color: white;"
                                        "    color: black;"
                                        "    border: 2px solid #4CAF50;"
                                        "}");
    ui->pushButton_buy->setStyleSheet("QPushButton {"
                                      "    background-color: #4CAF50;"
                                      "    border: none;"
                                      "    color: white;"
                                      "    text-align: center;"
                                      "    text-decoration: none;"
                                      "    font-size: 16px;"
                                      "    border-radius: 12px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "    background-color: white;"
                                      "    color: black;"
                                      "    border: 2px solid #4CAF50;"
                                      "}");
    ui->pushButton->setStyleSheet("QPushButton {"
                                      "    background-color:  #8a2be2; /* Зеленый цвет для фона кнопки */"
                                      "    color: white; /* Белый цвет для текста кнопки */"
                                      "    border: none;"
                                      "    border-radius: 5px;"
                                      "    padding: 10px 20px;"
                                      "}"

                                      "QPushButton:hover {"
                                  "    background-color: #8a2be2;"
                                  "    color: black;"
                                  "    border: 2px solid #a358e8;" /* Цвет кнопки при наведении мыши */);
    ui->pushButton_profil->setStyleSheet("QPushButton {"
                                         "    background-color: #4CAF50;"
                                         "    border: none;"
                                         "    color: white;"
                                         "    text-align: center;"
                                         "    text-decoration: none;"
                                         "    font-size: 16px;"
                                         "    border-radius: 12px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "    background-color: white;"
                                         "    color: black;"
                                         "    border: 2px solid #4CAF50;"
                                         "}");
    ui->pushButton_back->setStyleSheet("QPushButton {"
                                       "    background-color: red;"
                                       "    border: none;"
                                       "    color: white;"
                                       "    text-align: center;"
                                       "    text-decoration: none;"
                                       "    font-size: 16px;"
                                       "    border-radius: 12px;"
                                       "}"
                                       "QPushButton:hover {"
                                       "    background-color: white;"
                                       "    color: black;"
                                       "    border: 2px solid #4CAF50;"
                                       "}");
    ui->comboBox->setStyleSheet("QComboBox {"
                                "    background-color: #4CAF50;"
                                "    border: none;"
                                "    color: white;"
                                "    text-align: center;"
                                "    text-decoration: none;"
                                "    font-size: 16px;"
                                "    border-radius: 12px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: white;"
                                "    color: black;"
                                "    border: 2px solid #4CAF50;"
                                "}");
    ui->comboBox_course->setStyleSheet("QComboBox {"
                                "    background-color: #4CAF50;"
                                "    border: none;"
                                "    color: white;"
                                "    text-align: center;"
                                "    text-decoration: none;"
                                "    font-size: 18px;"
                                "    border-radius: 12px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: white;"
                                "    color: black;"
                                "    border: 2px solid #4CAF50;"
                                "}");
    ui->spinBox_yrok->setStyleSheet(
                "QSpinBox {"
                        "   border: 2px solid #4CAF50; /* Зеленый цвет для рамки */"
                        "   border-radius: 4px;"
                        "   background-color: #FFFFFF; /* Белый цвет для фона */"
                        "   padding: 2px;"
                        "   min-width: 70px;"
                        "}"
                "QSpinBox::up-button, QSpinBox::down-button {"
                "   width: 18px;  /* Устанавливаем ширину стрелок */"
                "   height: 25 px; /* Устанавливаем высоту стрелок */"
                 "   border: 1px solid #4CAF50; /* Зеленый цвет для обводки кнопок вверх и вниз */"
                "QSpinBox::up-arrow, QSpinBox::down-arrow {"
                    "   border: 1px solid #4CAF50; /* Зеленый цвет для обводки стрелок */"
                    "}"

                "}"

                        );
    ui->spinBox_ocenka->setStyleSheet(
                "QSpinBox {"
                        "   border: 2px solid #4CAF50; /* Зеленый цвет для рамки */"
                        "   border-radius: 4px;"
                        "   background-color: #FFFFFF; /* Белый цвет для фона */"
                        "   padding: 2px;"
                        "   min-width: 70px;"
                        "}"
                "QSpinBox::up-button, QSpinBox::down-button {"
                "   width: 18px;  /* Устанавливаем ширину стрелок */"
                "   height: 25 px; /* Устанавливаем высоту стрелок */"
                 "   border: 1px solid #4CAF50; /* Зеленый цвет для обводки кнопок вверх и вниз */"
                "QSpinBox::up-arrow, QSpinBox::down-arrow {"
                    "   border: 1px solid #4CAF50; /* Зеленый цвет для обводки стрелок */"
                    "}"

                "}"

                        );
    ui->pushButton_Vhod->setStyleSheet("QPushButton {"
                                       "    background-color: #4CAF50;"
                                       "    border: none;"
                                       "    color: white;"
                                       "    text-align: center;"
                                       "    text-decoration: none;"
                                       "    font-size: 16px;"
                                       "    border-radius: 12px;"
                                       "}"
                                       "QPushButton:hover {"
                                       "    background-color: white;"
                                       "    color: black;"
                                       "    border: 2px solid #4CAF50;"
                                       "}");
    ui->pushButton_Reg->setStyleSheet("QPushButton {"
                                      "    background-color: #4CAF50;"
                                      "    border: none;"
                                      "    color: white;"
                                      "    text-align: center;"
                                      "    text-decoration: none;"
                                      "    font-size: 16px;"
                                      "    border-radius: 12px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "    background-color: white;"
                                      "    color: black;"
                                      "    border: 2px solid #4CAF50;"
                                      "}");

    ui->lineEdit_login->setStyleSheet("QLineEdit {"
                                      "    border: 2px solid #4CAF50;"
                                      "    border-radius: 10px;"
                                      "    padding: 5px;"
                                      "}");
    ui->lineEdit_password->setStyleSheet("QLineEdit {"
                                         "    border: 2px solid #4CAF50;"
                                         "    border-radius: 10px;"
                                         "    padding: 5px;"
                                         "}");


    ui->label_login->setStyleSheet("QLabel {"
                                   "    color: #4CAF50;"
                                   "    font-size: 18px;"
                                   "}");
    ui->label_password->setStyleSheet("QLabel {"
                                      "    color: #4CAF50;"
                                      "    font-size: 18px;"
                                      "}");



    ui->tableView->setStyleSheet("QTableView {"
                                 "    border: 10px solid #4CAF50;"
                                 "    border-radius: 10px;"
                                 "    background-color: white;"
                                 "}");
    ui->groupBox->setStyleSheet("QGroupBox {"
                                "    border: 2px solid gray;"
                                "    border-radius: 5px;"
                                "    margin-top: 1ex;"
                                "}"
                                "QGroupBox::title {"
                                "    subcontrol-origin: margin;"
                                "    subcontrol-position: top center;"
                                "    padding: 0 3px;"
                                "}");

    ui->radioButton_student->setStyleSheet("QRadioButton {"
                                           "    spacing: 5px;"
                                           "    background-color: #4CAF50;"
                                           "    color: white;"
                                           "    padding: 5px 10px;"
                                           "    border-radius: 5px;"
                                           "}"
                                           "QRadioButton:hover {"
                                           "    background-color: white;"
                                           "    color: black;"
                                           "    border: 2px solid #4CAF50;"
                                           "}");
    ui->radioButton->setStyleSheet("QRadioButton {"
                                           "    spacing: 5px;"
                                           "    background-color: #4CAF50;"
                                           "    color: white;"
                                           "    padding: 5px 10px;"
                                           "    border-radius: 5px;"
                                           "}"
                                           "QRadioButton:hover {"
                                           "    background-color: white;"
                                           "    color: black;"
                                           "    border: 2px solid #4CAF50;"
                                           "}");
    ui->radioButton_teacher->setStyleSheet("QRadioButton {"
                                           "    spacing: 5px;"
                                           "    background-color: #4CAF50;"
                                           "    color: white;"
                                           "    padding: 5px 10px;"
                                           "    border-radius: 5px;"
                                           "}"
                                           "QRadioButton:hover {"
                                           "    background-color: white;"
                                           "    color: black;"
                                           "    border: 2px solid #4CAF50;"
                                           "}");




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveData(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password)
{

    QMessageBox::information(this, "", "Данные передались", QMessageBox::Ok);
    QSqlQuery query;
    query.prepare("INSERT INTO students (name, mail, telephone_number, login, password, student_status) VALUES (:name, :mail, :telephone_number, :login, :password, :student_status)");
    query.bindValue(":name", name);
    query.bindValue(":mail", mail);
    query.bindValue(":telephone_number", telephone_number);
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":student_status", "обучается");


    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Данные успешно добавлены в базу данных");
        ui->pushButton_add->show();
        ui->pushButton_remove->show();

        ui->pushButton_save->show();
        ui->tableView->show();
        ui->comboBox->show();

        ui->groupBox->hide();
        ui->label_login->hide();
        ui->label_password->hide();
        ui->lineEdit_login->hide();
        ui->lineEdit_password->hide();
        ui->pushButton_Vhod->hide();
        ui->pushButton_Reg->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить данные в базу данных: " + query.lastError().text());
    }

}


void MainWindow::on_pushButton_add_clicked()
{
    int row = model->rowCount();
    model->insertRows(row, 1);
    model->setData(model->index(row, 0), "");
    ui->pushButton_remove->setEnabled(true);

}

void MainWindow::on_pushButton_remove_clicked()
{

    if (ui->tableView->currentIndex().row()>=0)
    {
        int row = ui->tableView->currentIndex().row();
        model->removeRows(row,1);
        model->submitAll();
        model->select();
        ui->tableView->setModel(model);
    }
    else if(ui->tableView->currentIndex().row()==0)
    {
        ui->pushButton_remove->setEnabled(false);
    }
    // Проверка наличия модели данных
    if (model)
    {
        // Получение количества строк в модели данных
        int rowCount = model->rowCount();

        // Проверка, что количество строк больше 0
        if (rowCount > 0)
        {
            // Вычисление индекса последней строки
            QModelIndex lastIndex = model->index(rowCount - 1, 0);

            // Выбор последней строки в TableView
            ui->tableView->setCurrentIndex(lastIndex);

        }
    }


    //    selectionModel->select(ui->tableView->model()->index(ui->tableView->model()->rowCount());

}


void MainWindow::on_pushButton_save_clicked()
{
    model->submitAll();
    ui->tableView->model()->sort(0, Qt::AscendingOrder);
}


void MainWindow::on_pushButton_revert_clicked()
{
    model->revertAll();
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    model->setTable(arg1);

    model->select();

    if (arg1=="students")
    {
        model->setHeaderData(0, Qt::Horizontal, "Айди студента");
        model->setHeaderData(1, Qt::Horizontal, "Почта");
        model->setHeaderData(2, Qt::Horizontal, "Номер телефона");
        model->setHeaderData(3, Qt::Horizontal, "Статус студента");
        model->setHeaderData(4, Qt::Horizontal, "Номер покупки");
        model->setHeaderData(5, Qt::Horizontal, "Имя");
        model->setHeaderData(6, Qt::Horizontal, "Логин");
        model->setHeaderData(7, Qt::Horizontal, "Пароль");
    }
    if (arg1=="purchase")
    {
        model->setHeaderData(0, Qt::Horizontal, "Айди покупки");
        model->setHeaderData(1, Qt::Horizontal, "Стоимость покупки");
        model->setHeaderData(2, Qt::Horizontal, "Дата покупки");

    }
    if (arg1=="reviews")
    {
        model->setHeaderData(0, Qt::Horizontal, "Айди отзыва");
        model->setHeaderData(1, Qt::Horizontal, "Айди студента");
        model->setHeaderData(2, Qt::Horizontal, "Айди курса");
        model->setHeaderData(3, Qt::Horizontal, "Отзыв");
        model->setHeaderData(4, Qt::Horizontal, "Дата написания отзыва");
    }
    if (arg1=="courses")
    {
        model->setHeaderData(0, Qt::Horizontal, "Айди курса");
        model->setHeaderData(1, Qt::Horizontal, "Цена");
        model->setHeaderData(2, Qt::Horizontal, "Название");
        model->setHeaderData(3, Qt::Horizontal, "Дата начала");
        model->setHeaderData(4, Qt::Horizontal, "Количество уроков");
    }
    if (arg1=="teachers")
    {
        model->setHeaderData(0, Qt::Horizontal, "Айди учителя");
        model->setHeaderData(1, Qt::Horizontal, "Имя учителя");
        model->setHeaderData(2, Qt::Horizontal, "Паспортные данные");
        model->setHeaderData(3, Qt::Horizontal, "Номер телефона");
        model->setHeaderData(4, Qt::Horizontal, "Дата рождения");
        model->setHeaderData(5, Qt::Horizontal, "Фото");
        model->setHeaderData(6, Qt::Horizontal, "Статус");
    }


//    }
    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // Устанавливаем режим изменения размера ячеек по содержимому
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->model()->sort(0, Qt::AscendingOrder);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);

    if (model)
    {
        // Получение количества строк в модели данных
        int rowCount = model->rowCount();

        // Проверка, что количество строк больше 0
        if (rowCount > 0)
        {
            // Вычисление индекса последней строки
            QModelIndex lastIndex = model->index(rowCount - 1, 0);

            // Выбор последней строки в TableView
            ui->tableView->setCurrentIndex(lastIndex);
        }
    }
    if (arg1 == "students")
        ui->pushButton_add->setText("Добавить студента");
    else if (arg1 == "assessment")
        ui->pushButton_add->setText("Добавить оценку");
    else if (arg1 == "purchase")
        ui->pushButton_add->setText("Добавить покупку");
    else if (arg1 == "reviews")
        ui->pushButton_add->setText("Добавить комментарий");
    else if (arg1 == "teachers")
        ui->pushButton_add->setText("Добавить учителя");
    else if (arg1 == "courses")
        ui->pushButton_add->setText("Добавить курс");

    if (arg1 == "students")
        ui->pushButton_remove->setText("Удалить студента");
    else if (arg1 == "assessment")
        ui->pushButton_remove->setText("Удалить оценку");
    else if (arg1 == "purchase")
        ui->pushButton_remove->setText("Удалить покупку");
    else if (arg1 == "reviews")
        ui->pushButton_remove->setText("Удалить комментарий");
    else if (arg1 == "teachers")
        ui->pushButton_remove->setText("Удалить учителя");
    else if (arg1 == "courses")
        ui->pushButton_remove->setText("Удалить курс");



}


void MainWindow::on_pushButton_Reg_clicked()
{
    formDialog->show();
}




void MainWindow::on_pushButton_Vhod_clicked()
{
    if(ui->lineEdit_login->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка!", "Введите логин", QMessageBox::Ok);

    }
    else if(ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка!", "Введите пароль", QMessageBox::Ok);
    }

    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if (ui->radioButton_student->isChecked())
    {

        if(authenticateUser(login, password))
        {


            ui->groupBox->hide();
            ui->label_login->hide();
            ui->label_password->hide();
            ui->lineEdit_login->hide();
            ui->lineEdit_password->hide();
            ui->pushButton_Vhod->hide();
            ui->pushButton_Reg->hide();
            on_pushButton_raspis_clicked();
            ui->pushButton_back->show();
            ui->pushButton_profil->show();
            ui->pushButton_ocenka->hide();



            ui->tableView->show();
            ui->pushButton_save->hide();
            ui->pushButton_add->hide();
            ui->pushButton_remove->hide();

            ui->comboBox->hide();
            ui->pushButton_buy->show();
            ui->pushButton_ocenki->show();
            ui->pushButton_otziv->show();
            ui->pushButton_otziv_2->show();
            ui->pushButton_raspis->show();
        }
        else{
            QMessageBox::information(this, "", "Неверный логин или пароль", QMessageBox::Ok);
            ui->lineEdit_login->clear();
            ui->lineEdit_password->clear();
        }

    }
    else if(ui->radioButton_teacher->isChecked())
    {
        if(login =="admin" and password == "00000")
        {
            ui->groupBox->hide();
            ui->label_login->hide();
            ui->label_password->hide();
            ui->lineEdit_login->hide();
            ui->lineEdit_password->hide();
            ui->pushButton_Vhod->hide();
            ui->pushButton_Reg->hide();
            ui->pushButton_back->show();
            ui->pushButton_ocenka->hide();




            model = new QSqlTableModel(this, *db);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("students");
            model->select();
            ui->tableView->setModel(model);

            ui->pushButton_add->show();
            ui->pushButton_remove->show();

            ui->pushButton_save->show();
            ui->tableView->show();
            ui->comboBox->show();
        }
        else{
            QMessageBox::information(this, "", "Неверный логин или пароль", QMessageBox::Ok);
            ui->lineEdit_login->clear();
            ui->lineEdit_password->clear();
        }

    }
    else if(ui->radioButton->isChecked())
    {
        if(login =="tc" and password == "0")
        {
//            ui->pushButton_ocenka->setGeometry(10,60,221,51);
//            ui->pushButton_ocenka->show();
            ui->groupBox->hide();
            ui->label_login->hide();
            ui->label_password->hide();
            ui->lineEdit_login->hide();
            ui->lineEdit_password->hide();
            ui->pushButton_Vhod->hide();
            ui->pushButton_Reg->hide();
            ui->pushButton_back->show();

            model = new QSqlTableModel(this, *db);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("students");
            model->select();
            ui->tableView->setModel(model);

            ui->pushButton_add->show();
            ui->pushButton_remove->show();

            ui->pushButton_save->show();
            ui->tableView->show();
            ui->comboBox->show();
            on_pushButton_ocenka_clicked();
        }
        else{
            QMessageBox::information(this, "", "Неверный логин или пароль", QMessageBox::Ok);
            ui->lineEdit_login->clear();
            ui->lineEdit_password->clear();
        }
  }
}

bool MainWindow::authenticateUser(const QString &inputLogin, const QString &inputPassword)
{

    // Создаем SQL-запрос для поиска пользователя по логину и паролю
    QSqlQuery query;
    query.prepare("SELECT login, password, id_student FROM students WHERE login = :login AND password = :password");
    query.bindValue(":login", inputLogin);
    query.bindValue(":password", inputPassword);


    // Выполняем запрос
    if (query.exec() && query.next()) {
        student_id = query.value("id_student").toInt();
        qDebug() << student_id;
        // Если пользователь найден, возвращаем true
        return true;
    }

    // Если запрос не выполнен или пользователь не найден, возвращаем false
    return false;
}


void MainWindow::on_radioButton_teacher_clicked()
{
    ui->pushButton_Reg->hide();
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
}


void MainWindow::on_radioButton_student_clicked()
{
    ui->pushButton_Reg->show();
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
}


void MainWindow::on_pushButton_buy_clicked()
{
    ui->textEdit->hide();
    ui->tableView->setEnabled(true);
    ui->textEdit->clear();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
    Model_otz.clear();  // Очищаем всю модель
    Model_otz.setRowCount(0);  // Устанавливаем количество строк в 0
    Model_otz.setColumnCount(0);  // Устанавливаем количество столбцов в 0
    ui->tableView->setModel(&Model_otz);
    calendarWidget->hide();
    ui->tableView->show();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();
    ui->tableView->setModel(&Model_otz);


    Model_otz.setHorizontalHeaderLabels(QStringList() << "Не купленные предметы" << "Цена" <<"Действие");

    QSqlQuery query;
    query.prepare("SELECT title, price "
                  "FROM courses "
                  "WHERE id_courses NOT IN ( "
                  "SELECT c.id_courses "
                  "FROM courses c "
                  "JOIN students_courses sc ON c.id_courses = sc.id_courses "
                  "JOIN students s ON sc.id_student = s.id_student "
                  "WHERE s.id_student = :student_id);");
    query.bindValue(":student_id", student_id);

    if (query.exec()) {
        while (query.next()) {
            QString title = query.value("title").toString();
            QString price = query.value("price").toString();
            qDebug() << title <<""<< price;
            QList<QStandardItem*> foundRows = Model_otz.findItems(title);
            foundRows = Model_otz.findItems(price);
            int row;
            if (foundRows.isEmpty()) {
                Model_otz.appendRow(new QStandardItem(title));
                row = Model_otz.rowCount() - 1;
            } else {
                row = foundRows[0]->row();
            }

            QPushButton *viewButton = new QPushButton("Купить курс");
            connect(viewButton, &QPushButton::clicked, this, [=]() {
                buyButtonClicked(row);
            });

            // Устанавливаем элемент в модель
            Model_otz.setItem(row, 1, new QStandardItem(price));
            Model_otz.setItem(row, 2, new QStandardItem());
            ui->tableView->setIndexWidget(Model_otz.index(row, 2), viewButton);
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    // Устанавливаем модель для QTableView
    ui->tableView->setModel(&Model_otz);

    // Автоматическое изменение размеров столбцов и строк
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


void MainWindow::on_pushButton_raspis_clicked()
{
    ui->textEdit->hide();
    ui->tableView->setEnabled(true);
    ui->textEdit->clear();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
    calendarWidget->hide();
    ui->tableView->show();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();


    gradesModel->setHorizontalHeaderLabels(QStringList()<<"Предмет " << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14");
    QSqlQuery query;
    query.prepare("SELECT a.id_course, c.title, a.day, a.assessment "
                  "FROM assessment a "
                  "JOIN courses c ON a.id_course = c.id_courses "
                  "WHERE id_student = :id_student;");
    query.bindValue(":id_student", student_id);
    qDebug() << student_id;

    if (query.exec())
    {
        while (query.next()) {
            QString title = query.value("title").toString();
            int day = query.value("day").toInt();
            //               int lessonNumber = query.value("day").toInt();
            QString assessment = query.value("assessment").toString();

            // Находим индекс столбца и строку в соответствии с днем и номером урока
            /*int row = gradesModel->findItems(title).first()->row();*/ // Предполагается, что есть столбец с именем курса в модели

            QList<QStandardItem*> foundRows = gradesModel->findItems(title);
            int row;
            if (foundRows.isEmpty()) {
                gradesModel->appendRow(new QStandardItem(title));
                row = gradesModel->rowCount()-1;
            }
            else {

                row = foundRows[0]->row();
            }
            QStandardItem* item = new QStandardItem(assessment);
            if (assessment == "5") {
                item->setBackground(QBrush(Qt::green));  // Цвет фона для оценки "5"
            } else if (assessment == "4") {
                item->setBackground(QBrush(Qt::yellow));  // Цвет фона для оценки "4"
            } else if (assessment == "3"){
                // Остальные оценки могут иметь другой цвет фона
                item->setBackground(QBrush(QColor(252, 102, 0)));
            }
            else if (assessment == "2") {
                item->setBackground(QBrush(Qt::red));  // Цвет фона для оценки "2"
            }
            else if (assessment == "1") {
                item->setBackground(QBrush(Qt::red));  // Цвет фона для оценки "1"
            }
            else{
                item->setBackground(QBrush(Qt::white));
            }
            //            if (assessment.isEmpty()) {
            //                item = new QStandardItem(title);
            //            } else {
            //                item = new QStandardItem(assessment);
            //            }

            gradesModel->setItem(row, day, item);


            // Устанавливаем оценку в соответствующую ячейку
            //               gradesModel->setItem(row, column, new QStandardItem(day + ": " + assessment));
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    // Устанавливаем модель для QTableView
    ui->tableView->setModel(gradesModel);

    // Настроим QTableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}


void MainWindow::on_pushButton_ocenki_clicked()
{
    ui->textEdit->hide();
    ui->tableView->setEnabled(true);
    ui->textEdit->clear();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
    ui->tableView->hide();
    QString styleSheet = "QCalendarWidget QAbstractItemView {"
                         "    spacing: 10px;"  // Отступ между ячейками в календаре
            "}";
    calendarWidget->setStyleSheet(styleSheet);

    QSqlQuery query;
    query.prepare(  "SELECT lessons.start_date, lessons.id_courses "
                    "FROM students "
                    "JOIN students_courses ON students.id_student = students_courses.id_student "
                    "JOIN courses ON students_courses.id_courses = courses.id_courses "
                    "JOIN lessons ON courses.id_courses = lessons.id_courses "
                    "WHERE students.id_student = :id_student;");
    query.bindValue(":id_student", student_id);
    qDebug() << "222";


    if (query.exec()) {
        while (query.next()) {
            QString dateString = query.value(0).toString();
            QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
            QString course = query.value(1).toString();
            qDebug() << course;

            // Устанавливаем формат для каждой даты
            QTextCharFormat lessonFormat;
            if (course == "1")
            {
                ui->label_3->show();
                ui->label_4->show();
                lessonFormat.setBackground(Qt::blue);
                calendarWidget->setDateTextFormat(date, lessonFormat);
                calendarWidget->setCurrentPage(date.year(), date.month());
            }
            else if(course == "2")
            {
                ui->label_5->show();
                ui->label_6->show();
                lessonFormat.setBackground(Qt::yellow);
                calendarWidget->setDateTextFormat(date, lessonFormat);
                calendarWidget->setCurrentPage(date.year(), date.month());
            }
            else if(course == "3")
            {
                ui->label->show();
                ui->label_2->show();
                lessonFormat.setBackground(Qt::red);
                calendarWidget->setDateTextFormat(date, lessonFormat);
                calendarWidget->setCurrentPage(date.year(), date.month());
            }

            //        QTextCharFormat lessonFormat1;
            //        lessonFormat1.setBackground(Qt::blue);
            //        calendarWidget->setDateTextFormat(lessonDate1, lessonFormat1)
        }

        //    QString dateString = "2023-09-01";
        //    QDate lessonDate = QDate::fromString(dateString, "yyyy-MM-dd");

        int x = 250;       // ваше желаемое положение по горизонтали
        int y = 60;       // ваше желаемое положение по вертикали
        calendarWidget->setGeometry(x, y, 550, 550);
        calendarWidget->show();
    }
    else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
}


void MainWindow::on_pushButton_back_clicked()
{
    ui->groupBox->show();
    ui->label_login->show();
    ui->label_password->show();
    ui->lineEdit_login->show();
    ui->lineEdit_password->show();
    ui->pushButton_Vhod->show();
    ui->pushButton_Reg->show();
    calendarWidget->hide();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();
    gradesModel->clear();
    ui->pushButton_back->hide();
    ui->pushButton_save->hide();
    ui->pushButton_remove->hide();
    ui->pushButton_add->hide();
    ui->comboBox->hide();
    ui->pushButton_profil->hide();
    ui->textEdit->hide();
    ui->pushButton_enter->hide();
    ui->pushButton_cancel->hide();
    ui->tableView->setEnabled(true);
    ui->pushButton_ocenka->hide();
    ui->pushButton_red_tabl->hide();
    ui->tableView_2->hide();
    ui->frame->hide();

    Model_otz.clear();  // Очищаем всю модель
    Model_otz.setRowCount(0);  // Устанавливаем количество строк в 0
    Model_otz.setColumnCount(0);  // Устанавливаем количество столбцов в 0
    ui->tableView->setModel(&Model_otz);




    int year = 2023;
    int month = 9;

    QDate startDate(year, month, 1);
    QDate endDate(year, month, startDate.daysInMonth());

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        calendarWidget->setDateTextFormat(date, QTextCharFormat());
    }


    ui->pushButton_back->hide();
    ui->tableView->hide();
    ui->pushButton_buy->hide();
    ui->pushButton_ocenki->hide();
    ui->pushButton_otziv->hide();
    ui->pushButton_otziv_2->hide();
    ui->pushButton_raspis->hide();
}


void MainWindow::on_pushButton_otziv_clicked()
{

    Model_otz.clear();  // Очищаем всю модель
    Model_otz.setRowCount(0);  // Устанавливаем количество строк в 0
    Model_otz.setColumnCount(0);  // Устанавливаем количество столбцов в 0
    ui->tableView->setModel(&Model_otz);
    calendarWidget->hide();
    ui->tableView->show();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();
    ui->tableView->setModel(&Model_otz);


    Model_otz.setHorizontalHeaderLabels(QStringList() << "Ваши предметы" << "Действие");

    QSqlQuery query;
    query.prepare("SELECT title, id_courses "
                  "FROM courses "
                  "WHERE id_courses IN ( "
                  "SELECT c.id_courses "
                  "FROM courses c "
                  "JOIN students_courses sc ON c.id_courses = sc.id_courses "
                  "JOIN students s ON sc.id_student = s.id_student "
                  "WHERE s.id_student = :id_student);");
    query.bindValue(":id_student", student_id);

    if (query.exec()) {
        while (query.next()) {
            QString title = query.value("title").toString();
            QList<QStandardItem*> foundRows = Model_otz.findItems(title);
            int row;
            if (foundRows.isEmpty()) {
                Model_otz.appendRow(new QStandardItem(title));
                row = Model_otz.rowCount() - 1;
            } else {
                row = foundRows[0]->row();
            }

            QPushButton *viewButton = new QPushButton("Написать отзыв");
            connect(viewButton, &QPushButton::clicked, this, [=]() {
                handleViewButtonClicked(row);
            });

            // Устанавливаем элемент в модель
            Model_otz.setItem(row, 1, new QStandardItem());
            ui->tableView->setIndexWidget(Model_otz.index(row, 1), viewButton);
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    // Устанавливаем модель для QTableView
    ui->tableView->setModel(&Model_otz);

    // Настроим QTableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::handleViewButtonClicked(int row)
{
    qDebug() << "Клик в QTableView. Строка:" << row << "Столбец: 1";
    QModelIndex index = Model_otz.index(row, 0);
    QString cellText = index.isValid() ? index.data().toString() : "";
     qDebug() << cellText;
     ui->tableView->setEnabled(false);

    QSqlQuery query;
    query.prepare("SELECT id_courses FROM courses WHERE title = :title ");
    query.bindValue(":title", cellText);

    if (query.exec() && query.next()) {
        id_course = query.value("id_courses").toInt();
        qDebug() << id_course;
    }

    ui->textEdit->show();
//    ui->tableView->setEnabled(false);
    ui->textEdit->setGeometry(250, 360, 581, 181);
    ui->pushButton_cancel->show();
    ui->pushButton_enter->show();
}


void MainWindow::buyButtonClicked(int row)
{

    QModelIndex index = Model_otz.index(row, 0);
    QString cellText = index.isValid() ? index.data().toString() : "";
    qDebug() << cellText;

    QSqlQuery query;
    query.prepare("SELECT id_courses FROM courses WHERE title = :title ");
    query.bindValue(":title", cellText);

    if (query.exec() && query.next()) {
        id_course = query.value("id_courses").toInt();
        qDebug() << id_course;
    }
    QSqlQuery query1;
    query1.prepare("INSERT INTO students_courses (id_student, id_courses) VALUES (:id_student, :id_courses)");
    query1.bindValue(":id_student", student_id);
    query1.bindValue(":id_courses", id_course);

    if (query1.exec()) {
        qDebug() << "Данные покупок успешно обновлены";
    } else {
        qDebug() << "Ошибка обновления данных покупок:" << query1.lastError().text();
    }
    on_pushButton_buy_clicked();


}


void MainWindow::on_pushButton_profil_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT login, password, telephone_number, mail, name "
                  "FROM students "
                  "WHERE students.id_student = :id_student;");
    query.bindValue(":id_student", student_id);
    if (query.exec()) {
        if (query.next()) {
            QString login = query.value("login").toString();
            QString password = query.value("password").toString();
            QString telephoneNumber = query.value("telephone_number").toString();
            QString mail = query.value("mail").toString();
            QString name = query.value("name").toString();
            prohilDialog = new prohil(this, name, login, password, mail, telephoneNumber);
            prohilDialog->setWindowTitle("Профиль");
            prohilDialog->setModal(true);
            prohilDialog->show();

        } else {
            qDebug() << "Запрос вернул 0 строк.";
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
    connect(prohilDialog, &prohil::sendDATA, this, &MainWindow::refreshData);



}


void MainWindow::refreshData(const QString &name, const QString &mail, const QString &telephone_number, const QString &login, const QString &password)
{
    QSqlQuery query;
    query.prepare("UPDATE students SET name = :name, mail = :mail, telephone_number = :telephone_number, login = :login, password = :password "
                  "WHERE id_student = :id_student");
    query.bindValue(":id_student", student_id);
    query.bindValue(":name", name);
    query.bindValue(":mail", mail);
    query.bindValue(":telephone_number", telephone_number);
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":student_status", "обучается");


    if (query.exec()) {
        qDebug() << "Данные студента успешно обновлены";
    } else {
        qDebug() << "Ошибка обновления данных студента:" << query.lastError().text();
    }
}


void MainWindow::on_pushButton_cancel_clicked()
{
    ui->textEdit->hide();
    ui->tableView->setEnabled(true);
    ui->textEdit->clear();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
}


void MainWindow::on_pushButton_enter_clicked()// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    QString text_reviews = ui->textEdit->toPlainText();
    int length = text_reviews.length();
    if (length > 100)
    {
        QMessageBox::warning(this, "", "Ваш комментарий слишком длинный", QMessageBox::Ok);
    }
    else if (length == 0)
    {
        QMessageBox::warning(this, "", "Нельзя отправить пустой отзыв", QMessageBox::Ok);
    }
    else
    {
        QSqlQuery query;
        query.prepare("INSERT INTO reviews (id_student, id_course, text_reviews, date_writing) VALUES (:id_student, :id_course, :text_reviews, :date_writing)");
        query.bindValue(":id_student", student_id);
        query.bindValue(":id_course", id_course);
        query.bindValue(":text_reviews", text_reviews);
        query.bindValue(":date_writing", "2023-09-21");

        if (query.exec()) {
            qDebug() << "Данные отзывов успешно обновлены";
        } else {
            qDebug() << "Ошибка обновления данных отзывов:" << query.lastError().text();
        }
        ui->textEdit->hide();
        ui->tableView->setEnabled(true);
        ui->textEdit->clear();
        ui->pushButton_cancel->hide();
        ui->pushButton_enter->hide();

    }

}


void MainWindow::on_pushButton_ocenka_clicked()
{
    ui->pushButton_add->hide();
    ui->pushButton_remove->hide();
    ui->pushButton_save->hide();

    ui->comboBox->hide();
    QSqlQueryModel *completerModel = new QSqlQueryModel(this);

    // Выполняем запрос к базе данных для поиска подстрок в поле name
    QString queryStr = "SELECT name FROM students WHERE LOWER(name) LIKE :search";
    QSqlQuery query("SELECT name FROM students WHERE LOWER(name) LIKE :search");
    query.prepare(queryStr);

    // Устанавливаем параметр для поиска
//    query.bindValue(":search", "%" + ui->lineEdit->text().toLower() + "%");

    // Выполняем запрос
    if (query.exec()) {
        completerModel->setQuery(query);
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    // Создаем автодополнитель и устанавливаем модель запроса
//    QCompleter *completer = new QCompleter(completerModel, this);

    // Устанавливаем поле, которое будет автодополняться (например, lineEdit)
//    ui->lineEdit->setCompleter(completer);


    ui->tableView->setModel(&Model_otz);
    Model_otz.setHorizontalHeaderLabels(QStringList() << "Ученики" << "Действие"<< "Действие");

    QSqlQuery query1;
    query1.prepare("SELECT name FROM students");

    if (query1.exec()) {
        while (query1.next()) {
            QString title = query1.value("name").toString();
            QList<QStandardItem*> foundRows = Model_otz.findItems(title);
            int row;
            if (foundRows.isEmpty()) {
                Model_otz.appendRow(new QStandardItem(title));
                row = Model_otz.rowCount() - 1;
            } else {
                row = foundRows[0]->row();
            }

            QPushButton *viewButton = new QPushButton("Посмотреть оценки");
            connect(viewButton, &QPushButton::clicked, this, [=]() {
                ocenkaButtonClicked(row);

            });

            QPushButton *Button_ocenki = new QPushButton("Поставить оценку");
            connect(Button_ocenki, &QPushButton::clicked, this, [=]() {
                put_ocenkaButtonClicked(row);

            });

            // Устанавливаем элемент в модель
            Model_otz.setItem(row, 1, new QStandardItem());
            ui->tableView->setIndexWidget(Model_otz.index(row, 1), viewButton);

            Model_otz.setItem(row, 2, new QStandardItem());
            ui->tableView->setIndexWidget(Model_otz.index(row, 2), Button_ocenki);

        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query1.lastError().text();
    }

    // Устанавливаем модель для QTableView
    ui->tableView->setModel(&Model_otz);

    // Настроим QTableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);



}
void MainWindow::put_ocenkaButtonClicked(int row)
{
    ui->frame->show();
    ocenkaButtonClicked(row);
    glob_row = row;
    qDebug() << "Клик в QTableView. Строка:" << row << "Столбец: 2";
    QModelIndex index = Model_otz.index(row, 0);
    QString cellText = index.isValid() ? index.data().toString() : "";
     qDebug() << cellText;
     QSqlQuery query1;
     query1.prepare("SELECT DISTINCT c.title FROM courses c "
                    "JOIN students_courses sc ON c.id_courses = sc.id_courses "
                    "JOIN students s ON sc.id_student = s.id_student "
                    "WHERE s.name = :name");
     query1.bindValue(":name", cellText);

     if (query1.exec()) {
             // Очищаем предыдущие значения в комбо-боксе
             ui->comboBox_course->clear();

             // Заполняем комбо-бокс значениями из базы данных
             while (query1.next()) {
                 QString courseTitle = query1.value("title").toString();
                 ui->comboBox_course->addItem(courseTitle);
             }
         } else {
             qDebug() << "Ошибка выполнения запроса:" << query1.lastError().text();
             // Обработка ошибки выполнения запроса
         }
     QString course = ui->comboBox_course->currentText();
     if (course == "")
     {
         ui->comboBox_course->addItem("Нет предметов");
     }
     query1.prepare("SELECT id_student "
                    "FROM students "
                    "WHERE name = :name;");
     query1.bindValue(":name", cellText);
     if (query1.exec()) {
         while (query1.next()) {
             student_id = query1.value("id_student").toInt();
              qDebug() << student_id;
         }


         } else {
             qDebug() << "Ошибка выполнения запроса:" << query1.lastError().text();
             // Обработка ошибки выполнения запроса
         }
}

void MainWindow::on_pushButton_red_tabl_clicked()
{
    ui->comboBox->show();
    ui->pushButton_add->show();
    ui->pushButton_remove->show();
    ui->pushButton_save->show();

    ui->frame->hide();
    ui->tableView_2->hide();

    model = new QSqlTableModel(this, *db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("students");

//    ui->tableView_team1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void MainWindow::ocenkaButtonClicked(int row)
{
    // Устанавливаем модель для QTableView
    glob_row = row;
    gradesModel->clear();  // Очищаем всю модель
    gradesModel->setRowCount(0);  // Устанавливаем количество строк в 0
    gradesModel->setColumnCount(0);
    ui->tableView_2->show();
    qDebug() << "Клик в QTableView. Строка:" << row << "Столбец: 1";
    QModelIndex index = Model_otz.index(row, 0);
    QString cellText = index.isValid() ? index.data().toString() : "";
     qDebug() << cellText;
     ui->tableView->setEnabled(false);

    QSqlQuery query;
    query.prepare("SELECT id_student FROM students WHERE name = :name ");
    query.bindValue(":name", cellText);

    if (query.exec() && query.next()) {
        student_id = query.value("id_student").toInt();
        qDebug() << student_id;
    }

    ui->textEdit->hide();
    ui->tableView->setEnabled(true);
    ui->textEdit->clear();
    ui->pushButton_cancel->hide();
    ui->pushButton_enter->hide();
    calendarWidget->hide();
    ui->tableView->show();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();


    gradesModel->setHorizontalHeaderLabels(QStringList()<<"Предмет " << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14");
    QSqlQuery query1;
    query1.prepare("SELECT a.id_course, c.title, a.day, a.assessment "
                  "FROM assessment a "
                  "JOIN courses c ON a.id_course = c.id_courses "
                  "WHERE id_student = :id_student "
                   "ORDER BY a.id_assessment DESC "); // !!!!!!!!!!!!
    query1.bindValue(":id_student", student_id);

    connect(gradesModel, &QStandardItemModel::dataChanged, this, &MainWindow::onDataChanged);

    if (query1.exec())
    {
        while (query1.next()) {
            QString title = query1.value("title").toString();
            int day = query1.value("day").toInt();
            //               int lessonNumber = query.value("day").toInt();
            QString assessment = query1.value("assessment").toString();
            QList<QStandardItem*> foundRows = gradesModel->findItems(title);
            int row;
            if (foundRows.isEmpty()) {
                gradesModel->appendRow(new QStandardItem(title));
                row = gradesModel->rowCount()-1;
            }
            else {

                row = foundRows[0]->row();
            }
            QStandardItem* item = new QStandardItem(assessment);
            if (assessment == "5") {
                item->setBackground(QBrush(Qt::green));  // Цвет фона для оценки "5"
            } else if (assessment == "4") {
                item->setBackground(QBrush(Qt::yellow));  // Цвет фона для оценки "4"
            } else if (assessment == "3"){
                // Остальные оценки могут иметь другой цвет фона
                item->setBackground(QBrush(QColor(252, 102, 0)));
            }
            else if (assessment == "2") {
                item->setBackground(QBrush(Qt::red));  // Цвет фона для оценки "2"
            }
            else if (assessment == "1") {
                item->setBackground(QBrush(Qt::red));  // Цвет фона для оценки "1"
            }
            else{
                item->setBackground(QBrush(Qt::white));
            }
            //            if (assessment.isEmpty()) {
            //                item = new QStandardItem(title);
            //            } else {
            //                item = new QStandardItem(assessment);
            //            }

            gradesModel->setItem(row, day, item);


        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query1.lastError().text();
    }

    ui->tableView_2->setGeometry(250,340,581,261);
    // Устанавливаем модель для QTableView
    ui->tableView_2->setModel(gradesModel);

    // Настроим QTableView
//    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //       ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->resizeColumnsToContents();

    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);


}


void MainWindow::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QModelIndex index = gradesModel->index(glob_row, 0);
    QString cellText = index.isValid() ? index.data().toString() : "";
    if (topLeft.isValid() && bottomRight.isValid()) {
        int row = topLeft.row();
        int column = topLeft.column();
        QString newData = gradesModel->data(topLeft).toString();

        // Проверка на допустимые значения (цифры от 1 до 5)
        bool isValidData = false;
        int numericValue = newData.toInt(&isValidData);

        if ((isValidData && numericValue >= 1 && numericValue <= 5) || newData.isEmpty()) {
            qDebug() << "Изменены данные в ячейке. Строка:" << row << "Столбец:" << column;
            qDebug() << "Новое значение:" << newData;

            // Ваш код для обработки измененных данных
        } else {
            // Если введены недопустимые значения, вы можете проигнорировать изменения
            // или выполнить какие-то дополнительные действия.
            qDebug() << "Введены недопустимые значения в ячейке. Строка:" << row << "Столбец:" << column;
            qDebug() << "Новое значение:" << newData;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO students (name, mail, telephone_number, login, password, student_status) VALUES (:name, :mail, :telephone_number, :login, :password, :student_status)");
        query.bindValue(":name", name);
        query.bindValue(":id_student", student_id);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int id_course = 0;
    int ocenka = ui->spinBox_ocenka->value();
    int yrok = ui->spinBox_yrok->value();
    QString course = ui->comboBox_course->currentText();
    int id_teacher = 1;
    QSqlQuery query;
    if (course != "Нет предметов")
    {

        query.prepare("SELECT id_courses FROM courses WHERE title = :title ");
        query.bindValue(":title", course);

        if (query.exec() && query.next()) {
            id_course = query.value("id_courses").toInt();
            qDebug() << id_course;
        }
        query.prepare("INSERT INTO assessment (id_student, id_teacher, assessment, day, id_course) VALUES (:id_student, :id_teacher, :assessment, :day, :id_course)");
        query.bindValue(":id_teacher", id_teacher);
        query.bindValue(":id_student", student_id);
        query.bindValue(":assessment", ocenka);
        query.bindValue(":day", yrok);
        query.bindValue(":id_course", id_course);

        if (query.exec()) {
            QMessageBox::information(this, "Успех", "Данные успешно добавлены в базу данных");

        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить данные в базу данных: " + query.lastError().text());
        }
     }
     else
    {
        QMessageBox::warning(this, "Ошибка", "У ученика нет купленных предметов");
    }



}


void MainWindow::on_comboBox_course_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Нет предметов")
    {
        ui->comboBox_course->setStyleSheet("QComboBox {"
                                    "    background-color: #ff0000;"
                                    "    border: none;"
                                    "    color: white;"
                                    "    text-align: center;"
                                    "    text-decoration: none;"
                                    "    font-size: 16px;"
                                    "    border-radius: 12px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "    background-color: white;"
                                    "    color: black;"
                                    "    border: 2px solid #4CAF50;"
                                    "}");
    }
    else{
        ui->comboBox_course->setStyleSheet("QComboBox {"
                                    "    background-color: #4CAF50;"
                                    "    border: none;"
                                    "    color: white;"
                                    "    text-align: center;"
                                    "    text-decoration: none;"
                                    "    font-size: 16px;"
                                    "    border-radius: 12px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "    background-color: white;"
                                    "    color: black;"
                                    "    border: 2px solid #4CAF50;"
                                    "}");
    }
}

void MainWindow::on_pushButton_otziv_2_clicked()
{
    Model_otz.clear();  // Очищаем всю модель
    Model_otz.setRowCount(0);  // Устанавливаем количество строк в 0
    Model_otz.setColumnCount(0);  // Устанавливаем количество столбцов в 0
    ui->tableView->setModel(&Model_otz);
    calendarWidget->hide();
    ui->tableView->show();
    ui->label_6->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label->hide();
    ui->tableView->setModel(&Model_otz);





    Model_otz.setHorizontalHeaderLabels(QStringList() << "Ученики" << "Предмет"<<"Комментарий");

    QSqlQuery query;
    query.prepare("SELECT students.name AS student_name, courses.title AS course_title, reviews.text_reviews "
                  "FROM reviews "
                  "INNER JOIN students ON reviews.id_student = students.id_student "
                  "INNER JOIN courses ON reviews.id_course = courses.id_courses;");

    if (query.exec()) {
        while (query.next()) {
            QString title = query.value("student_name").toString();
            QString price = query.value("course_title").toString();
            QString comm = query.value("text_reviews").toString();
            QList<QStandardItem*> foundRows = Model_otz.findItems(title);
            foundRows = Model_otz.findItems(price);
            foundRows = Model_otz.findItems(comm);
            int row;
            if (foundRows.isEmpty()) {
                Model_otz.appendRow(new QStandardItem(title));
                row = Model_otz.rowCount() - 1;
            } else {
                row = foundRows[0]->row();
            }


            // Устанавливаем элемент в модель
            ui->tableView->setRowHeight(row, 60);
            Model_otz.setItem(row, 1, new QStandardItem(price));
            QStandardItem* commentItem = new QStandardItem(comm);
            commentItem->setTextAlignment(Qt::AlignCenter);
            commentItem->setFlags(commentItem->flags() ^ Qt::ItemIsEditable);

            Model_otz.setItem(row, 2, commentItem);



        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    // Настроим QTableView
    ui->tableView->setWordWrap(true);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->resizeColumnsToContents();



}

void MainWindow::on_radioButton_clicked()
{
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
    ui->pushButton_Reg->hide();
    ui->lineEdit_login->setText("tc");
    ui->lineEdit_password->setText("0");
}
