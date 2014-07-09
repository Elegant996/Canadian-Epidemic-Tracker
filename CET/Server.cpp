#include "include/Server.h"

Server::Server(ConnectionManagement* value, QObject* parent) : CM(value), QTcpServer(parent) {
    listen(QHostAddress::Any, 10521);
    qDebug() << "Listening on port" << this->serverPort();
 }

Server::~Server() {
}

void Server::incomingConnection(int socketDescriptor) {
    qDebug() << "Incoming connection";
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(readyRead()), this, SLOT(processClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(removeClient()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));
}

void Server::processClient() {
    qDebug() << "Data received";

    QString msg, type;
    QByteArray buffer;
    buffer = socket->readAll();
    msg = buffer;
    p.parse(msg);
    qDebug() << msg;
    type = typeid(*(p.getReply())).name();

    if (type.contains("LoginReply"))
       handleLoginReply();

    processComplete(); // If we can get here we're good

    /*qint16 size;
    QString msg;
    QByteArray buffer;
    qDebug() << "avaliable on start" << socket->bytesAvailable();
    buffer = socket->readAll(); qDebug() << "read to buffer" << buffer.size();
    qDebug() << "availiable now" << socket->bytesAvailable();
    QDataStream in (buffer);
    in >> size; qDebug() << "size" << size;
    in >> msg; qDebug() << "msg" << msg;*/
}

void Server::processComplete() {
    qDebug() << "I am all done!";
}

void Server::removeClient() {
    socket = (QTcpSocket*)sender();
    socket->deleteLater();
    qDebug() << "IP:" << socket->peerAddress().toString() << "disconnected";
}

void Server::socketError(QAbstractSocket::SocketError error)
{
    if (error != 1)
        qDebug() << error;
}

void Server::handleLoginReply() {
    CM->setSID(dynamic_cast<LoginReply*>(p.getReply())->getSID());
    CM->setLoginStatus(true);
}
