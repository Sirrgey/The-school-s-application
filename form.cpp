#include "form.h"
#include "ui_form.h"

form::form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("QPushButton {"
                                      "    background-color: #9966CC;"  // Зеленый цвет для фона
                                      "    border: none;"
                                      "    color: white;"
                                      "    text-align: center;"
                                      "    text-decoration: none;"
                                      "    font-size: 16px;"
                                      "    border-radius: 12px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "    background-color: #27AE60;"  // Зеленый цвет при наведении
                                      "    color: white;"
                                      "    border: 2px solid #2ECC71;"   // Зеленая рамка при наведении
                                      "}");
    ui->lineEdit_name->setStyleSheet("QLineEdit {"
                                "    background-color: white;"  // Зеленый цвет для фона
                                "    border: 1px solid #2ECC71;"   // Зеленая рамка
                                "    color: black;"
                                "    border-radius: 5px;"
                                "}"
                                "QLineEdit:hover {"
                                "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                                "}");
    ui->lineEdit_mail->setStyleSheet("QLineEdit {"
                                "    background-color: white;"  // Зеленый цвет для фона
                                "    border: 1px solid #2ECC71;"   // Зеленая рамка
                                "    color: black;"
                                "    border-radius: 5px;"
                                "}"
                                "QLineEdit:hover {"
                                "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                                "}");
    ui->lineEdit_phone->setStyleSheet("QLineEdit {"
                                "    background-color: white;"  // Зеленый цвет для фона
                                "    border: 1px solid #2ECC71;"   // Зеленая рамка
                                "    color: black;"
                                "    border-radius: 5px;"
                                "}"
                                "QLineEdit:hover {"
                                "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                                "}");
    ui->lineEdit_password->setStyleSheet("QLineEdit {"
                                "    background-color: white;"  // Зеленый цвет для фона
                                "    border: 1px solid #2ECC71;"   // Зеленая рамка
                                "    color: black;"
                                "    border-radius: 5px;"
                                "}"
                                "QLineEdit:hover {"
                                "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                                "}");
    ui->lineEdit_login->setStyleSheet("QLineEdit {"
                                "    background-color: white;"  // Зеленый цвет для фона
                                "    border: 1px solid #2ECC71;"   // Зеленая рамка
                                "    color: black;"
                                "    border-radius: 5px;"
                                "}"
                                "QLineEdit:hover {"
                                "    border: 1px solid #27AE60;"   // Зеленая рамка при наведении
                                "}");
    ui->label_reg->setStyleSheet("QLabel {"
                             "    background-color: #9966CC;"  // Зеленый цвет для фона
                             "    color: white;"
                             "    border-radius: 5px;"
                             "}"
                             "QLabel:hover {"
                             "    background-color: #27AE60;"  // Зеленый цвет при наведении
                             "}");

}

form::~form()
{
    delete ui;
}

// Функция проверки российского номера телефона
bool isValidPhoneNumber(QString &phone) {
    QRegularExpression phoneRegex(R"(+7[0-9]{10})");
    QRegularExpressionValidator validator(phoneRegex);
    int pos = 0;
    return validator.validate(phone, pos) == QValidator::Acceptable;
}

// Функция проверки имени (просто наличие букв)
bool isValidName(QString &name) {
    QRegularExpression nameRegex(R"([A-Za-zА-Яа-я]+)");
    QRegularExpressionValidator validator(nameRegex);
    int pos = 0;
    return validator.validate(name, pos) == QValidator::Acceptable;
}

// Функция проверки пароля (пример: не менее 6 символов)
bool isValidPassword(const QString &password) {
    return password.length() >= 6;
}

// Функция проверки логина (пример: латинские буквы и цифры)
bool isValidLogin(QString &login) {
    QRegularExpression loginRegex(R"([A-Za-z0-9]+)");
    QRegularExpressionValidator validator(loginRegex);
    int pos = 0;
    return validator.validate(login, pos) == QValidator::Acceptable;
}
bool form::validateEmail()
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

void form::on_pushButton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString mail = ui->lineEdit_mail->text();
    QString telephone_number = ui->lineEdit_phone->text();
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if (!isValidPhoneNumber(telephone_number)) {
        QMessageBox::warning(this, "Ошибка!", "Введите корректный номер телефона", QMessageBox::Ok);
    } else if (!isValidName(name)) {
        QMessageBox::warning(this, "Ошибка!", "Введите корректное имя", QMessageBox::Ok);
    } else if (!isValidPassword(password)) {
        QMessageBox::warning(this, "Ошибка!", "Введите пароль длиной не менее 6 символов", QMessageBox::Ok);
    } else if (!isValidLogin(login)) {
        QMessageBox::warning(this, "Ошибка!", "Введите корректный логин (латинские буквы и цифры)", QMessageBox::Ok);
    }else if (!validateEmail()) {
        QMessageBox::warning(this, "Ошибка!", "Введите корректную почту ", QMessageBox::Ok);
    }
    else {
        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_mail->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_name->clear();

        // Отправка сигнала с данными
        emit sendData(name, mail, telephone_number,login,password);
        close();

    }


}




