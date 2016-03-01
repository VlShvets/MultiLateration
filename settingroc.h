#ifndef SETTINGROC_H
#define SETTINGROC_H

#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>
#include <QTableWidget>

#include "model.h"

class SettingRoc : public QWidget
{
    Q_OBJECT

public:
    explicit SettingRoc(class Model *_model, QWidget *parent = 0);  /// Конструктор класса
    ~SettingRoc();                                                  /// Деструктор класса

private slots:
    void changeNumberRoc(int _count);     /// Изменение количества целей
    void changeParRoc(int _i, int _j);  /// Изменение параметров локаторов

private:
    void loadTable();           /// Загрузка таблицы с начальными данными

    QLCDNumber *lNumberRoc;     /// Дисплей количества целей
    QTableWidget *tParRoc;      /// Таблица параметров целей

    class Model *model;
};

#endif // SETTINGROC_H
