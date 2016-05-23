#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.set();
    w.setWindowTitle("Project");
    QIcon ico("fr.ico");
    w.setWindowIcon(ico);

    return a.exec();
}
