#include <QApplication>
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server* server;
    server = new Server();


    return a.exec();
}
