#include "settingroc.h"

SettingRoc::SettingRoc(Model *_model, QWidget *parent) :
    QWidget(parent)
{
    this->model = _model;

    this->setWindowTitle(QObject::tr("Параметры целей"));

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(new QLabel(QObject::tr("Количество целей: ")), 0, 0, 1, 1);

    QSlider *sliderRoc = new QSlider(Qt::Horizontal);
    sliderRoc->setRange(1, 9);
    sliderRoc->setTickInterval(1);
    sliderRoc->setValue(model->nRoc);
    sliderRoc->setTickPosition(QSlider::TicksAbove);
    sliderRoc->setFixedWidth(100);
    QObject::connect(sliderRoc, SIGNAL(valueChanged(int)), this, SLOT(changeNumberRoc(int)));
    gridLayout->addWidget(sliderRoc, 0, 1, 1, 1);
    lNumberRoc = new QLCDNumber(1);
    lNumberRoc->setSegmentStyle(QLCDNumber::Flat);
    lNumberRoc->setMode(QLCDNumber::Dec);
    lNumberRoc->display(model->nRoc);
    lNumberRoc->setFixedWidth(100);
    gridLayout->addWidget(lNumberRoc, 0, 2, 1, 1);

    gridLayout->addWidget(new QLabel(QObject::tr("\tПараметры целей:")), 1, 0, 1, 3);

    tParRoc = new QTableWidget(model->nRoc, 4, this);
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
    for(int i = 0; i < model->nRoc; ++i)
    {
        tParRoc->setItem(i, 0, new QTableWidgetItem(QString::number(model->coordX.at(i))));
        tParRoc->setItem(i, 1, new QTableWidgetItem(QString::number(model->coordY.at(i))));
        tParRoc->setItem(i, 2, new QTableWidgetItem(QString::number(model->sRocX.at(i))));
        tParRoc->setItem(i, 3, new QTableWidgetItem(QString::number(model->sRocY.at(i))));
    }
}

void SettingRoc::changeNumberRoc(int _count)
{
    model->nRoc = _count;
    model->imPoints.clear();

    tParRoc->setRowCount(_count);
    loadTable();

    lNumberRoc->display(_count);
}

void SettingRoc::changeParRoc(int _i, int _j)
{
//    qDebug() << _i << "\t" << _j;
    switch(_j)
    {
    case 0:
    {
        model->coordX[_i] = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 1:
    {
        model->coordY[_i] = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 2:
    {
        model->sRocX[_i] = tParRoc->item(_i, _j)->text().toFloat();
        break;
    }
    case 3:
    {
        model->sRocY[_i] = tParRoc->item(_i, _j)->text().toFloat();
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
