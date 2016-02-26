#ifndef SETTINGTOTAL_H
#define SETTINGTOTAL_H

#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>

#include "painter.h"

class SettingTotal : public QWidget
{
    Q_OBJECT

public:
    explicit SettingTotal(Painter *_painter, QWidget *parent = 0);  /// Конструктор класса
    ~SettingTotal();                                                /// Деструктор класса

private slots:
    void changeSizeMemory(int _count);  /// Изменение длины следа
    void visualizerStartStop();         /// Запуск и остановка отрисовщика
    void changeTotalTime(int _count);   /// Изменение времени моделирования
    void visualizerStartFromStart();    /// Запуск с начала

private:
    QPushButton *pStartStop;        /// Кнопка запуска и остановки процессов
    bool isStart;                   /// Флаг состояния кнопки
    QPushButton *pStartFromStart;   /// Кнопка запуска с начала

    Painter *painter;
};

#endif // SETTINGTOTAL_H
