#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(QDateTime::currentDateTime().toTime_t());
    Model* client= new Model();
    MainWindow w(0,client);
    w.show();

    return a.exec();
}
