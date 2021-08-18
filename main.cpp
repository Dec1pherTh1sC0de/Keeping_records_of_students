#include "form1.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    form1 w;
    w.show();
    return a.exec();
}
