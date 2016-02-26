#include <QApplication>

#include "multilateration.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MultiLateration multilateration;
    multilateration.showMaximized();

    return a.exec();
}
