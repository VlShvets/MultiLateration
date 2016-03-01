#ifndef SETTINGLOK_H
#define SETTINGLOK_H

#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>
#include <QTableWidget>

#include "model.h"

class SettingLok : public QWidget
{
    Q_OBJECT

public:
    explicit SettingLok(class Model *_model, QWidget *parent = 0);   /// Конструктор класса
    ~SettingLok();                                                   /// Деструктор класса

private slots:
    void changeNumberLok(int _count);   /// Изменение количества локаторов
    void changeParLok(int _i, int _j);  /// Изменение параметров локаторов

private:
    void loadTable();   /// Загрузка таблицы с начальными данными

    QLCDNumber *lNumberLok;     /// Дисплей количества локаторов
    QTableWidget *tParLok;      /// Таблица параметров локаторов

    class Model *model;
};

#endif // SETTINGLOK_H
