#include "../Common/ReplyObjectHeaders/readupdatereply.h"

ReadUpdateReply::ReadUpdateReply()
{
}

ReadUpdateReply::ReadUpdateReply(QString rs,QString re, int rc)
    :revStart(rs),revEnd(re),retCode(rc){}

ReadUpdateReply::~ReadUpdateReply(){}

//getters
QString ReadUpdateReply::getStart(){
    return this->revStart;
}

QString ReadUpdateReply::getEnd(){
    return this->revEnd;
}

int ReadUpdateReply::getRetCode(){
    return this->retCode;
}

//set revision info
void ReadUpdateReply::setRevStart(QString start){
    this->revStart=start;
}

void ReadUpdateReply::setRevEnd(QString end){
    this->revEnd=end;
}

void ReadUpdateReply::setRetCode(int rc){
    this->retCode=rc;
}

QString ReadUpdateReply::toXML(){
    return "<ReadUpdateReply returnCode=\"" + QString::number(retCode) + "\" revisionStart=\"" + revStart + "\" revisionEnd=\"" + revEnd + "\">";
 }
