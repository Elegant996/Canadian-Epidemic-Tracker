#ifndef SERVER_H
#define SERVER_H

#include <QThreadPool>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "ThreadProcessor.h"
#include "data.h"
#include "../Common/include/Parser.h"
#include "../Common/ReplyObjectHeaders/reply.h"
#include "../Common/ReplyObjectHeaders/loginmsg.h"
#include "../Common/ReplyObjectHeaders/logoutmsg.h"
#include "../Common/ReplyObjectHeaders/loginreply.h"
#include "../Common/ReplyObjectHeaders/logoutreply.h"
#include "../Common/ReplyObjectHeaders/readupdate.h"
#include "../Common/ReplyObjectHeaders/writeupdate.h"
#include "../Common/ReplyObjectHeaders/readupdatereply.h"
#include "../Common/ReplyObjectHeaders/writeupdatereply.h"

const unsigned int numberOfThreads = 5;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject* parent = 0);
    ~Server();

signals:

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void processClient();
    void processComplete(Reply* reply);
    //void removeClient();
    void socketError(QAbstractSocket::SocketError error);

private:
    class ClientInfo
    {
    public:
        ClientInfo(int id, QString address)
        {
            SessionID = id;
            IP = address;
            PORT = 10521;
        }
        ~ClientInfo() { }

    public:
        int SessionID;
        QString IP;
        int PORT;
    };

    void handleLogin();
    void handleLogout(LogoutMsg* logoutMsg);
    void handleReadUpdate(ReadUpdate* readUpdate);
    void handleWriteUpdate(WriteUpdate* writeUpdate);
    bool validClient(int sid);

    int session;
    data database;
    ClientInfo* clientInfo;
    QTcpSocket* socket;
    QThreadPool threadPool;
    QList<ClientInfo*> clientList;
};

#endif // SERVER_H
