#include "settingroc.h"

SettingRoc::SettingRoc(Painter *_painter, QWidget *parent) :
    QWidget(parent), painter(_painter)
{
    this->setWindowTitle(QObject::tr("Параметры целей"));

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(new QLabel(QObject::tr("Количество целей: ")), 0, 0, 1, 1);

    QSlider *sliderRoc = new QSlider(Qt::Horizontal);
    sliderRoc->setRange(1, 9);
    sliderRoc->setTickInterval(1);
    sliderRoc->setValue(painter->nRoc);
    sliderRoc->setTickPosition(QSlider::TicksAbove);
    sliderRoc->setFixedWidth(100);
    QObject::connect(sliderRoc, SIGNAL(valueChanged(int)), this, SLOT(changeNumberRoc(int)));
    gridLayout->addWidget(sliderRoc, 0, 1, 1, 1);
    lNumberRoc = new QLCDNumber(1);
    lNumberRoc->setSegmentStyle(QLCDNumber::Flat);
    lNumberRoc->setMode(QLCDNumber::Dec);
    lNumberRoc->display(painter->nRoc);
    lNumberRoc->setFixedWidth(100);
    gridLayout->addWidget(lNumberRoc, 0, 2, 1, 1);

    gridLayout->addWidget(new QLabel(QObject::tr("\tПараметры целей:")), 1, 0, 1, 3);

    tParRoc = new QTableWidget(painter->nRoc, 4, this);
    tParRoc->setHorizontalHeaderLabels(QStringList() << "Координата X" << "Координата Y" << "Скор. X (км/ч)" << "Скор. Y (км/ч)");
    QObject::connect(tParRoc, SIGNAL(cellChanged(int,int)), this, SLOT(changeParRoc(int,int)));
    gridLayout->addWidget(tParRoc, 2, 0, 1, 3);

    loadTable();

    this->setLayout(gridLayout);
    this->show();
}

SettingRoc::~SettingRoc()
{
    delete lNumberRoc;
    delete tParRoc;
}

void SettingRoc::loadTable()
{
    for(int i = 0; i < painter->nRoc; ++i)
    {
        tParRoc->setItem(i, 0, new QTableWidgetItem(QString::number(painter->roc.at(i).coordX)));
        tParRoc->setItem(i, 1, new QTableWidgetItem(QString::number(painter->roc.at(i).coordY)));
        tParRoc->setItem(i, 2, new QTableWidgetItem(QString::number(painter->roc.at(i).speedX)));
        tParRoc->setItem(i, 3, new QTableWidgetItem(QString::number(painter->roc.at(i).speedY)));
    }
}

void SettingRoc::changeNumberRoc(int _count)
{
    painter->nRoc = _count;
    painter->imPoints.clear();

    tParRoc->setRowCount(_count);
    loadTable();

    lNumberRoc->display(_count);
}

void SettingRoc::changeParRoc(int _i, int _j)
{
    switch(_j)
    {
    case 0:
    {
        painter->roc[_i].coordX = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 1:
    {
        painter->roc[_i].coordY = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 2:
    {
        painter->roc[_i].speedX = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 3:
    {
        painter->roc[_i].speedY = tParRoc->item(_i, _j)->text().toFloat();
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
