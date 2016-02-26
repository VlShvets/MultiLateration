#include "settingtotal.h"

#include <QDebug>

SettingTotal::SettingTotal(Painter *_painter, QWidget *parent) :
    QWidget(parent), isStart(false), painter(_painter)
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(new QSplitter());
    hLayout->addWidget(new QLabel(QObject::tr("Длина следа:")));

    QSlider *sliderMemory = new QSlider(Qt::Horizontal);
    sliderMemory->setRange(0, 200);
    sliderMemory->setTickInterval(20);
    sliderMemory->setValue(painter->sizeOfMemory);
    sliderMemory->setTickPosition(QSlider::TicksAbove);
    QObject::connect(sliderMemory, SIGNAL(valueChanged(int)), this, SLOT(changeSizeMemory(int)));
    hLayout->addWidget(sliderMemory);

    pStartStop = new QPushButton(QObject::tr("Запустить"));
    pStartStop->setFixedWidth(200);
    QObject::connect(pStartStop, SIGNAL(clicked()), this, SLOT(visualizerStartStop()));
    hLayout->addWidget(pStartStop);

    hLayout->addWidget(new QLabel(QObject::tr("Время моделирования:")));
    QSpinBox *sTotalTime = new QSpinBox(this);
    sTotalTime->setValue((int) painter->totalTime);
    sTotalTime->setRange(0, 600);
    sTotalTime->setSuffix(QObject::tr(" c"));
    QObject::connect(sTotalTime, SIGNAL(valueChanged(int)), this, SLOT(changeTotalTime(int)));
    hLayout->addWidget(sTotalTime);

    pStartFromStart = new QPushButton(QObject::tr("Начать с начала"));
    pStartFromStart->setFixedWidth(200);
    QObject::connect(pStartFromStart, SIGNAL(clicked()), this, SLOT(visualizerStartFromStart()));
    hLayout->addWidget(pStartFromStart);
    hLayout->addWidget(new QSplitter());

    this->setLayout(hLayout);
}

SettingTotal::~SettingTotal()
{
    delete pStartStop;
    delete pStartFromStart;
}

void SettingTotal::changeSizeMemory(int _count)
{
    painter->sizeOfMemory = _count + 1;
}

void SettingTotal::visualizerStartStop()
{
    if(isStart)
    {
        painter->tTime->stop();

        pStartStop->setText(QObject::tr("Запустить"));
    }
    else
    {
        painter->tTime->start((int) (100.0));

        pStartStop->setText(QObject::tr("Остановить"));

    }
    isStart = !isStart;
}

void SettingTotal::changeTotalTime(int _count)
{
    painter->totalTime = (float) _count;
}

void SettingTotal::visualizerStartFromStart()
{
    painter->time = (float) 0.0;
    painter->repaint();
}