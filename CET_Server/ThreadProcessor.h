#ifndef THREADPROCESSOR_H
#define THREADPROCESSOR_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QRunnable>
#include <QDebug>
#include <typeinfo>
#include "../Common/include/Parser.h"
#include "../Common/ReplyObjectHeaders/reply.h"

class ThreadProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ThreadProcessor(QTcpSocket* s);
    ~ThreadProcessor();

signals:
    void processComplete(Reply* reply);

public slots:

protected:
    void run();

private:
    QTcpSocket* socket;
    Parser p;
};

#endif // THREADPROCESSOR_H
