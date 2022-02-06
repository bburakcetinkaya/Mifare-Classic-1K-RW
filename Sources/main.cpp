#include "Headers\mainwindow.h"
#include "Headers/textwindow.h"
#include "Headers\connect.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
