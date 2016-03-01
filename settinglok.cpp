#include "settinglok.h"

SettingLok::SettingLok(Painter *_painter, QWidget *parent) :
    QWidget(parent)
{
    this->painter = _painter;

    this->setWindowTitle(QObject::tr("Параметры измерителей"));

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(new QLabel(QObject::tr("Количество измерителей: ")), 0, 0, 1, 1);
    QSlider *sliderLok = new QSlider(Qt::Horizontal);
    sliderLok->setRange(1, 5);
    sliderLok->setTickInterval(1);
    sliderLok->setValue(painter->nLok);
    sliderLok->setTickPosition(QSlider::TicksAbove);
    sliderLok->setFixedWidth(100);
    QObject::connect(sliderLok, SIGNAL(valueChanged(int)), this, SLOT(changeNumberLok(int)));
    gridLayout->addWidget(sliderLok, 0, 1, 1, 1);
    lNumberLok = new QLCDNumber(1);
    lNumberLok->setSegmentStyle(QLCDNumber::Flat);
    lNumberLok->setMode(QLCDNumber::Dec);
    lNumberLok->display(painter->nLok);
    lNumberLok->setFixedWidth(100);
    gridLayout->addWidget(lNumberLok, 0, 2, 1, 1);

    gridLayout->addWidget(new QLabel(QObject::tr("\tПараметры измерителей:")), 1, 0, 1, 3);

    tParLok = new QTableWidget(painter->nLok, 7, this);
    tParLok->setHorizontalHeaderLabels(QStringList() << "Первая полуось" << "Вторая полуось" << "Смещение по X" << "Смещение по Y" <<
                                        "Нач. фаза (360º)" << "Скорость (км/ч)" << "Радиус локации");
    QObject::connect(tParLok, SIGNAL(cellChanged(int,int)), this, SLOT(changeParLok(int,int)));
    gridLayout->addWidget(tParLok, 2, 0, 1, 3);

    loadTable();

    this->setLayout(gridLayout);
}

SettingLok::~SettingLok()
{
    delete lNumberLok;
    delete tParLok;
}

void SettingLok::loadTable()
{
    for(int i = 0; i < painter->nLok; ++i)
    {
        tParLok->setItem(i, 0, new QTableWidgetItem(QString::number(painter->paramA.at(i))));
        tParLok->setItem(i, 1, new QTableWidgetItem(QString::number(painter->paramB.at(i))));
        tParLok->setItem(i, 2, new QTableWidgetItem(QString::number(painter->deltaX.at(i))));
        tParLok->setItem(i, 3, new QTableWidgetItem(QString::number(painter->deltaY.at(i))));
        tParLok->setItem(i, 4, new QTableWidgetItem(QString::number(painter->startph.at(i))));
        tParLok->setItem(i, 5, new QTableWidgetItem(QString::number(painter->speedL.at(i))));
        tParLok->setItem(i, 6, new QTableWidgetItem(QString::number(painter->radius.at(i))));
    }
}

void SettingLok::changeNumberLok(int _count)
{
    painter->nLok = _count;
    painter->imPoints.clear();

    tParLok->setRowCount(_count);
    loadTable();

    lNumberLok->display(_count);
}

void SettingLok::changeParLok(int _i, int _j)
{
//    qDebug() << _i << "\t" << _j;
    switch(_j)
    {
    case 0:
    {
        painter->paramA[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 1:
    {
        painter->paramB[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 2:
    {
        painter->deltaX[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 3:
    {
        painter->deltaY[_i] = tParLok->item(_i, _j)->text().toFloat() * (-1.0);
        break;
    }
    case 4:
    {
        painter->startph[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 5:
    {
        painter->speedL[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 6:
    {
        painter->radius[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    default:
    {
        break;
    }
    }
    painter->imPoints.clear();
    painter->repaint();
}
