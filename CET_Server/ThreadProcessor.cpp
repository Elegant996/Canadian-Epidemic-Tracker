#include "ThreadProcessor.h"

ThreadProcessor::ThreadProcessor(QTcpSocket* s) {
    socket = s;
    //socket->setSocketDescriptor(descriptor);
}

ThreadProcessor::~ThreadProcessor() {

}

void ThreadProcessor::run() {
    qDebug() << "Data received";
    // qint16 size;
    QString msg;
    QByteArray buffer;
    //qDebug() << "avaliable on start" << socket->bytesAvailable();
    buffer = socket->readAll(); //qDebug() << "read to buffer" << buffer.size();
    //qDebug() << "availiable now" << socket->bytesAvailable();
    msg = buffer;
    //qDebug() << "Message was:" << msg;
    /*
    QDataStream in (buffer);
    in >> size; qDebug() << "size" << size;
    in >> msg; qDebug() << "msg" << msg;
    */
    p.parse(msg);

    /*
    QString type = typeid(*(p.getReply())).name();

    if (type == "8LoginMsg")
    {
        emit handleLogin(dynamic_cast<LoginMsg*>(p.getReply()));
        return;
    }
    else if (type == "9LogoutMsg")
        emit handleLogout(dynamic_cast<LogoutMsg*>(p.getReply()));
    */

    emit processComplete(p.getReply());
}
