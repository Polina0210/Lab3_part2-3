#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PieDiagram.h"
#include "BarDiagram.h"

// конструктор
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    //настраиваем интерфейс окна
    ui->setupUi(this);
    //задание размера первого столбца в зависимости от длины отображающихся элементов
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //задание стратегии
    chooseStrategy = new FolderStrategy();
    //задание пути к домашней папке
    path = QDir::homePath();
    // создание модели файловой системы
    // здесь формируется отображение дерева папок
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Hidden | QDir::System);
    dirModel->setRootPath(path);

    ui->treeView->setModel(dirModel);
    ui->treeView->expandAll();
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(3);
    // задание отображения
    howView = new TableView(this);
    ui->splitter->addWidget(howView->treatmentData(sizeData));
    // соединение сигнала выбора директории со слотом отображения информации
    connect(ui->treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

}

void MainWindow::infoShow(bool refreshData = true, AbstractView *br = nullptr) {
    // проверка, необходимо ли обновить данные
    if (refreshData) {
        //если необходаима, получаем новые данные
        sizeData = chooseStrategy->SizeInfo(path);
        //обновление
        howView->treatmentData(sizeData);
    } else {
        //Если данные не нужно обновлять
        //размер виджетов сохраняется
        QList<int> width = ui->splitter->sizes();
        //удаление старого отображение
        delete howView;
        //запоминаем нужное отображение
        howView = br;
        //добавление виджета и задание размеров виджетов
        ui->splitter->addWidget(howView->treatmentData(sizeData));
        ui->splitter->setSizes(width);
    }
    //отображаем путь
    this->statusBar()->showMessage("Выбранный путь: " + path);
}


void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected) {
    Q_UNUSED(deselected);
    //получение индекса выбранной папки
    QModelIndexList indexs = selected.indexes();
    //получение пути выбранной папки
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
    }
    //сохраняем путь к папке/файлу
    path = filePath;
    //отображаем данные
    infoShow();
}


MainWindow::~MainWindow() {
    delete ui;
    delete dirModel;
    delete chooseStrategy;
    delete howView;
}

//Мб реализовать через слоты, если успею
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        delete chooseStrategy;
        chooseStrategy = new FolderStrategy();
        break;
    case 1:
        delete chooseStrategy;
        chooseStrategy = new TypeStrategy();
        break;
    }
    infoShow();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        infoShow(false, new TableView());
        break;
    case 1:
        infoShow(false, new PieDiagram());
        break;
    case 2:
        infoShow(false, new BarDiagram());
        break;
    }
}
