#include "Server.h"

Server::Server(QObject* parent) : QTcpServer(parent) {
    listen(QHostAddress::Any, 10520);
    qDebug() << "Listening on port" << this->serverPort();
    session = 1001;
 }

Server::~Server() {
    if (clientInfo)
        delete clientInfo;
}

void Server::incomingConnection(int socketDescriptor) {
    qDebug() << "Incoming connection";
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    /*
    clientInfo = new ClientInfo(session, socket->peerAddress().toString());
    session++;
    //clientList.append(socket);
    clientList.append(clientInfo);
    qDebug() << "IP:" << clientInfo->IP << "connected, given session number" << clientInfo->SessionID;
    */
    connect(socket, SIGNAL(readyRead()), this, SLOT(processClient()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(removeClient()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
}

void Server::processClient() {
    //socket = static_cast<QTcpSocket *>(sender());
    ThreadProcessor *threadProcessor = new ThreadProcessor(socket);//->socketDescriptor());
    connect(threadProcessor, SIGNAL(processComplete(Reply*)), this, SLOT(processComplete(Reply*)));
    threadPool.start(threadProcessor);
}

void Server::processComplete(Reply* reply) {
    QString type = typeid(*(reply)).name();

    if (type.contains("LoginMsg"))
        handleLogin();
    else if (type.contains("LogoutMsg"))
        handleLogout(dynamic_cast<LogoutMsg*>(reply));
    else if (type.contains("ReadUpdate"))
        handleReadUpdate(dynamic_cast<ReadUpdate*>(reply));
    else if (type.contains("WriteUpdate"))
        handleWriteUpdate(dynamic_cast<WriteUpdate*>(reply));
}

void Server::handleLogin() {
    clientInfo = new ClientInfo(session, socket->peerAddress().toString()); // Create new Client
    session++; // Increase Session ID for next user
    clientList.append(clientInfo); // Add new Client to List

    LoginReply* loginReply = new LoginReply(0, clientInfo->SessionID, 0);
    QByteArray arr;
    arr = loginReply->toXML().toAscii().append('\0');
    socket->write(arr);
    while(socket->bytesToWrite() > 0)
    {
       socket->waitForBytesWritten();
    }
    socket->deleteLater();
}

void Server::handleLogout(LogoutMsg* logoutMsg) {
    ClientInfo* tmp;
    foreach(ClientInfo* client, clientList)
        if (client->SessionID == logoutMsg->getSID())
        {
            tmp = client;
            break;
        }
        clientList.removeOne(tmp);

    LogoutReply* logoutReply = new LogoutReply();
    QByteArray arr;
    arr = logoutReply->toXML().toAscii().append('\0');
    socket->write(arr);
    while(socket->bytesToWrite() > 0)
    {
       socket->waitForBytesWritten();
    }
    socket->deleteLater();
}

void Server::handleReadUpdate(ReadUpdate* readUpdate) {
    QByteArray arr;
    if (!validClient(readUpdate->getSessionID().remove("sid").toInt()))
    {
        MessageError* mError = new MessageError(100);
        arr = mError->toXML().toAscii().append('\0');
    } else {
        ReadUpdateReply* readUpdateReply = new ReadUpdateReply(readUpdate->getClientRevision(),"rev" +QString::number(database.getLatestRev()),0);
        UpdateReply* update = database.getUpdate(readUpdate->getClientRevision().remove("rev").toInt());
        qDebug()<<"client revision"<< readUpdate->getClientRevision();

        QString msg = readUpdateReply->toXML() + update->toXML() + "</ReadUpdateReply>";
        arr = msg.toAscii().append('\0');
        //qDebug()<<msg;
    }
    socket->write(arr);
    while(socket->bytesToWrite() > 0)
    {
       socket->waitForBytesWritten();
    }
    socket->deleteLater();
}

void Server::handleWriteUpdate(WriteUpdate* writeUpdate) {

}

bool Server::validClient(int sid) {
    foreach(ClientInfo* client, clientList)
        if (client->SessionID == sid)
            return true;

    return false;
}

/*
void Server::removeClient() {
    socket = (QTcpSocket*)sender();
    //clientList.removeOne(socket);
    clientList.removeOne(clientInfo);
    socket->deleteLater();
    qDebug() << "IP:" << socket->peerAddress().toString() << "disconnected";
}
*/

void Server::socketError(QAbstractSocket::SocketError error)
{
    /*
    if (error == 1)
    {
        socket = (QTcpSocket*)sender();
        qDebug() << socket->peerAddress().toString();
        socket->deleteLater();
    } else */
        qDebug() << error;
}
