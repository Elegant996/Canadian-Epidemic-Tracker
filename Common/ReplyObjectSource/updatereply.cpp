#include "../Common/ReplyObjectHeaders/updatereply.h"

UpdateReply::UpdateReply()
{
}

//getters


QList<DiseaseType*> UpdateReply::getD_Types(){
    return this->dTypes;
}

QList<SupplyType*> UpdateReply::getS_Types(){
    return this->sTypes;
}

QList<DiseaseCase*> UpdateReply::getD_Cases(){
    return this->dCases;
}


QList<Shipment*> UpdateReply::getShipments(){
    return this->shipments;
}

QList<Supply*> UpdateReply::getSupplyUpdates(){
    return this->supplyUpdates;
}



//add to lists
void UpdateReply::addDType(DiseaseType* dt){
    this->dTypes.append(dt);
}

void UpdateReply::addDTypeList(QList<DiseaseType *>* dtList){
    foreach (DiseaseType* dt, *dtList){
        this->addDType(dt);
    }
}

void UpdateReply::addSType(SupplyType* st){
    this->sTypes.append(st);
}

void UpdateReply::addSTypeList(QList<SupplyType *> * STList){
    foreach(SupplyType* st, *STList){
        this->addSType(st);
    }
}

void UpdateReply::addDCase(DiseaseCase* dc){
    this->dCases.append(dc);
}

void UpdateReply::addDCaseList(QList<DiseaseCase *> *DCList){
    foreach(DiseaseCase* dc, *DCList){
        this->addDCase(dc);
    }
}

void UpdateReply::addShipment(Shipment* s){
    this->shipments.append(s);
}

void UpdateReply::addShipmentList(QList<Shipment *> * ShipList){
    foreach(Shipment* s, *ShipList){
        this->addShipment(s);
    }
}

void UpdateReply::addSupplyUpdateList(QList<Supply *> * suList){
    foreach(Supply* s, *suList){
        this->addSupplyUpdate(s);
    }
}

void UpdateReply::addSupplyUpdate(Supply* su){
    this->supplyUpdates.append(su);
}

QString UpdateReply::toXML(){
    QString reply;
    reply.append("<CETUpdateList>");
    foreach(DiseaseType* dt, dTypes){
        reply.append("<CETUpdate>");
        reply.append(dt->toXML());
        reply.append("</CETUpdate>");
    }
    foreach(SupplyType* st, sTypes){
        reply.append("<CETUpdate>");
        reply.append(st->toXML());
        reply.append("</CETUpdate>");
    }
    foreach(DiseaseCase* dc, dCases){
        reply.append("<CETUpdate>");
        reply.append(dc->toXML());
        reply.append("</CETUpdate>");
    }
    foreach(Shipment* s, shipments){
        reply.append("<CETUpdate>");
        reply.append(s->toXML());
        reply.append("</CETUpdate>");
    }
    foreach(Supply* s, supplyUpdates){
        reply.append("<CETUpdate>");
        reply.append(s->toXML());
        reply.append("</CETUpdate>");
    }
    reply.append("</CETUpdateList>");
    return reply;
}
