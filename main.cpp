#include <QtGui/QApplication>
#include "widget.h"
#include <mcheck.h>

int main(int argc, char *argv[])
{
    mtrace();
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
    muntrace();
}
