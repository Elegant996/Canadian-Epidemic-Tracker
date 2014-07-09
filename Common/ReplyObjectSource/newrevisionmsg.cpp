
#include "../Common/ReplyObjectHeaders/newrevisionmsg.h"

NewRevisionMsg::NewRevisionMsg()
{
}

NewRevisionMsg::NewRevisionMsg(QString rNum)
    :revNum(rNum){}

NewRevisionMsg::~NewRevisionMsg(){}


QString NewRevisionMsg::getRevNum(){
    return this->revNum;
}

QString NewRevisionMsg::toXML(){
    return "<NewRevision serverRevision=\"rev" + revNum + "\" />";
}
