#ifndef LOGINREPLY_H
#define LOGINREPLY_H

#include "reply.h"
#include <QString>

class LoginReply : public Reply
{
public:
    LoginReply();
    LoginReply(int, int=0, int=0);
    ~LoginReply();

    int getReturnCode();
    int getSID();
    int getAuthLevel();
virtual QString toXML();

private:
    int returnCode;
    int sID;
    int authLevel;

};

#endif // LOGINREPLY_H
