#include "sdimain.h"

SDImain::SDImain(QWidget *parent)
    : QMainWindow(parent)
{
    model = new Model;
    settingLok = new SettingLok(model);
    settingRoc = new SettingRoc(model);
    settingTotal = new SettingTotal(model);

    setCentralWidget(model);

    QDockWidget *dSettingForLoc = new QDockWidget(this);
    dSettingForLoc->setWidget(settingLok);
    dSettingForLoc->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dSettingForLoc->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, dSettingForLoc);

    QDockWidget *dSettingRoc = new QDockWidget(this);
    dSettingRoc->setWidget(settingRoc);
    dSettingRoc->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    dSettingRoc->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, dSettingRoc);

    QToolBar *tSettingTotal = new QToolBar(this);
    tSettingTotal->addWidget(settingTotal);
    tSettingTotal->setMovable(false);
    addToolBar(tSettingTotal);
}

SDImain::~SDImain()
{
    delete settingRoc;
    delete settingLok;
    delete model;
}
