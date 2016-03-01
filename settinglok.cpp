#include "settinglok.h"

SettingLok::SettingLok(Model *_model, QWidget *parent) :
    QWidget(parent)
{
    this->model = _model;

    this->setWindowTitle(QObject::tr("Параметры измерителей"));

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(new QLabel(QObject::tr("Количество измерителей: ")), 0, 0, 1, 1);
    QSlider *sliderLok = new QSlider(Qt::Horizontal);
    sliderLok->setRange(1, 5);
    sliderLok->setTickInterval(1);
    sliderLok->setValue(model->nLok);
    sliderLok->setTickPosition(QSlider::TicksAbove);
    sliderLok->setFixedWidth(100);
    QObject::connect(sliderLok, SIGNAL(valueChanged(int)), this, SLOT(changeNumberLok(int)));
    gridLayout->addWidget(sliderLok, 0, 1, 1, 1);
    lNumberLok = new QLCDNumber(1);
    lNumberLok->setSegmentStyle(QLCDNumber::Flat);
    lNumberLok->setMode(QLCDNumber::Dec);
    lNumberLok->display(model->nLok);
    lNumberLok->setFixedWidth(100);
    gridLayout->addWidget(lNumberLok, 0, 2, 1, 1);

    gridLayout->addWidget(new QLabel(QObject::tr("\tПараметры измерителей:")), 1, 0, 1, 3);

    tParLok = new QTableWidget(model->nLok, 7, this);
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
    for(int i = 0; i < model->nLok; ++i)
    {
        tParLok->setItem(i, 0, new QTableWidgetItem(QString::number(model->paramA.at(i))));
        tParLok->setItem(i, 1, new QTableWidgetItem(QString::number(model->paramB.at(i))));
        tParLok->setItem(i, 2, new QTableWidgetItem(QString::number(model->deltaX.at(i))));
        tParLok->setItem(i, 3, new QTableWidgetItem(QString::number(model->deltaY.at(i))));
        tParLok->setItem(i, 4, new QTableWidgetItem(QString::number(model->startph.at(i))));
        tParLok->setItem(i, 5, new QTableWidgetItem(QString::number(model->speedL.at(i))));
        tParLok->setItem(i, 6, new QTableWidgetItem(QString::number(model->radius.at(i))));
    }
}

void SettingLok::changeNumberLok(int _count)
{
    model->nLok = _count;
    model->imPoints.clear();

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
        model->paramA[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 1:
    {
        model->paramB[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 2:
    {
        model->deltaX[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 3:
    {
        model->deltaY[_i] = tParLok->item(_i, _j)->text().toFloat() * (-1.0);
        break;
    }
    case 4:
    {
        model->startph[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 5:
    {
        model->speedL[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    case 6:
    {
        model->radius[_i] = tParLok->item(_i, _j)->text().toFloat();
        break;
    }
    default:
    {
        break;
    }
    }
    model->imPoints.clear();
    model->repaint();
}
