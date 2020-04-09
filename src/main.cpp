#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QApplication::setApplicationName("Slider App Demo");
    QApplication::setOrganizationName("org.keshavnrj.ubuntu");
    QApplication::setApplicationVersion("1");

    return a.exec();
}
