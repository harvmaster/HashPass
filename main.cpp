#include "MainDialog.h"
#include <QApplication>

#include <QEvent>
#include <QTimer>
#include <QObject>

int main(int argc, char *argv[])
{
    // Create application
    QApplication a(argc, argv);

    // Create dialog
    MainDialog w;
    w.exec();

    // (HACK) Wait 1 second so that hash can copy into clipboard (if we exit straight away, it doesn't make it)
    QTimer *timer = new QTimer(&a);
    timer->start(1000);
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()), Qt::QueuedConnection);

    // Enter main application loop
    return a.exec();
}
