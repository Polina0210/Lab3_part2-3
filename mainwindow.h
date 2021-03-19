#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAbstractItemView>
#include <QFileSystemModel>
#include <QItemSelection>
#include <QMainWindow>
#include "AbstractView.h"
#include "model.h"
#include "Strategy.h"
#include "FolderStrategy.h"
#include "TypeStrategy.h"
#include "tableview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //слот, активирующийся при выборе директории
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    //комбобоксы с выбором представления
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);

private:
    //интерфейс окна
    Ui::MainWindow *ui;
    //модель файловой системы
    QFileSystemModel *dirModel;
    //указатель на стратегию
    Strategy *chooseStrategy;
    //данные о размерах элементов папки
    QList<fileSizeInfo> sizeData;
    //указатель на способ отображения
    AbstractView *howView;
    //путь к нужной папке
    QString path;
    //функция, организующая отображение данных в окне
    //на входе - флаг, указывающий на необходимость обновления данных,
    //а также указатель на отображение, на которое нужно сменить текущее
    void infoShow(bool, AbstractView*);
};
#endif // MAINWINDOW_H
