#include "tableview.h"

TableView::TableView(QObject *p): AbstractView(p) {

    QTableView *view_ptr = new QTableView();

    modelView = new model();

    // устанавливаем отображение на всю ширину и высоту виджета
    view_ptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // сохранение виджета
    view = view_ptr;
}

TableView::~TableView() {
    //удаляем виджет и модель соответственно
    delete view;
    delete modelView;
}


QWidget* TableView::treatmentData(const QList<fileSizeInfo> &data) {
    //удаляем предыдущей модели
    delete modelView;
    //создаём новую модель
    modelView = new model(parent, data);
    //заносим новую модель в виджет
    view->setModel(modelView);
    //функция возвращает указатель на виджет
    return view;
}
