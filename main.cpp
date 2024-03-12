#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;  // Создаем экземпляр вашего главного окна
    w.show();  // Показываем главное окно

    return a.exec();  // Запускаем цикл обработки событий
}
