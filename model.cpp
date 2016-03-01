#include "model.h"

Model::Model(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(QObject::tr("Модель"));

    QPalette palette;
    palette.setColor(backgroundRole(), Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);

    nRoc = 3;
    nLok = 3;

    sizeOfMemory = 100;
    totalTime = 20.0;

    angleX = 0.0;
    angleY = 0.0;
    scale = 20;

    tTime = new QTimer(this);
    QObject::connect(tTime, SIGNAL(timeout()), this, SLOT(timerOut()));

    initializationParOfLok();
    initializationParOfRoc();
}

Model::~Model()
{
    delete tTime;
}

void Model::initializationParOfLok()
{
    paramA.push_back(10.0);     paramA.push_back(2.0);      paramA.push_back(2.0);      paramA.push_back(10.0);     paramA.push_back(10.0);
    paramB.push_back(2.0);      paramB.push_back(10.0);     paramB.push_back(10.0);     paramB.push_back(2.0);      paramB.push_back(10.0);
    deltaX.push_back(0.0);      deltaX.push_back(-5.0);     deltaX.push_back(5.0);      deltaX.push_back(0.0);      deltaX.push_back(0.0);
    deltaY.push_back(5.0);      deltaY.push_back(0.0);      deltaY.push_back(0.0);      deltaY.push_back(-5.0);     deltaY.push_back(0.0);
    startph.push_back(90.0);     startph.push_back(0.0);     startph.push_back(90.0);    startph.push_back(180.0);   startph.push_back(270.0);
    speedL.push_back(800.0);    speedL.push_back(800.0);    speedL.push_back(800.0);    speedL.push_back(800.0);    speedL.push_back(400.0);
    radius.push_back(10.0);     radius.push_back(10.0);     radius.push_back(10.0);     radius.push_back(10.0);     radius.push_back(10.0);
}

void Model::initializationParOfRoc()
{
    for(int j = 0; j < 9; ++j)
    {
        coordX.push_back(-10.0 + 2 * (int) (j / 3));
        coordY.push_back(5.0 + 2 * (j % 3));
        sRocX.push_back(3000.0);
        sRocY.push_back(-3000.0);
    }
}

QVector <QVector <bool> > Model::IdentificationLocator()
{
    QVector <QVector <bool> > temp;

    for(int i = 0; i < nLok; ++i)
    {
        temp.push_back(QVector <bool> ());
        for(int j = 0; j < nRoc; ++j)
        {
            if(qSqrt((pLok[i].x() - pRoc[j].x()) * (pLok[i].x() - pRoc[j].x()) +
                     (pLok[i].y() - pRoc[j].y()) * (pLok[i].y() - pRoc[j].y())) <= radius.at(i) * scale)
                temp.last().push_back(true);
            else
                temp.last().push_back(false);
        }
    }

    return temp;
}

void Model::timerOut()
{
    /// Время
    if(time < totalTime)
        time += 0.1;
    else
    {
        time = 0;
        imPoints.clear();
    }
//    qDebug("Time = %f", time);

    repaint();
}

void Model::mousePressEvent(QMouseEvent * _pEvent)
{
    if(!_pEvent)
        return;
    oldPosMouse = _pEvent->pos();
    this->setCursor(Qt::CursorShape(Qt::ClosedHandCursor));
}

void Model::mouseReleaseEvent(QMouseEvent *)
{
    this->setCursor(Qt::CursorShape(Qt::OpenHandCursor));
}

void Model::mouseMoveEvent(QMouseEvent * _pEvent)
{
    if(!_pEvent)
        return;

    angleX += _pEvent->pos().x() - oldPosMouse.x();
//    qDebug("X = %f", angleX);

    angleY += _pEvent->pos().y() - oldPosMouse.y();
//    qDebug("Y = %f", angleY);

    oldPosMouse = _pEvent->pos();
    repaint();
}

void Model::wheelEvent(QWheelEvent * _pEvent)
{
    if(!_pEvent || !_pEvent->delta())
    return;

    if(_pEvent->delta() > 0)
    {
        if(scale < 100)
        {
            scaleTemp++;
            if(scaleTemp < 100)
                scale++;
            else
                scaleTemp = scale;
        }
    }
    else
    {
        if(scale > 2)
        {
            scaleTemp--;
            if(scaleTemp > 2)
                scale--;
            else
                scaleTemp = scale;
        }
    }
//    qDebug("Scale = %f", scale);

    imPoints.clear();
    repaint();
}

