#ifndef SDIMAIN_H
#define SDIMAIN_H

#include <QMainWindow>
#include <QToolBar>
#include <QDockWidget>

#include "settinglok.h"
#include "settingroc.h"
#include "settingtotal.h"

class SDImain : public QMainWindow
{
    Q_OBJECT

public:
    SDImain(QWidget *parent = 0);
    ~SDImain();

private:
    Model *model;
    SettingLok *settingLok;
    SettingRoc *settingRoc;
    SettingTotal *settingTotal;
};

#endif // SDIMAIN_H
