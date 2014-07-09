#ifndef MESSAGEERROR_H
#define MESSAGEERROR_H

#include "reply.h"

class MessageError : public Reply
{
public:
    MessageError();
    MessageError(int);
    ~MessageError();

    int getReturnCode();
    virtual QString toXML();

private:
    int returnCode;


};

#endif // MESSAGEERROR_H
