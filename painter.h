#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QQueue>
#include <QTimer>

#include <qmath.h>

class Painter : public QWidget
{
    Q_OBJECT

public:
    Painter(QWidget *parent = 0);
    ~Painter();

    int nLok;                   /// Колличество локаторов
    int nRoc;                   /// Колличество целей

    int sizeOfMemory;           /// Длина следа

    /// Переменные, связанные со временем
    QTimer *tTime;   /// Таймер времени
    float totalTime;        /// Общее время моделирования (в секундах)
    float time;             /// Текущее время

    QQueue <QVector <QVector <QPointF> > > imPoints;  /// Мнимые точки

    /// Параметры локтаоров
    QVector <float> paramA;     /// Первая главная полуось элипса
    QVector <float> paramB;     /// Вторая главная полуось элипса
    QVector <float> deltaX;     /// Смещение элипса по оси X
    QVector <float> deltaY;     /// Смещение элипса по оси Y
    QVector <float> startph;    /// Начальная фаза движения локатора
    QVector <float> speedL;     /// Скорость локаторов
    QVector <float> radius;     /// Радиус локации

    /// Параметры ракет
    QVector <float> coordX;     /// Координата X
    QVector <float> coordY;     /// Координата Y
    QVector <float> sRocX;      /// Скорость X
    QVector <float> sRocY;      /// Скорость Y


protected:
    void mousePressEvent(QMouseEvent * _pEvent);
    void mouseMoveEvent(QMouseEvent * _pEvent);
    void wheelEvent(QWheelEvent * _pEvent);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void timerOut();

private:
    void initializationParOfLok();  /// Начальная инициализация параметров локаторов
    void initializationParOfRoc();  /// Начальная инициализация параметров ракет

    QVector <QVector <bool> > IdentificationLocator();  /// Локация целей

    /// Переменные, связанные с движением курсора мыши
    float angleX, angleY;   /// Сдвиг системы координат
    float angleTemp;        /// Шаг штрихов координатной плоскости
    int indexTemp;          /// Цифровые значения осей системы координат
    int sizeScale;          /// Размер штрихов координатной плоскости
    QPoint oldPosMouse;     /// Предыдущая позиция курсора мыши
    int scale, scaleTemp;   /// Масштаб системы координат

    QVector <QVector <bool> > identificationLocator;    /// Двумерный массив идентификации целей локаторами

    /// Наборы точек и линий для отрисовки движущихся объектов
    QVector <QPoint> point;     /// Точки для отрисовки координатных осей
    QVector <QPointF> pLok;      /// Локаторы
    QVector <QPointF> pRoc;      /// Цели
    QVector <QLineF> line;      /// Линии для отрисовки пелингов
};

#endif // MODEL_H
