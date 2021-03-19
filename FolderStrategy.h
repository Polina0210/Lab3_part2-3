#ifndef GROUPBYFOLDER_H
#define GROUPBYFOLDER_H
#include "Strategy.h"
#include "QTextStream"
#include "QFileInfo"
#include "QDir"

using namespace std;
//Конкретный класс для группировки по папкам
class FolderStrategy: public Strategy
{
private:
    //Функция для вычисление размера папки
    //На вход подаётся путь к папке
    //На выходе - размер всей папки в байтах
    qint32 FolderSize(const QString&path);
public:
    FolderStrategy() {};
    //функция для вычисление размеров содержимого папки
    //также здесь производится группировка по элементам папки
    //На вход подаётся путь к файлу
    //На выходе - данные о размере каждого элемента в папке
    QList<fileSizeInfo> SizeInfo(const QString & path);
};





#endif // GROUPBYFOLDER_H
