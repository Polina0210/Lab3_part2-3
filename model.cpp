#include "model.h"

//конструктор
model::model(QObject *parent, const QList<fileSizeInfo> &data): QAbstractTableModel(parent) {
    //задаём размер массива
    dataModel.resize(data.size());
    //устанавливаем итератор в начало массива
    auto dataIterator = dataModel.begin();
    //цикл для занесения данных в массив
    for (auto iterator = data.begin(); iterator != data.end(); iterator++) {
        *dataIterator = *iterator;
        dataIterator++;
    }
}

int model::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return dataModel.count();
}

//возвращаем количество столбцов
//Здесь их два, поскольку имеется два параметра: название и объем в процентах
int model::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 2;
}


QVariant model:: data(const QModelIndex &index, int role) const{
    //если индекс неверный, ничего не возвращаем
    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole)) {
            return QVariant();
        }

    //если первый столбец, возвращаем имя
        if (index.column() == 0) {
            return dataModel[index.row()].fileName;

        }
        //иначе возращаем проценты (второй столбец)
        else if (index.column() == 1) {
            QString result;
            if (dataModel[index.row()].percent > 0 && dataModel[index.row()].percent < 0.01) {
                result = "< 0.01%";
            } else {
                result = QString::number(dataModel[index.row()].percent, 'f', 2) + '%';
            }
            return result;
        }
        return QVariant();
}

QVariant model:: headerData(int section, Qt::Orientation orientation, int role) const{
    //если роль не отображается, ничего не возвращаем
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    //проверка, вертикальная ли ориентация
    if (orientation == Qt::Vertical) {
        return section + 1;
    }

    //выбор, какая секция
    switch (section) {
    case NAME:
        return "Название";
    case PERCENT:
        return "В процентах";
    }
    return QVariant();
}
