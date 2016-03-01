#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QQueue>
#include <QTimer>

#include <qmath.h>

#include <grapher2d.h>

class Painter : public Grapher2D
{
    Q_OBJECT

public:
    Painter(QWidget *parent = 0);
    ~Painter();

    int nLok;                   /// Колличество локаторов
    int nRoc;                   /// Колличество целей

    int sizeOfMemory;           /// Длина следа

    /// Переменные, связанные со временем
    QTimer *tTime;      /// Таймер времени
    float totalTime;    /// Общее время моделирования (в секундах)
    float time;         /// Текущее время

    QQueue <QVector <QVector <QPointF> > > imPoints;  /// Мнимые точки

    struct Lok
    {
        float paramA;   /// Первая главная полуось элипса
        float paramB;   /// Вторая главная полуось элипса
        float deltaX;   /// Смещение элипса по оси X
        float deltaY;   /// Смещение элипса по оси Y
        float startph;  /// Начальная фаза движения локатора
        float speed;    /// Скорость локаторов
        float radius;   /// Радиус локации

        QPointF pos;    /// Текущее положение
    };
    QVector <Lok> lok;  /// Локаторы

    struct Roc
    {
        float coordX;   /// Координата X
        float coordY;   /// Координата Y
        float speedX;   /// Скорость X
        float speedY;   /// Скорость Y

        QPointF pos;    /// Текущее положение
    };
    QVector <Roc> roc;  /// Цели

protected:
    void paintEvent(QPaintEvent *_pEvent);

private slots:
    void timerOut();

private:
    void initializationParOfLok();  /// Начальная инициализация параметров локаторов
    void initializationParOfRoc();  /// Начальная инициализация параметров ракет

    QVector <QVector <bool> > IdentificationLocator();  /// Локация целей
};

#endif // MODEL_H
