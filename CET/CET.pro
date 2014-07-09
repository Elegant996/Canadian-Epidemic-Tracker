#-------------------------------------------------
#
# Project created by QtCreator 2010-11-11T15:29:59
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

TARGET = CET
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    UIDrawHelper.cpp \
    ListContainer.cpp \
    DataDisplay.cpp \
    User.cpp \
    DiseaseCriteria.cpp \
    SupplyCriteria.cpp \
    ShipmentCriteria.cpp \
    Model.cpp \
    ClientParser.cpp \
    ShipmentSettings.cpp \
    ../Common/Trackables.cpp \
    ../Common/SupplyType.cpp \
    ../Common/Supply.cpp \
    ../Common/Shipment.cpp \
    ../Common/Parser.cpp \
    ../Common/handler.cpp \
    ../Common/DiseaseType.cpp \
    ../Common/DiseaseCase.cpp \
    ../Common/City.cpp \
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
    ../Common/ReplyObjectSource/loginmsg.cpp \
    Server.cpp \
    ConnectionManagement.cpp \
    Inventorysettings.cpp

LIBS += -L/usr/lib -lmarblewidget

HEADERS  += MainWindow.h \
    include/User.h \
    include/UIDrawHelper.h \
    include/Trackables.h \
    include/SupplyType.h \
    include/SupplyCriteria.h \
    include/Supply.h \
    include/ShipmentCriteria.h \
    include/Shipment.h \
    include/ServerParser.h \
    include/Server.h \
    include/SearchCriteria.h \
    include/Parser.h \
    include/Model.h \
    include/ListContainer.h \
    include/DiseaseType.h \
    include/DiseaseCriteria.h \
    include/DataDisplay.h \
    include/ConnectionManagement.h \
    include/ClientParser.h \
       include/City.h \
    include/Handler.h \
    include/reply.h \
    include/loginreply.h \
    include/logoutreply.h \
    include/updatereply.h \
    include/newrevisionmsg.h \
    include/ReplyObjectHeaders/updatereply.h \
    include/ReplyObjectHeaders/reply.h \
    include/ReplyObjectHeaders/newrevisionmsg.h \
    include/ReplyObjectHeaders/logoutreply.h \
    include/ReplyObjectHeaders/loginreply.h \
    include/ReplyObjectHeaders/writeupdatereply.h \
    include/ReplyObjectHeaders/messageerror.h \
    include/ReplyObjectHeaders/loginmsg.h \
    include/ReplyObjectHeaders/readupdate.h \
    include/ReplyObjectHeaders/writeupdate.h \
    include/ReplyObjectHeaders/logoutmsg.h \
    include/ReplyObjectHeaders/readupdatereply.h \
    include/data.h \
    ShipmentSettings.h \
    ../Common/include/DiseaseCase.h \
    ../Common/include/DiseaseType.h \
    ../Common/include/Trackables.h \
    ../Common/include/SupplyType.h \
    ../Common/include/Supply.h \
    ../Common/include/Shipment.h \
    ../Common/include/Parser.h \
    ../Common/include/Handler.h \
    ../Common/include/City.h \
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
    ../Common/ReplyObjectHeaders/loginmsg.h \
    Inventorysettings.h

FORMS    += MainWindow.ui \
    ShipmentSettings.ui \
    Inventorysettings.ui
