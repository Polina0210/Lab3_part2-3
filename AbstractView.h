#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include <QWidget>
#include <QList>
#include "Strategy.h"

//Абстрактный класс для отображения информации в нужном виде
class AbstractView
{
public:
    //конструктор
    AbstractView(QObject *p = nullptr): parent(p) {};
    //функция обработки данных
    //на вход принимает данные о размерах элементов папки
    //на выходе - указатель на виджет, необходимый для отображения информации в нужном виде
    virtual QWidget* treatmentData(const QList<fileSizeInfo>&) = 0;
    // виртуальный деструктор
    virtual ~AbstractView() {};
protected:
    //указатель на родителя
    QObject *parent;
};


#endif // ABSTRACTVIEW_H
