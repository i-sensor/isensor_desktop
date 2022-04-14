#include "isensor.h"
#include <QApplication>

#include "HomeScreen/HomeScreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ISensor w;
    //w.show();
    HomeScreen s;
    s.show();

    return a.exec();
}
