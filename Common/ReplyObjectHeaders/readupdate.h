#ifndef READUPDATE_H
#define READUPDATE_H

#include "reply.h"

#include <QString>

class ReadUpdate : public Reply
{
public:
    ReadUpdate();
    ReadUpdate(QString,QString);
    ~ReadUpdate();

    QString getSessionID();
    QString getClientRevision();
    virtual QString toXML();

private:
    QString sessionID;
    QString clientRev;

};

#endif // READUPDATE_H
