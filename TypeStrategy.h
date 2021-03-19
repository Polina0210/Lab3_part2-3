#ifndef GROUPBYTYPE_H
#define GROUPBYTYPE_H

#include "Strategy.h"
#include "QFileInfo"
#include "QDir"
#include "QMap"
#include "QTextStream"

using namespace std;

//Класс для группировки по типу данных
class TypeStrategy: public Strategy
{
private:
    //Вычисление размера вложенной папки
    //На вход подаётся путь, а также QMap - контейнер, хранящий информацию о размере,
    //который занимает в папке каждый тип данных
    void FolderSize(const QString&path, QMap<QString, qint32>&data);
    //Функция, которая определяет тип файла
    //На вход подаётся путь
    //На выходе - тип файла
    QString Type(const QString&path);
public:
    //конструктор
    TypeStrategy() {};
    //Функция для вычисления размеров элементов, находящихся в папке
    //На вход подаётся путь к файлу
    //На выходе - информация вида: типи и занимаемое в папке место
    QList<fileSizeInfo> SizeInfo(const QString & path);
};




#endif // GROUPBYTYPE_H
