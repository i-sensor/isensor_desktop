#include "isensor.h"
#include <QApplication>

#include "Header/Header.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ISensor w;
    //w.show();
    Header w;
    w.show();

    return a.exec();
}
