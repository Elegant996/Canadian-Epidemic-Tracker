#include "../Common/ReplyObjectHeaders/logoutreply.h"

LogoutReply::LogoutReply():retCode(0)
{
}

LogoutReply::LogoutReply(int rc)
    :retCode(rc){}

LogoutReply::~LogoutReply(){

}

int LogoutReply::getReturnCode(){
    return this->retCode;
}

QString LogoutReply::toXML(){
    return "<LogoutReply returnCode =\"" + QString::number(retCode) + "\" />";
}
