#ifndef SETTINGTOTAL_H
#define SETTINGTOTAL_H

#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>

#include "model.h"

class SettingTotal : public QWidget
{
    Q_OBJECT

public:
    explicit SettingTotal(class Model *_model, QWidget *parent = 0);    /// Конструктор класса
    ~SettingTotal();                                                    /// Деструктор класса

private slots:
    void changeSizeMemory(int _count);  /// Изменение длины следа
    void visualizerStartStop();         /// Запуск и остановка отрисовщика
    void changeTotalTime(int _count);   /// Изменение времени моделирования
    void visualizerStartFromStart();    /// Запуск с начала

private:
    QPushButton *pStartStop;        /// Кнопка запуска и остановки процессов
    bool isStart;                   /// Флаг состояния кнопки
    QPushButton *pStartFromStart;   /// Кнопка запуска с начала

    class Model *model;
};

#endif // SETTINGTOTAL_H
