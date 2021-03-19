#include "PieDiagram.h"

PieDiagram::PieDiagram(QObject *p): AbstractView(p)
{    //создаём виджет
    view = new QtCharts::QChartView();

    modelView = new QtCharts::QChart();
}

PieDiagram::~PieDiagram() {
    delete view;
    //модель была удалена вместе с виджетом
}

QWidget* PieDiagram::treatmentData(const QList<fileSizeInfo> &data) {
    //создаём диаграмму
    QtCharts::QChart *newModel = new QtCharts::QChart();

    //элементы диаграммы
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    // цикл по всем элементам списка данных
    for (auto iterator = data.begin(); iterator != data.end(); iterator++) {
        // создание элемента диаграммы, занесение данных в серию
        series->append(new QtCharts::QPieSlice(iterator->fileName + " (" + QString::number(iterator->percent, 'f', 2) + "%)", iterator->percent));
    }
    //заносим данные в диаграмму
    newModel->addSeries(series);

   //задаём настройки легенды: видимость и расположение
    newModel->legend()->setVisible(true);
    newModel->legend()->setAlignment(Qt::AlignRight);

    //удаляем предыдущую модель, потому что виджет меняет модель, теряется наблюдение за прошлой, её нужно удалить самостоятельно
    QtCharts::QChart *modelTemp = modelView;
    modelView = newModel;
    view->setChart(this->modelView);
    delete modelTemp;
    // возврат указателя на виджет
    return view;
}
