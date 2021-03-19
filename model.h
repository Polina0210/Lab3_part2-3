#ifndef MODEL_H
#define MODEL_H
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include"Strategy.h"

//класс для считывания размера файлов
class model: public QAbstractTableModel
{
    Q_OBJECT
public:
    //конструктор
    model(QObject *parent = nullptr, const QList<fileSizeInfo> &dt = QList<fileSizeInfo>());

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    // Возвращает данные, хранящиеся в данной роли для элемента,
    //на который ссылается индекс
    //на входе ссылка на индекс элемента и int - роль
    //на выхоже - данные элемента модели
    QVariant data(const QModelIndex &index, int role) const override;
    //Возвращает заголовок элемента модели
    //(данные для данной роли и раздела в заголовке с указанной ориентацией)
    //на входе секция, ориентация и роль,
    //на выходе - данные заголовка элементов модели
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum NameColumn {
        NAME,
        PERCENT
    };
    //данные модели
    QVector<fileSizeInfo> dataModel;
};

#endif // MODEL_H
