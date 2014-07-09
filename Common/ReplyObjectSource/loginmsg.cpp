#include "../Common/ReplyObjectHeaders/loginmsg.h"

LoginMsg::LoginMsg():user("i'm a user"),pass("this is my password"){}

LoginMsg::LoginMsg(QString u,QString p)
    :user(u),pass(p){}

LoginMsg::~LoginMsg(){}

QString LoginMsg::getUser(){
    return this->user;
}

QString LoginMsg::getPass(){
    return this->pass;
}

QString LoginMsg::toXML(){
    return "<Login><userName>" + user + "</userName><password>" + pass + "</password></Login>";
}


