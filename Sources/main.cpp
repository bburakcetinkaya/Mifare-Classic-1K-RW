#include "Headers\mainwindow.h"
#include "Headers/textwindow.h"
#include "Headers\connect.h"
#include <Qt>
#include <QTimer>
#include <QThread>
#include <QWidget>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

//    QTimer* timer1 = new QTimer();

//        QThread* thread = new QThread();
//        Tester* tester = new Tester();

//        timer1->setInterval(500);
//        timer1->setSingleShot(false);
//        timer1->start();

//        QObject::connect(timer1, SIGNAL(timeout()), tester, SLOT(greet()));

//        timer1->moveToThread(thread);

//        thread->start();
    w.show();



    return a.exec();
}
