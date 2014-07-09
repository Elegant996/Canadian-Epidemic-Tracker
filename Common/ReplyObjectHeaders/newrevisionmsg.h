#ifndef NEWREVISIONMSG_H
#define NEWREVISIONMSG_H

#include "reply.h"
#include "QString"

class NewRevisionMsg : public Reply
{
public:
    NewRevisionMsg();
    NewRevisionMsg(QString);
    ~NewRevisionMsg();


    QString getRevNum();
    virtual QString toXML();

private:
    QString revNum;
};

#endif // NEWREVISIONMSG_H
