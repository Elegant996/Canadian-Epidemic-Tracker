#include "../Common/ReplyObjectHeaders/logoutmsg.h"

LogoutMsg::LogoutMsg():sID(0)
{
}

LogoutMsg::LogoutMsg(int id)
    :sID(id){}

LogoutMsg::~LogoutMsg(){}

int LogoutMsg::getSID(){
    return this->sID;
}

QString LogoutMsg::toXML(){
    return "<Logout sessionID=\"sid" + QString::number(sID) + "\" />";
}
