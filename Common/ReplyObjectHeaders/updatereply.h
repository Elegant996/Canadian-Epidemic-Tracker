#ifndef UPDATEREPLY_H
#define UPDATEREPLY_H

#include "reply.h"
#include "../include/DiseaseType.h"
#include "../include/SupplyType.h"
#include "../include/DiseaseCase.h"
#include "../include/Shipment.h"
#include "../include/Supply.h"


#include <QList>
#include <QString>


class UpdateReply : public Reply
{
public:
    UpdateReply();
    //getters

    QList<DiseaseType*> getD_Types();
    QList<SupplyType*> getS_Types();
    QList<DiseaseCase*> getD_Cases();
    QList<Shipment*> getShipments();
    QList<Supply*> getSupplyUpdates();

    //add to lists
    void addDType(DiseaseType*);
    void addDTypeList(QList<DiseaseType*>*);
    void addSType(SupplyType*);
    void addSTypeList(QList<SupplyType*>*);
    void addDCase(DiseaseCase*);
    void addDCaseList(QList<DiseaseCase*>*);
    void addShipment(Shipment*);
    void addShipmentList(QList<Shipment*>*);
    void addSupplyUpdate(Supply*);
    void addSupplyUpdateList(QList<Supply*>*);

    virtual QString toXML();

private:

    QList<DiseaseType*> dTypes;
    QList<SupplyType*> sTypes;
    QList<DiseaseCase*> dCases;
    QList<Shipment*> shipments;
    QList<Supply*> supplyUpdates;

};

#endif // UPDATEREPLY_H
