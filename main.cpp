#include <QApplication>

#include "sdimain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SDImain sdimain;
    sdimain.showMaximized();

    return a.exec();
}
