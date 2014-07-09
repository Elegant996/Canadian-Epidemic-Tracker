
#include "include/ShipmentCriteria.h"



ShipmentCriteria::ShipmentCriteria()
{
    startDate.setDate(1500,1,1);
    endDate.setDate(3000,1,1);
    minQuantity = 0;
    maxQuantity = 99999999;

}

bool ShipmentCriteria::addSenders(QList<City*> citiesToAdd)
{
    for(int i = 0; i < citiesToAdd.count();i++)
    {
        addSender(citiesToAdd.at(i));
    }
    return true;
}
bool ShipmentCriteria::addSender(City* cityToAdd)
{
    senders.insert(0,cityToAdd);
    return true;
}
QList<City*> ShipmentCriteria::getSenderList()
{
    return senders;
}
QList<QString> ShipmentCriteria::getSenderCityNames()
{
    return senderCityNames;
}
bool ShipmentCriteria::addSender(QString cityName)
{
    senderCityNames.insert(0,cityName);
    return true;
}

bool ShipmentCriteria::addDestinations(QList<City*> citiesToAdd)
{
    for(int i = 0; i < citiesToAdd.count();i++)
    {
        addDestination(citiesToAdd.at(i));
    }
    return true;
}
bool ShipmentCriteria::addDestination(City* cityToAdd)
{
    destinations.append(cityToAdd);
    return true;
}
bool ShipmentCriteria::addDestination(QString cityName)
{
    this->destinationCityNames.insert(0,cityName);
    return true;
}

QList<City*> ShipmentCriteria::getDestinationList()
{
    return destinations;
}
QList<QString> ShipmentCriteria::getDestinationCityNames()
{
    return this->destinationCityNames;
}

bool ShipmentCriteria::addTypes(QList<int> typesToAdd)
{
    for(int i = 0;i < typesToAdd.count();i++)
    {
    addType(typesToAdd.at(i));
    }
}

bool  ShipmentCriteria::addType(QString typeToAdd)
{
    this->typeNames.insert(0,typeToAdd);
}

QList<QString>  ShipmentCriteria::getTypeNames()
{
    return this->typeNames;
}

bool ShipmentCriteria::addType(int typeToAdd)
{
    types.append(typeToAdd);
}
QList<int> ShipmentCriteria::getTypeList()
{
    return types;
}
bool ShipmentCriteria::setStartDate(QDate newStartDate)
{
    startDate = newStartDate;
    if(endDate < startDate)
    {
        endDate = startDate;
    }
    else
    {
        startDate = newStartDate;
    }
    return true;
}
QDate ShipmentCriteria::getStartDate()
{
    return startDate;
}
bool ShipmentCriteria::setEndDate(QDate newEndDate)
{
    endDate = newEndDate;
    if(endDate < startDate)
    {
        startDate = endDate;
    }else
    {
        endDate = newEndDate;
    }
    return true;
}
QDate ShipmentCriteria::getEndDate()
{
    return endDate;
}
bool ShipmentCriteria::setMaxQuantity(int newMax)
{
    if(newMax < 0)
    {
       maxQuantity = 0;
    }
    if(maxQuantity < minQuantity)
    {
        minQuantity = maxQuantity;
    }else
    {
        maxQuantity = newMax;
    }
    return true;
}
bool ShipmentCriteria::setMinQuantity(int newMin)
{
    if(newMin < 0)
    {
       minQuantity = 0;
    }
    if(maxQuantity < minQuantity)
    {
        maxQuantity == minQuantity;
    }else
    {
        minQuantity = newMin;
    }
    return true;
}
int ShipmentCriteria::getMinQuantity()
{
   return minQuantity;
}
int ShipmentCriteria::getMaxQuantity()
{
    return maxQuantity;
}
bool ShipmentCriteria::addShipmentStatus(Shipment::SHIPMENT_STATUS newStatus)
{
    status.append(status);
    return true;
}
QList<Shipment::SHIPMENT_STATUS> ShipmentCriteria::getStatus()
{
    return status;
}
