#-------------------------------------------------
#
# Project created by QtCreator 2010-11-23T15:49:44
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

TARGET = CET_Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Server.cpp \
    ThreadProcessor.cpp \
    data.cpp \
    ../Common/City.cpp \
    ../Common/SupplyType.cpp \
    ../Common/DiseaseType.cpp \
    ../Common/Trackables.cpp \
    ../Common/Shipment.cpp \
    ../Common/handler.cpp \
    ../Common/Parser.cpp \
    ../Common/DiseaseCase.cpp \
    ../Common/Supply.cpp \
    ../Common/ReplyObjectSource/writeupdatereply.cpp \
    ../Common/ReplyObjectSource/writeupdate.cpp \
    ../Common/ReplyObjectSource/updatereply.cpp \
    ../Common/ReplyObjectSource/reply.cpp \
    ../Common/ReplyObjectSource/readupdatereply.cpp \
    ../Common/ReplyObjectSource/readupdate.cpp \
    ../Common/ReplyObjectSource/newrevisionmsg.cpp \
    ../Common/ReplyObjectSource/messageerror.cpp \
    ../Common/ReplyObjectSource/logoutreply.cpp \
    ../Common/ReplyObjectSource/logoutmsg.cpp \
    ../Common/ReplyObjectSource/loginreply.cpp \
    ../Common/ReplyObjectSource/loginmsg.cpp

HEADERS += \
    Server.h \
    ThreadProcessor.h \
    data.h \
    ../Common/include/City.h \
    ../Common/include/Supply.h \
    ../Common/include/SupplyType.h \
    ../Common/include/DiseaseType.h \
    ../Common/include/Shipment.h \
    ../Common/include/Parser.h \
    ../Common/include/Handler.h \
    ../Common/include/DiseaseCase.h \
    ../Common/ReplyObjectHeaders/writeupdatereply.h \
    ../Common/ReplyObjectHeaders/writeupdate.h \
    ../Common/ReplyObjectHeaders/updatereply.h \
    ../Common/ReplyObjectHeaders/reply.h \
    ../Common/ReplyObjectHeaders/readupdatereply.h \
    ../Common/ReplyObjectHeaders/readupdate.h \
    ../Common/ReplyObjectHeaders/newrevisionmsg.h \
    ../Common/ReplyObjectHeaders/messageerror.h \
    ../Common/ReplyObjectHeaders/logoutreply.h \
    ../Common/ReplyObjectHeaders/logoutmsg.h \
    ../Common/ReplyObjectHeaders/loginreply.h \
    ../Common/ReplyObjectHeaders/loginmsg.h
