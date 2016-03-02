#include "multilateration.h"

MultiLateration::MultiLateration(QWidget *parent)
    : QMainWindow(parent)
{
#ifdef Q_OS_WIN         /// Widnows
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp-1251"));
#elif defined Q_OS_UNIX /// Linux
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
#endif

    painter = new Painter;
    settingLok = new SettingLok(painter);
    settingRoc = new SettingRoc(painter);
    settingTotal = new SettingTotal(painter);

    setCentralWidget(painter);

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

MultiLateration::~MultiLateration()
{
    delete settingLok;
    delete settingRoc;
    delete settingTotal;
    delete painter;
}
