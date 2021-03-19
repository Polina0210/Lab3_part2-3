#ifndef PIEDIAGRAM_H
#define PIEDIAGRAM_H
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "AbstractView.h"

//класс для отображения информации в виде круговой диаграммы
class PieDiagram: public AbstractView
{
public:
    PieDiagram(QObject *p = nullptr);
    //функция обработки данных
    //на входе - данные о размерах элементов папки
    //на выходе  - указатель на виджет, отображающий информацию в виде круговой диаграммы
    QWidget* treatmentData(const QList<fileSizeInfo>&);
    ~PieDiagram();
private:
    // указатель на виджет, отображающий информацию в виде круговой диаграммы
    QtCharts::QChartView *view;
    // указатель на модель, из которой строится круговая диаграмма
    QtCharts::QChart *modelView;
};

#endif // PIEDIAGRAM_H