void Model::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.translate(width() / 2.0 + angleX, height() / 2.0 + angleY);

    /// Модель

    /// Локаторы
    for(int j = 0; j < nLok; ++j)
    {
        /// Траектория движения локатора
        p.setPen(QPen(Qt::blue, 1, Qt::DashLine));
        p.drawEllipse(QPointF(deltaX.at(j) * scale, deltaY.at(j) * scale), paramA.at(j) * scale, paramB.at(j) * scale);

        /// Локатор
        p.setPen(QPen(Qt::blue, 9, Qt::DotLine));
        pLok.push_back(QPoint((paramA.at(j) * qCos(speedL.at(j) * time * 0.00036 / (paramA.at(j) + paramB.at(j))
                                                   + (2 * M_PI / 360) * startph.at(j)) + deltaX.at(j)) * scale,
                              (paramB.at(j) * qSin(speedL.at(j) * time * 0.00036 / (paramA.at(j) + paramB.at(j))
                                                   + (2 * M_PI / 360) * startph.at(j)) + deltaY.at(j)) * scale));
        p.drawPoint(pLok.at(j));
        p.drawText(pLok.at(j).x() + 10, pLok.at(j).y() - 10, QString::number(j + 1));

        /// Радиус действия локатора
        p.setPen(QPen(Qt::blue, 3, Qt::DotLine));
        p.drawEllipse(pLok.at(j), radius.at(j) * scale, radius.at(j) * scale);
    }

    /// Ракеты
    p.setPen(QPen(Qt::darkGreen, 6, Qt::DashLine));
    for(int j = 0; j < nRoc; ++j)
    {
        pRoc.push_back(QPoint((coordX.at(j) + sRocX.at(j) * time / 3600.0) * scale,
                              -1.0 * (coordY.at(j) + sRocY.at(j) * time / 3600.0) * scale));
        p.drawPoint(pRoc[j]);
        p.drawText(pRoc.at(j).x() + 10, pRoc.at(j).y() - 10, QString::number(j + 1));
    }

    /// Пелинги
    p.setPen(QPen(Qt::blue, 1, Qt::SolidLine));
    identificationLocator = IdentificationLocator();
    for(int i = 0; i < nLok; ++i)
    {
        for(int j = 0; j < nRoc; ++j)
        {
            if(identificationLocator[i][j])
            {   
                line.push_back(QLineF(pLok[i], pRoc[j]));   /// С точной информацией о местоположении цели
                line.last().setLength(radius.at(i)*scale);             /// С неточной информацией о местоположении цели

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
            p.setPen(QPen(Qt::red, 6, Qt::SolidLine));
            if(line[i].intersect(line[j], &imPoint) == QLineF::BoundedIntersection &&
                    !pLok.contains(imPoint.toPoint()) && !pRoc.contains(imPoint.toPoint()))
            {
                p.drawPoint(imPoint);
                imPoints.last().last().push_back(imPoint);
            }
            else
                imPoints.last().last().push_back(QPointF());

            /// Цели в зоне видимости измерителей
            p.setPen(QPen(Qt::green, 6, Qt::SolidLine));
            if(pRoc.contains(imPoint.toPoint()))
                p.drawPoint(imPoint);

            /// Траектория мнимых точек
            p.setPen(QPen(Qt::red, 1, Qt::SolidLine));
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

    /// --------------------------------------------------

    /// Построение координатных осей
    p.setPen(QPen(Qt::black, 1, Qt::SolidLine));

    /// Построение линий координатный осей
    point.push_back(QPoint(- width() / 2 - angleX, 0));
    point.push_back(QPoint(width() / 2 - angleX, 0));
    point.push_back(QPoint(0, - height() / 2 - angleY));
    point.push_back(QPoint(0, height() / 2 - angleY));
    p.drawLine(point[0], point[1]);
    p.drawLine(point[2], point[3]);
    point.clear();

    /// Построение стрелок направлений координатных осей
    point.push_back(QPoint(0, - height() / 2 - angleY));
    point.push_back(QPoint(- 5, - height() / 2 + 5 - angleY));
    point.push_back(QPoint(+ 5,- height() / 2 + 5 - angleY));
    point.push_back(QPoint(width() / 2 - angleX, 0));
    point.push_back(QPoint(width() / 2 - 5 - angleX, - 5));
    point.push_back(QPoint(width() / 2 - 5 - angleX, + 5));
    p.drawLine(point[0], point[1]);
    p.drawLine(point[0], point[2]);
    p.drawLine(point[3], point[4]);
    p.drawLine(point[3], point[5]);
    point.clear();

    /// Построение штрихов на координатных осях
    /// Восток
    indexTemp = 1;
    angleTemp = scale;
    do
    {
        if(scale > 50)
            p.drawText(angleTemp - 3, 18, QString::number(indexTemp));
        if(scale > 10 && indexTemp%10 == 0)
            p.drawText(angleTemp - 3, 18, QString::number(indexTemp));
        if(indexTemp%100 == 0)
            p.drawText(angleTemp - 3, 18, QString::number(indexTemp));

        sizeScale = (indexTemp%100 == 0)?10:(indexTemp%50 == 0)?8:(indexTemp%10 == 0)?6:(indexTemp%5 == 0)?4:2;

        point.push_back(QPoint(angleTemp, -sizeScale));
        point.push_back(QPoint(angleTemp, sizeScale));

        p.drawLine(point[0], point[1]);
        point.clear();

        angleTemp += scale;
        ++indexTemp;
    }
    while(angleTemp <= width() / 2 - angleX);

    /// Запад
    indexTemp = 1;
    angleTemp = - scale;
    do
    {
        if(scale > 50)
            p.drawText(angleTemp - 9, 18, QString::number(-indexTemp));
        if(scale > 10 && indexTemp%10 == 0)
            p.drawText(angleTemp - 9, 18, QString::number(-indexTemp));
        if(indexTemp%100 == 0)
            p.drawText(angleTemp - 9, 18, QString::number(-indexTemp));

        sizeScale = (indexTemp%100 == 0)?10:(indexTemp%50 == 0)?8:(indexTemp%10 == 0)?6:(indexTemp%5 == 0)?4:2;
        ++indexTemp;

        point.push_back(QPoint(angleTemp, -sizeScale));
        point.push_back(QPoint(angleTemp, sizeScale));
        angleTemp -= scale;

        p.drawLine(point[0], point[1]);
        point.clear();
    }
    while(angleTemp >= - width() / 2 - angleX);

    /// Юг
    indexTemp = 1;
    angleTemp = scale;
    do
    {
        if(scale > 50)
            p.drawText(-30, angleTemp + 6, QString::number(-indexTemp));
        if(scale > 10 && indexTemp%10 == 0)
            p.drawText(-30, angleTemp + 6, QString::number(-indexTemp));
        if(indexTemp%100 == 0)
            p.drawText(-30, angleTemp + 6, QString::number(-indexTemp));

        sizeScale = (indexTemp%100 == 0)?10:(indexTemp%50 == 0)?8:(indexTemp%10 == 0)?6:(indexTemp%5 == 0)?4:2;
        ++indexTemp;

        point.push_back(QPoint(-sizeScale, angleTemp));
        point.push_back(QPoint(sizeScale, angleTemp));
        angleTemp += scale;

        p.drawLine(point[0], point[1]);
        point.clear();
    }
    while(angleTemp <= height() / 2 - angleY);

    /// Север
    indexTemp = 1;
    angleTemp = - scale;
    do
    {
        if(scale > 50)
            p.drawText(-24, angleTemp + 6, QString::number(indexTemp));
        if(scale > 10 && indexTemp%10 == 0)
            p.drawText(-24, angleTemp + 6, QString::number(indexTemp));
        if(indexTemp%100 == 0)
            p.drawText(-24, angleTemp + 6, QString::number(indexTemp));

        sizeScale = (indexTemp%100 == 0)?10:(indexTemp%50 == 0)?8:(indexTemp%10 == 0)?6:(indexTemp%5 == 0)?4:2;
        ++indexTemp;

        point.push_back(QPoint(-sizeScale, angleTemp));
        point.push_back(QPoint(sizeScale, angleTemp));
        angleTemp -= scale;

        p.drawLine(point[0], point[1]);
        point.clear();
    }
    while(angleTemp >= - height() / 2 - angleY);
}
