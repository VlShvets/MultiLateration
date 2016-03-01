#ifndef SETTINGROC_H
#define SETTINGROC_H

#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>
#include <QTableWidget>

#include "painter.h"

class SettingRoc : public QWidget
{
    Q_OBJECT

public:
    explicit SettingRoc(class Painter *_painter, QWidget *parent = 0);  /// Конструктор класса
    ~SettingRoc();                                                      /// Деструктор класса

private slots:
    void changeNumberRoc(int _count);     /// Изменение количества целей
    void changeParRoc(int _i, int _j);  /// Изменение параметров локаторов

private:
    void loadTable();           /// Загрузка таблицы с начальными данными

    QLCDNumber *lNumberRoc;     /// Дисплей количества целей
    QTableWidget *tParRoc;      /// Таблица параметров целей

    class Painter *painter;
};

#endif // SETTINGROC_H
