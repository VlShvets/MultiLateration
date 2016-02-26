#ifndef MULTILATERATION_H
#define MULTILATERATION_H

#include <QMainWindow>
#include <QToolBar>
#include <QDockWidget>

#include "settinglok.h"
#include "settingroc.h"
#include "settingtotal.h"

class MultiLateration : public QMainWindow
{
    Q_OBJECT

public:
    MultiLateration(QWidget *parent = 0);
    ~MultiLateration();

private:
    Painter *painter;
    SettingLok *settingLok;
    SettingRoc *settingRoc;
    SettingTotal *settingTotal;
};

#endif // MULTILATERATION_H