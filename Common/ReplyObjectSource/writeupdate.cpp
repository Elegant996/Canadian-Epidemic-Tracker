#include "../Common/ReplyObjectHeaders/writeupdate.h"

WriteUpdate::WriteUpdate()
{
}

WriteUpdate::WriteUpdate(QString sID, QString cr)
    :sessionID(sID),clientRevision(cr){}

//getters
QString WriteUpdate::getClientRevision(){
    return this->clientRevision;
}

QString WriteUpdate::getSessionID(){
    return this->sessionID;
}

//set revision info
void WriteUpdate::setClientRevision(QString cr){
    this->clientRevision=cr;
}

void WriteUpdate::setSessionID(QString sID){
    this->sessionID=sID;
}

QString WriteUpdate::toXML(){
    return "WriteUpdate sessionID=\"" + sessionID + "\" clientRevision=\"" + clientRevision + "\">";
}
