#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include "AbstractView.h"
#include "model.h"
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QTableView>

//класс для отображения информации в виде таблицы
class TableView: public AbstractView
{
public:
    TableView(QObject *p = nullptr);
    //функция обработки данных
    //на входе - данные о размерах элементов папки
    //на выходе  - указатель на виджет, отображающий информацию в табличном виде
    QWidget* treatmentData(const QList<fileSizeInfo>&);
    ~TableView();
private:
    // указатель на виджет, отображающий информацию в табличном виде
    QAbstractItemView *view;
    // указатель на модель, из которой строится таблица
    QAbstractTableModel *modelView;
};

#endif // TABLEVIEW_H
