#include "../Common/ReplyObjectHeaders/messageerror.h"

MessageError::MessageError():returnCode(2)
{
}

MessageError::MessageError(int rc)
    :returnCode(rc){}

MessageError::~MessageError(){}

int MessageError::getReturnCode(){
    return this->returnCode;
}

QString MessageError::toXML(){
    return "<MessageError returnCode=\""+QString::number(returnCode)+"\" />";
}
