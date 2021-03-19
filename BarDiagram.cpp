#include "BarDiagram.h"

BarDiagram::BarDiagram(QObject *p): AbstractView(p) {
    //создаём виджет
    view = new QtCharts::QChartView();

    modelView = new QtCharts::QChart();

};

BarDiagram::~BarDiagram() {
    delete view;
    //модель была удалена вместе с виджетом
}

QWidget* BarDiagram::treatmentData(const QList<fileSizeInfo> &data) {
    //создаём диаграмму
    QtCharts::QChart *newModel = new QtCharts::QChart();

    //элементы диаграммы
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // цикл по всем элементам списка данных
    for (auto iterator = data.begin(); iterator != data.end(); iterator++) {
        // создание элемента диаграммы, занесение данных в этот элемент и серию
        QtCharts::QBarSet *set = new QtCharts::QBarSet(iterator->fileName + " (" + QString::number(iterator->percent, 'f', 2) + "%)");
        set->operator<<(iterator->percent);
        series->append(set);
    }

    //заносим данные в диаграмму
    newModel->addSeries(series);

    newModel->createDefaultAxes();

    //задаём настройки анимации
    newModel->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // создание оси y для удобного отображения данных
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setRange(0,100);
   // newModel->addAxis(axisY, Qt::AlignLeft);
    //series->attachAxis(axisY);

    // задание настроек легенды
    newModel->legend()->setVisible(true);
    newModel->legend()->setAlignment(Qt::AlignRight);

    //удаляем предыдущую модель, потому что виджет меняет модель, теряется наблюдение за прошлой, её нужно удалить самостоятельно
    QtCharts::QChart *modelTemp = modelView;
    modelView = newModel;
    view->setChart(this->modelView);
    delete modelTemp;

    return view;
}

