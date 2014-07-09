#include "../Common/ReplyObjectHeaders/readupdate.h"

ReadUpdate::ReadUpdate(){}

ReadUpdate::ReadUpdate(QString s, QString cr)
    :sessionID(s), clientRev(cr){}

ReadUpdate::~ReadUpdate(){}

QString ReadUpdate::getSessionID(){
    return this->sessionID;
}

QString ReadUpdate::getClientRevision(){
    return this->clientRev;
}

QString ReadUpdate::toXML(){
    return "<ReadUpdate sessionID=\"" + sessionID + "\" clientRevision =\"" + clientRev + "\" />";
}
