#include "../Common/ReplyObjectHeaders/writeupdatereply.h"

WriteUpdateReply::WriteUpdateReply():retCode(0)
{
}

WriteUpdateReply::WriteUpdateReply(int rc)
    :retCode(rc){}

WriteUpdateReply::~WriteUpdateReply(){}

int WriteUpdateReply::getRetCode(){
    return this->retCode;
}

QString WriteUpdateReply::toXML(){
    return "<WriteUpdateReply returnCode=\"" + QString::number(retCode) + "\" />";
}
