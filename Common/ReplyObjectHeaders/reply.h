#ifndef REPLY_H
#define REPLY_H

#include <QString>

class Reply
{
public:
    Reply();
    virtual ~Reply();
    virtual QString toXML()=0;
};

#endif // REPLY_H
