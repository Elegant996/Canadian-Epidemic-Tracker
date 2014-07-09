#ifndef LOGINMSG_H
#define LOGINMSG_H

#include "reply.h"

#include <QString>

class LoginMsg : public Reply
{
public:
    LoginMsg();
    LoginMsg(QString,QString);
    ~LoginMsg();

    QString getUser();
    QString getPass();
virtual QString toXML();
private:
    QString user;
    QString pass;

};

#endif // LOGINMSG_H
