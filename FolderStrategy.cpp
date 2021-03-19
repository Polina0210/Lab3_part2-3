#include "FolderStrategy.h"
//Функция для вычисление размера папки
//На вход подаётся путь к папке
//На выходе - размер всей папки в байтах
qint32 FolderStrategy::FolderSize(const QString &path){
    qint32 res = 0;
    //Цикл по папкам в текущей папке
    foreach (QFileInfo size, QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden))
    {
        res+= FolderSize(size.absoluteFilePath());
    }
    //Цикл по всем файлам в папке
    foreach(QFileInfo result, QDir(path).entryInfoList(QDir::Files | QDir::NoDotAndDotDot| QDir::Hidden))
    {
        res+= result.size();
    }

    return res;
}

//функция для вычисление размеров содержимого папки
//также здесь производится группировка по элементам папки
//На вход подаётся путь к файлу
//На выходе - данные о размере каждого элемента в папке
QList<fileSizeInfo> FolderStrategy:: SizeInfo(const QString & path)
{
    QTextStream cout(stdout), cin(stdin);
    QList<fileSizeInfo> res;
    QList<qint32> size_;
    qint32 res_size = 0;

//Если файл является папкой
    if(QFileInfo(path).isDir()){
        //Если папка пуста, пользователь получает соответствующее сообщение
        if(QDir(path).isEmpty()){
            cout<<"The object "<<path<<" is empty"<<endl;
            return QList<fileSizeInfo>();
        }
//Цикл по всем папкам в папке
        foreach(QFileInfo size, QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir:: System, QDir::Name))
        {
            size_.append(FolderSize(size.absoluteFilePath()));
            res_size += size_[size_.size()-1];
        }
//Цикл по файлам в текущей папке
        foreach(QFileInfo size, QDir(path).entryInfoList(QDir::Files | QDir::NoDotAndDotDot|QDir::Hidden | QDir:: System, QDir::Name)){
            size_.append(size.size());
            res_size += size_[size_.size()-1];
        }
//Если итоговый размер равен нулю, пользователь получает соответствующее сообщение
        if(res_size == 0){
            cout<<"The object "<<path<<" is empty";
            return QList<fileSizeInfo>();
        }

        auto iter = size_.begin();
//Цикл по папкам в текущей папке
//Вычисление процентного соотношения
        foreach(QFileInfo folder_info, QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot|QDir::Hidden | QDir:: System, QDir::Name))
        {
            if(folder_info.fileName().mid(folder_info.fileName().lastIndexOf('.') + 1) == "lnk")
            {
                continue;
            }

            res.append(fileSizeInfo(folder_info.fileName(), *iter, ((float)*iter/res_size)*100));
            iter++;
        }
//Цикл по остальным файлам в папке
//Вычисление процентного соотношения
        foreach(QFileInfo file, QDir(path).entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir:: Hidden | QDir:: System, QDir::Name))
        {
            res.append(fileSizeInfo(file.fileName(), *iter, ((float)*iter/res_size)*100));
            iter++;
        }
    }
//Если на вход подали не папку, а файл
//Просто вычисляется размер, а процентное соотношение устанавливается 100
    else
    {
        cout<<"Files: "<<endl;
        qint32 file_size = QFileInfo(path).size();
        res.append(fileSizeInfo(QFileInfo(path).fileName(), file_size, 100));
    }

    return res;
}
