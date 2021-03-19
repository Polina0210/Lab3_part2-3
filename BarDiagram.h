#ifndef BARDIAGRAM_H
#define BARDIAGRAM_H

#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include "AbstractView.h"

//класс для отображения информации в виде столбчатой диаграммы
class BarDiagram: public AbstractView
{
public:
    // конструктор
    BarDiagram(QObject *p = nullptr);
    //функция обработки данных
    //на входе - данные о размерах элементов папки
    //на выходе  - указатель на виджет, отображающий информацию в виде столбчатой диаграммы
    QWidget* treatmentData(const QList<fileSizeInfo>&);
    // деструктор
    ~BarDiagram();
private:
    // указатель на виджет, отображающий информацию в виде круговой диаграммы
    QtCharts::QChartView *view;
    // указатель на модель, из которой строится круговая диаграмма
    QtCharts::QChart *modelView;

};

#endif // BARDIAGRAM_H
