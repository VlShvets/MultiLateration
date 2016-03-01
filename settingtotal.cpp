#include "settingtotal.h"

SettingTotal::SettingTotal(Model *_model, QWidget *parent) :
    QWidget(parent)
{
    this->model = _model;

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(new QSplitter());
    hLayout->addWidget(new QLabel(QObject::tr("Длина следа:")));

    QSlider *sliderMemory = new QSlider(Qt::Horizontal);
    sliderMemory->setRange(0, 200);
    sliderMemory->setTickInterval(20);
    sliderMemory->setValue(model->sizeOfMemory);
    sliderMemory->setTickPosition(QSlider::TicksAbove);
    QObject::connect(sliderMemory, SIGNAL(valueChanged(int)), this, SLOT(changeSizeMemory(int)));
    hLayout->addWidget(sliderMemory);

    pStartStop = new QPushButton(QObject::tr("Запустить"));
    pStartStop->setFixedWidth(200);
    QObject::connect(pStartStop, SIGNAL(clicked()), this, SLOT(visualizerStartStop()));
    hLayout->addWidget(pStartStop);

    hLayout->addWidget(new QLabel(QObject::tr("Время моделирования:")));
    QSpinBox *sTotalTime = new QSpinBox(this);
    sTotalTime->setValue((int) model->totalTime);
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
    model->sizeOfMemory = _count + 1;
}

void SettingTotal::visualizerStartStop()
{
    if(isStart)
    {
        model->tTime->stop();

        pStartStop->setText(QObject::tr("Запустить"));
    }
    else
    {
        model->tTime->start((int) (100.0));

        pStartStop->setText(QObject::tr("Остановить"));

    }
    isStart = !isStart;
}

void SettingTotal::changeTotalTime(int _count)
{
    model->totalTime = (float) _count;
}

void SettingTotal::visualizerStartFromStart()
{
    model->time = (float) 0.0;
    model->repaint();
}
