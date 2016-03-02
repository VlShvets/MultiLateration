#ifndef MULTILATERATION_H
#define MULTILATERATION_H

#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QToolBar>
#include <QDockWidget>

#include "settinglok.h"
#include "settingroc.h"
#include "settingtotal.h"

class MultiLateration : public QMainWindow
{
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
