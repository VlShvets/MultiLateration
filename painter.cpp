#include "painter.h"

Painter::Painter(QWidget *parent)
    : Grapher2D(parent)
{
    setCSAbsMeasure(1000);
    setCSOrdMeasure(1000);
    setCSZoom(2);

    this->setWindowTitle(QObject::tr("МультиЛатерация"));

    nRoc = 3;
    nLok = 3;

    sizeOfMemory = 100;
    totalTime = 60.0;

    tTime = new QTimer(this);
    QObject::connect(tTime, SIGNAL(timeout()), this, SLOT(timerOut()));

    initializationParOfLok();
    initializationParOfRoc();
}

Painter::~Painter()
{
    delete tTime;
    lok.clear();
    roc.clear();
    imPoints.clear();
}

void Painter::initializationParOfLok()
{
    lok.push_back(Lok());       lok.push_back(Lok());       lok.push_back(Lok());       lok.push_back(Lok());       lok.push_back(Lok());
    lok[0].paramA = 100000.0;   lok[1].paramA = 20000.0;    lok[2].paramA = 20000.0;    lok[3].paramA = 100000.0;   lok[4].paramA = 100000.0;
    lok[0].paramB = 20000.0;    lok[1].paramB = 100000.0;   lok[2].paramB = 100000.0;   lok[3].paramB = 20000.0;    lok[4].paramB = 100000.0;
    lok[0].deltaX = 0.0;        lok[1].deltaX = -50000.0;   lok[2].deltaX = 50000.0;    lok[3].deltaX = 0.0;        lok[4].deltaX = 0.0;
    lok[0].deltaY = 50000.0;    lok[1].deltaY = 0.0;        lok[2].deltaY = 0.0;        lok[3].deltaY = -50000.0;   lok[4].deltaY = 0.0;
    lok[0].startph = 90.0;      lok[1].startph = 0.0;       lok[2].startph = 90.0;      lok[3].startph = 180.0;     lok[4].startph = 270.0;
    lok[0].speed = 800.0;       lok[1].speed = 800.0;       lok[2].speed = 1600.0;       lok[3].speed = 800.0;       lok[4].speed = 400.0;
    lok[0].radius = 100000.0;   lok[1].radius = 100000.0;   lok[2].radius = 100000.0;   lok[3].radius = 100000.0;   lok[4].radius = 100000.0;
}

void Painter::initializationParOfRoc()
{
    for(int j = 0; j < 9; ++j)
    {
        roc.push_back(Roc());
        roc[j].coordX = -100000.0 + 20000 * (int) (j / 3);
        roc[j].coordY = 50000.0 + 20000 * (j % 3);
        roc[j].speedX = 3000.0;
        roc[j].speedY = -3000.0;
    }
}

QVector <QVector <bool> > Painter::IdentificationLocator(QVector <QPointF> *_pLok, QVector <QPointF> *_pRoc)
{
    QVector <QVector <bool> > temp;

    for(int i = 0; i < nLok; ++i)
    {
        temp.push_back(QVector <bool> ());
        for(int j = 0; j < nRoc; ++j)
        {
            if(qSqrt((_pLok->at(i).x() - _pRoc->at(j).x()) * (_pLok->at(i).x() - _pRoc->at(j).x()) +
                     (_pLok->at(i).y() - _pRoc->at(j).y()) * (_pLok->at(i).y() - _pRoc->at(j).y())) <= lok.at(i).radius)
                temp.last().push_back(true);
            else
                temp.last().push_back(false);
        }
    }

    return temp;
}

void Painter::timerOut()
{
    /// Время
    if(time < totalTime)
        time += 0.1;
    else
    {
        time = 0;
        imPoints.clear();
    }

    repaint();
}

