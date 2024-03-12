#include "prohil.h"
#include "ui_prohil.h"


prohil::prohil(QWidget *parent,QString name, QString login , QString password  , QString mail , QString telephoneNumber) :
    QDialog(parent),
    ui(new Ui::prohil)
{
    ui->setupUi(this);
    ui->lineEdit_name->setText(name);
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_mail->setText(mail);
    ui->lineEdit_phone->setText(telephoneNumber);

    old_name = name;
    old_password = password;
    old_login = login;
    old_mail = mail;
    old_phone = telephoneNumber;


    QString styleSheet_PushButton = "QPushButton {"
                                    "    background-color: #9966CC;"  // Зеленый цвет для фона
            "    border: none;"
            "    color: white;"
            "    text-align: center;"
            "    text-decoration: none;"
            "    font-size: 16px;"
            "    border-radius: 12px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #9988CC;"  // Зеленый цвет при наведении
            "    color: white;"
            "    border: 2px solid #9966CC;"   // Зеленая рамка при наведении
            "}";
    ui->pushButton_exit->setStyleSheet("QPushButton {"
          "    background-color: red;"  // Зеленый цвет для фона
          "    border: none;"
          "    color: white;"
          "    text-align: center;"
          "    text-decoration: none;"
          "    font-size: 16px;"
          "    border-radius: 12px;"
          "}"
          "QPushButton:hover {"
          "    background-color: #ff2e2e;"  // Зеленый цвет при наведении
          "    color: white;"
          "    border: 2px solid #cc0029;"   // Зеленая рамка при наведении
          "}");
    ui->pushButton->setStyleSheet(styleSheet_PushButton);
    QString styleSheet_lineEdit = "QLineEdit {"
                                  "    background-color: #d4d4d4;"  // Зеленый цвет для фона
            "    border: 1px solid #2ECC71;"   // Зеленая рамка
            "    color: black;"
            "    border-radius: 5px;"
            "}"
            "QLineEdit:hover {"
            "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
            "}";
    QString styleSheet_lineEdit_white = "QLineEdit {"
                                        "    background-color: #d4d4d4;"  // Зеленый цвет для фона
            "    border: 1px solid #2ECC71;"   // Зеленая рамка
            "    color: black;"
            "    border-radius: 5px;"
            "}"
            "QLineEdit:hover {"
            "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
            "}";
    ui->lineEdit_login->setStyleSheet(styleSheet_lineEdit);
    ui->lineEdit_mail->setStyleSheet(styleSheet_lineEdit);
    ui->lineEdit_phone->setStyleSheet(styleSheet_lineEdit);
    ui->lineEdit_name->setStyleSheet(styleSheet_lineEdit);
    ui->lineEdit_password->setStyleSheet(styleSheet_lineEdit);

    ui->label_reg->setStyleSheet("QLabel {"
                                 "    background-color: #9966CC;"  // Зеленый цвет для фона
                                 "    color: white;"
                                 "    border-radius: 5px;"
                                 "}"
                                 "QLabel:hover {"
                                 "    background-color: #27AE60;"  // Зеленый цвет при наведении
                                 "}");

    ui->lineEdit_login->setEnabled(false);
    ui->lineEdit_name->setEnabled(false);
    ui->lineEdit_password->setEnabled(false);
    ui->lineEdit_mail->setEnabled(false);
    ui->lineEdit_phone->setEnabled(false);



}

prohil::~prohil()
{
    delete ui;
}
// Функция проверки российского номера телефона


// Функция проверки имени (просто наличие букв)
bool isValidname(const QString &input) {
    // Проверка корректности имени, фамилии или отчества в одной строке
    bool isValid = QRegExp("^[А-Яа-яЁё\\s'-]{1,50}$").exactMatch(input);

    if (isValid) {
        qDebug() << "Валидное имя, фамилия или отчество:" << input;
    } else {
        qDebug() << "Невалидное имя, фамилия или отчество:" << input;
    }

    return isValid;
}
// Функция проверки пароля (пример: не менее 6 символов)
bool isValidpassword(const QString &password) {
    return password.length() >= 6;
}

