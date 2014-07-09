#ifndef LOGOUTREPLY_H
#define LOGOUTREPLY_H

#include "reply.h"

class LogoutReply : public Reply
{
public:
    LogoutReply();
    LogoutReply(int);
    ~LogoutReply();

    int getReturnCode();
    virtual QString toXML();

private:
    int retCode;

};

#endif // LOGOUTREPLY_H
