#include "multilateration.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MultiLateration multiLateration;
    multiLateration.showMaximized();

    return a.exec();
}
