#include "isensor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ISensor w;
    w.show();

    return a.exec();
}
