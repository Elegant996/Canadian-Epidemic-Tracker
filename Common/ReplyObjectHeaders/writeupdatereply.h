#ifndef WRITEUPDATEREPLY_H
#define WRITEUPDATEREPLY_H

#include "reply.h"

class WriteUpdateReply : public Reply
{
public:
    WriteUpdateReply();
    WriteUpdateReply(int);
    ~WriteUpdateReply();

    int getRetCode();
virtual QString toXML();
private:
    int retCode;
};

#endif // WRITEUPDATEREPLY_H
