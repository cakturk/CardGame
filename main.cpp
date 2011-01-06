#include <QtGui/QApplication>
#include "widget.h"

#ifdef LOGGING
#include <iostream>
#include <fstream>
using namespace std;

ofstream logfile;
void myMessageHandler(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        logfile << QTime::currentTime().toString("HH:mm-ss").toAscii().data()
                << " Debug: " << msg << '\n';
        break;
    case QtCriticalMsg:
        logfile << QTime::currentTime().toString("HH:mm-ss").toAscii().data()
                << " Critical: " << msg << '\n';
        break;
    case QtWarningMsg:
        logfile << QTime::currentTime().toString("HH:mm-ss").toAscii().data()
                << " Warning: " << msg << '\n';
        break;
    case QtFatalMsg:
        logfile << QTime::currentTime().toString("HH:mm-ss").toAscii().data()
                << " Fatal: " << msg << '\n';
        abort();
    }
}
#endif

int main(int argc, char *argv[])
{
#ifdef LOGGING
    logfile.open("/home/cihangir/logfile.txt", ios::app);
    qInstallMsgHandler(myMessageHandler);
#endif
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
