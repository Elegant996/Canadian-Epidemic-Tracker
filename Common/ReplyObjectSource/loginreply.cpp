#include "../Common/ReplyObjectHeaders/loginreply.h"

LoginReply::LoginReply()
{  returnCode = 0;
    sID = 0;
    authLevel =0;
}

LoginReply::~LoginReply(){

}

LoginReply::LoginReply(int rc,int s, int a)
        :returnCode(rc), sID(s), authLevel(a){}


int LoginReply::getReturnCode(){
    return this->returnCode;
}

int LoginReply::getSID(){
    return this->sID;
}

int LoginReply::getAuthLevel(){
    return this->authLevel;
}

QString LoginReply::toXML(){
    return "<LoginReply returnCode=\"" + QString::number(returnCode) + "\" sessionID=\"sid"
            + QString::number(sID) + "\"><authLevel>"+ QString::number(authLevel) + "</authLevel></LoginReply>";

}
