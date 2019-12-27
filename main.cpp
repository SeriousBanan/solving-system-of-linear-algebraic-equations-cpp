#include "slae.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SLAE w;
    w.show();
    return a.exec();
}