void Painter::paintEvent(QPaintEvent *_pEvent)
{
    Grapher2D::paintEvent(_pEvent);

    QPainter p(this);
    p.translate(getCSAbsTranslate(), getCSOrdTranslate());
    p.scale(getCSAbsScale(), getCSOrdScale());

    QPen pen;
    pen.setCosmetic(true);

    /// Локаторы
    QVector <QPointF> pLok;
    pen.setColor(Qt::darkBlue);
    pen.setStyle(Qt::DashLine);
    for(int i = 0; i < nLok; ++i)
    {
        /// Траектория движения локатора
        pen.setWidth(1);
        p.setPen(pen);
        p.drawEllipse(QPointF(lok.at(i).deltaX, lok.at(i).deltaY), lok.at(i).paramA, lok.at(i).paramB);

        /// Локатор
        pLok.push_back(QPoint(lok.at(i).paramA * qCos(lok.at(i).speed * time / (lok.at(i).paramA + lok.at(i).paramB)
                                                      + (2 * M_PI / 360) * lok.at(i).startph) + lok.at(i).deltaX,
                              lok.at(i).paramB * qSin(lok.at(i).speed * time / (lok.at(i).paramA + lok.at(i).paramB)
                                                      + (2 * M_PI / 360) * lok.at(i).startph) + lok.at(i).deltaY));
        pen.setWidth(9);
        p.setPen(pen);
        p.drawPoint(pLok.last());

        /// Радиус действия локатора
        pen.setWidth(3);
        p.setPen(pen);
        p.drawEllipse(pLok.at(i), lok.at(i).radius, lok.at(i).radius);
    }

    /// Ракеты
    QVector <QPointF> pRoc;
    pen.setColor(Qt::darkGreen);
    pen.setWidth(6);
    p.setPen(pen);
    for(int j = 0; j < nRoc; ++j)
    {
        pRoc.push_back(QPoint(roc.at(j).coordX + roc.at(j).speedX * time,
                              roc.at(j).coordY + roc.at(j).speedY * time));
        p.drawPoint(pRoc.last());
    }

    /// Пелинги
    QVector <QLineF> line;
    pen.setColor(Qt::darkBlue);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    p.setPen(pen);
    QVector <QVector <bool> > identificationLocator;
    identificationLocator = IdentificationLocator(&pLok, &pRoc);
    for(int i = 0; i < nLok; ++i)
    {
        for(int j = 0; j < nRoc; ++j)
        {
            if(identificationLocator[i][j])
            {
                line.push_back(QLineF(pLok.at(i), pRoc.at(j)));     /// С точной информацией о местоположении цели
                line.last().setLength(lok.at(i).radius);            /// С неточной информацией о местоположении цели

                /// Отрисовка
                p.drawLine(line.last());
            }
            else
                line.push_back(QLineF());
        }
    }

    /// Отображение мнимых точек и их траекторий
    QPointF imPoint;
    imPoints.enqueue(QVector <QVector <QPointF> > ());
    for(int i = 1; i < line.size(); ++i)
    {
        imPoints.last().push_back(QVector <QPointF> ());
        for(int j = 0; j < i; ++j)
        {
            /// Мнимые точки
            pen.setWidth(6);
            if(line[i].intersect(line[j], &imPoint) == QLineF::BoundedIntersection &&
                    !pLok.contains(imPoint.toPoint()) && !pRoc.contains(imPoint.toPoint()))
            {
                pen.setColor(Qt::red);
                p.setPen(pen);
                p.drawPoint(imPoint);
                imPoints.last().last().push_back(imPoint);
            }
            else
                imPoints.last().last().push_back(QPointF());

            /// Цели в зоне видимости измерителей
            if(pRoc.contains(imPoint.toPoint()))
            {
                pen.setColor(Qt::green);
                p.setPen(pen);
                p.drawPoint(imPoint);
            }

            /// Траектория мнимых точек
            pen.setColor(Qt::red);
            pen.setWidth(1);
            p.setPen(pen);
            for(int i = imPoints.size(); i > 1; --i)
            {
                if(!imPoints.at(imPoints.size() - i).at(imPoints.last().size() - 1).at(imPoints.last().last().size() - 1).isNull() &&
                        !imPoints.at(imPoints.size() - i + 1).at(imPoints.last().size() - 1).at(imPoints.last().last().size() - 1).isNull())
                {
                    p.drawLine(imPoints.at(imPoints.size() - i).at(imPoints.last().size() - 1).at(imPoints.last().last().size() - 1),
                               imPoints.at(imPoints.size() - i + 1).at(imPoints.last().size() - 1).at(imPoints.last().last().size() - 1));
                }
            }
        }
    }
    for(int i = imPoints.size(); i > sizeOfMemory - 1; --i)
        imPoints.dequeue();

    pLok.clear();
    pRoc.clear();
    line.clear();
    identificationLocator.clear();

    p.end();
}