// Функция проверки логина (пример: латинские буквы и цифры)
bool isValidlogin(QString &login) {
    QRegularExpression loginRegex(R"([A-Za-z0-9]+)");
    QRegularExpressionValidator validator(loginRegex);
    int pos = 0;
    return validator.validate(login, pos) == QValidator::Acceptable;
}
bool prohil::validateEmail()
{
    // Получите введенный email из QLineEdit (допустим, ui->lineEdit_email)
    QString email = ui->lineEdit_mail->text();

    // Создайте регулярное выражение для проверки email
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    // Создайте валидатор с использованием регулярного выражения
    QRegularExpressionValidator validator(emailRegex, this);

    // Проверьте, соответствует ли введенный email регулярному выражению
    int pos = 0;
    QValidator::State state = validator.validate(email, pos);

    // Выведите сообщение об ошибке, если email не корректен
    if (state != QValidator::Acceptable) {
        QMessageBox::warning(this, "Ошибка!", "Введите корректный email", QMessageBox::Ok);
        return 0;
    }
    return 1;

}
void prohil::on_pushButton_clicked()
{
    if (red == 0)
    {
        ui->lineEdit_login->setEnabled(true);
        ui->lineEdit_password->setEnabled(true);
        ui->lineEdit_mail->setEnabled(true);
        ui->lineEdit_name->setEnabled(true);
        ui->lineEdit_phone->setEnabled(true);
        QString stile = "QLineEdit {"
                        "    background-color: white;"  // Зеленый цвет для фона
                        "    border: 1px solid #2ECC71;"   // Зеленая рамка
                        "    color: black;"
                        "    border-radius: 5px;"
                        "    font-size: 18px;"
                        "}"
                        "QLineEdit:hover {"
                        "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                        "}";
        ui->lineEdit_login->setStyleSheet(stile);
        ui->lineEdit_mail->setStyleSheet(stile);
        ui->lineEdit_name->setStyleSheet(stile);
        ui->lineEdit_phone->setStyleSheet(stile);
        ui->lineEdit_password->setStyleSheet(stile);
        red = 1;
        ui->pushButton->setText("Сохранить изменения");
    }
    else
    {

        ui->lineEdit_login->setEnabled(false);
        ui->lineEdit_password->setEnabled(false);
        ui->lineEdit_mail->setEnabled(false);
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_phone->setEnabled(false);

        QString name = ui->lineEdit_name->text();
        QString mail = ui->lineEdit_mail->text();
        QString telephone_number = ui->lineEdit_phone->text();
        QString login = ui->lineEdit_login->text();
        QString password = ui->lineEdit_password->text();

        if (!isValidname(name)) {
            QMessageBox::warning(this, "Ошибка!", "Введите корректное имя", QMessageBox::Ok);
            ui->lineEdit_login->setEnabled(true);
            ui->lineEdit_password->setEnabled(true);
            ui->lineEdit_mail->setEnabled(true);
            ui->lineEdit_name->setEnabled(true);
            ui->lineEdit_phone->setEnabled(true);
        } else if (!isValidpassword(password)) {
            QMessageBox::warning(this, "Ошибка!", "Введите пароль длиной не менее 6 символов", QMessageBox::Ok);
            ui->lineEdit_login->setEnabled(true);
            ui->lineEdit_password->setEnabled(true);
            ui->lineEdit_mail->setEnabled(true);
            ui->lineEdit_name->setEnabled(true);
            ui->lineEdit_phone->setEnabled(true);
        } else if (!isValidlogin(login)) {
            QMessageBox::warning(this, "Ошибка!", "Введите корректный логин (латинские буквы и цифры)", QMessageBox::Ok);
            ui->lineEdit_login->setEnabled(true);
            ui->lineEdit_password->setEnabled(true);
            ui->lineEdit_mail->setEnabled(true);
            ui->lineEdit_name->setEnabled(true);
            ui->lineEdit_phone->setEnabled(true);
        }else if (!validateEmail()) {
            QMessageBox::warning(this, "Ошибка!", "Введите корректную почту ", QMessageBox::Ok);
            ui->lineEdit_login->setEnabled(true);
            ui->lineEdit_password->setEnabled(true);
            ui->lineEdit_mail->setEnabled(true);
            ui->lineEdit_name->setEnabled(true);
            ui->lineEdit_phone->setEnabled(true);
        }
        else {
            QString styleSheet_lineEdit = "QLineEdit {"
                                                "    background-color: #d4d4d4;"  // Зеленый цвет для фона
                    "    border: 1px solid #2ECC71;"   // Зеленая рамка
                    "    color: black;"
                    "    border-radius: 5px;"
                    "    font-size: 18px;"
                    "}"
                    "QLineEdit:hover {"
                    "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                    "}";

            ui->lineEdit_login->setStyleSheet(styleSheet_lineEdit);
            ui->lineEdit_mail->setStyleSheet(styleSheet_lineEdit);
            ui->lineEdit_phone->setStyleSheet(styleSheet_lineEdit);
            ui->lineEdit_name->setStyleSheet(styleSheet_lineEdit);
            ui->lineEdit_password->setStyleSheet(styleSheet_lineEdit);
            // Отправка сигнала с данными
            emit sendDATA(name, mail, telephone_number,login,password);
            red = 0;
            ui->pushButton->setText("Редактировать");

    }


  }
}

void prohil::on_pushButton_exit_clicked()
{
    if ((old_login != QString(ui->label_login->text()) or old_login != QString(ui->label_login->text()) or old_login != QString(ui->label_login->text()) or old_login != QString(ui->label_login->text())))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание!!!");
        msgBox.setText("Вы уверены, что хотите продолжить? Данные могли не сохраниться");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, "Да");
        msgBox.setButtonText(QMessageBox::Cancel, "Отмена");

        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
          close();
        }
        else {

        }
    }
    else{
        close();
    }
}

void prohil::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Внимание!!!");
    msgBox.setText("Вы уверены, что хотите продолжить? Данные могли не сохраниться");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::Cancel, "Отмена");

    int reply = msgBox.exec();
    if (reply == QMessageBox::Yes)
    {
      event->accept();
    }
    else {
        event->ignore();

    }
}




