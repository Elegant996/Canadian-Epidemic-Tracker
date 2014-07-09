#ifndef READUPDATEREPLY_H
#define READUPDATEREPLY_H

#include "reply.h"

#include <QString>

class ReadUpdateReply : public Reply
{
public:


    ReadUpdateReply();
    ReadUpdateReply(QString,QString,int);
    ~ReadUpdateReply();
    QString getStart();
    QString getEnd();
    int getRetCode();
    virtual QString toXML();

    //set revision info
    void setRevStart(QString);
    void setRevEnd(QString);
    void setRetCode(int);

private:
    QString revStart;
    QString revEnd;
    int retCode;
};

#endif // READUPDATEREPLY_H
