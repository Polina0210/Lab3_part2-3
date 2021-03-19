#include "mainwindow.h"

#include <QApplication>

 //тут ничего и не должно быть
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
