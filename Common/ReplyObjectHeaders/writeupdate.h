#ifndef WRITEUPDATE_H
#define WRITEUPDATE_H

#include "reply.h"
#include "../include/DiseaseType.h"
#include "../include/SupplyType.h"
#include "../include/DiseaseCase.h"
#include "../include/Shipment.h"
#include "../include/Supply.h"


#include <QList>
#include <QString>


class WriteUpdate : public Reply
{
public:
    WriteUpdate();
    WriteUpdate(QString,QString);



    //getters
    QString getClientRevision();
    QString getSessionID();

    //set revision info
    void setClientRevision(QString);
    void setSessionID(QString);


    //add to lists

    virtual QString toXML();

private:
    QString sessionID;
    QString clientRevision;
};

#endif // WRITEUPDATE_H
