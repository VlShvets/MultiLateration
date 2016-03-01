#include "painter.h"

Painter::Painter(QWidget *parent)
    : Grapher2D(parent)
{
    setCSAbsMeasure(1000);
    setCSOrdMeasure(1000);
    setCSZoom(5);

    this->setWindowTitle(QObject::tr("Модель"));

    QPalette palette;
    palette.setColor(backgroundRole(), Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);

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
}

void Painter::initializationParOfLok()
{
    paramA.push_back(100000.0);     paramA.push_back(20000.0);      paramA.push_back(20000.0);      paramA.push_back(100000.0);     paramA.push_back(100000.0);
    paramB.push_back(20000.0);      paramB.push_back(100000.0);     paramB.push_back(100000.0);     paramB.push_back(20000.0);      paramB.push_back(100000.0);
    deltaX.push_back(0.0);          deltaX.push_back(-50000.0);     deltaX.push_back(50000.0);      deltaX.push_back(0.0);          deltaX.push_back(0.0);
    deltaY.push_back(50000.0);      deltaY.push_back(0.0);          deltaY.push_back(0.0);          deltaY.push_back(-50000.0);     deltaY.push_back(0.0);
    startph.push_back(90.0);        startph.push_back(0.0);         startph.push_back(90.0);        startph.push_back(180.0);       startph.push_back(270.0);
    speedL.push_back(800.0);        speedL.push_back(800.0);        speedL.push_back(800.0);        speedL.push_back(800.0);        speedL.push_back(400.0);
    radius.push_back(100000.0);     radius.push_back(100000.0);     radius.push_back(100000.0);     radius.push_back(100000.0);     radius.push_back(100000.0);
}

void Painter::initializationParOfRoc()
{
    for(int j = 0; j < 9; ++j)
    {
        coordX.push_back(-100000.0 + 20000 * (int) (j / 3));
        coordY.push_back(50000.0 + 20000 * (j % 3));
        sRocX.push_back(3000.0);
        sRocY.push_back(-3000.0);
    }
}

QVector <QVector <bool> > Painter::IdentificationLocator()
{
    QVector <QVector <bool> > temp;

    for(int i = 0; i < nLok; ++i)
    {
        temp.push_back(QVector <bool> ());
        for(int j = 0; j < nRoc; ++j)
        {
            if(qSqrt((pLok[i].x() - pRoc[j].x()) * (pLok[i].x() - pRoc[j].x()) +
                     (pLok[i].y() - pRoc[j].y()) * (pLok[i].y() - pRoc[j].y())) <= radius.at(i))
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
    for(int j = 0; j < nLok; ++j)
    {
        /// Траектория движения локатора
        pen.setColor(Qt::blue);
        pen.setWidth(1);
        pen.setStyle(Qt::DashLine);
        p.setPen(pen);
        p.drawEllipse(QPointF(deltaX.at(j), deltaY.at(j)), paramA.at(j), paramB.at(j));

        /// Локатор
        pen.setWidth(9);
        pen.setStyle(Qt::DotLine);
        p.setPen(pen);
        pLok.push_back(QPoint((paramA.at(j) * qCos(speedL.at(j) * time / (paramA.at(j) + paramB.at(j))
                                                   + (2 * M_PI / 360) * startph.at(j)) + deltaX.at(j)),
                              (paramB.at(j) * qSin(speedL.at(j) * time / (paramA.at(j) + paramB.at(j))
                                                   + (2 * M_PI / 360) * startph.at(j)) + deltaY.at(j))));
        p.drawPoint(pLok.at(j));

        /// Радиус действия локатора
        pen.setWidth(3);
        p.setPen(pen);
        p.drawEllipse(pLok.at(j), radius.at(j), radius.at(j));
    }

    /// Ракеты
    pen.setColor(Qt::darkGreen);
    pen.setWidth(6);
    pen.setStyle(Qt::DashLine);
    p.setPen(pen);
    for(int j = 0; j < nRoc; ++j)
    {
        pRoc.push_back(QPoint((coordX.at(j) + sRocX.at(j) * time),
                              (coordY.at(j) + sRocY.at(j) * time)));
        p.drawPoint(pRoc.at(j));
    }

    /// Пелинги
    pen.setColor(Qt::blue);
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);
    identificationLocator = IdentificationLocator();
    for(int i = 0; i < nLok; ++i)
    {
        for(int j = 0; j < nRoc; ++j)
        {
            if(identificationLocator[i][j])
            {   
                line.push_back(QLineF(pLok[i], pRoc[j]));   /// С точной информацией о местоположении цели
                line.last().setLength(radius.at(i));        /// С неточной информацией о местоположении цели

                /// Отрисовка
                p.drawLine(line.last());
            }
            else
                line.push_back(QLineF ());
        }
    }

    /// Отображение мнимых точек и их траекторий
    QPointF imPoint;
    for(int i = imPoints.size(); i >= sizeOfMemory; --i)
        imPoints.dequeue();
    imPoints.enqueue(QVector <QVector <QPointF> > ());
    for(int i = 1; i < line.size(); ++i)
    {
        imPoints.last().push_back(QVector <QPointF> ());
        for(int j = 0; j < i; ++j)
        {
            /// Мнимые точки
            pen.setColor(Qt::red);
            pen.setWidth(6);
            pen.setStyle(Qt::SolidLine);
            p.setPen(pen);
            if(line[i].intersect(line[j], &imPoint) == QLineF::BoundedIntersection &&
                    !pLok.contains(imPoint.toPoint()) && !pRoc.contains(imPoint.toPoint()))
            {
                p.drawPoint(imPoint);
                imPoints.last().last().push_back(imPoint);
            }
            else
                imPoints.last().last().push_back(QPointF());

            /// Цели в зоне видимости измерителей
            pen.setColor(Qt::green);
            p.setPen(pen);
            if(pRoc.contains(imPoint.toPoint()))
                p.drawPoint(imPoint);

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

    pLok.clear();
    pRoc.clear();
    line.clear();

    p.end();
}
