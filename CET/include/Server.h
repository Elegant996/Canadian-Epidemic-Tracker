#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <typeinfo>
#include "../Common/include/Parser.h"
#include "include/ConnectionManagement.h"

class ConnectionManagement;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(ConnectionManagement* value, QObject* parent = 0);
    ~Server();

signals:

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void processClient();
    void processComplete();
    void removeClient();
    void socketError(QAbstractSocket::SocketError error);

private:
    void handleLoginReply();

    ConnectionManagement* CM;
    Parser p;
    QTcpSocket* socket;
};

#endif // SERVER_H
