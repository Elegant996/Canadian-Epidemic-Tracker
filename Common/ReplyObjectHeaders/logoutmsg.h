#ifndef LOGOUTMSG_H
#define LOGOUTMSG_H

#include "reply.h"
#include <QString>

class LogoutMsg : public Reply
{
public:
    LogoutMsg();
    LogoutMsg(int);
    ~LogoutMsg();
    int getSID();
    virtual QString toXML();


private:
    int sID;
};

#endif // LOGOUTMSG_H
