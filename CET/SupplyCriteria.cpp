#include "include/SupplyCriteria.h"

SupplyCriteria::SupplyCriteria()
{

    this->minSupplyQuantity = 0;
    this->maxSupplyQuantity = 99999999;
}

bool SupplyCriteria::addCriteriaCities(QList<City*> cityList)
{
    for(int i = 0; i < cityList.count(); i++)
    {
        this->locations.append(cityList.at(i));
    }
 return true;
}
bool SupplyCriteria::addCriteriaCity(City *city)
{
    locations.append(city);


 return true;
}
bool SupplyCriteria::addCity(QString cityName)
{
    this->cityNames.insert(0,cityName);
    return true;
}
QList<QString> SupplyCriteria::getCityNames()
{
    return cityNames;
}

bool SupplyCriteria::addCriteriaSupplyType(int newSupplyCriteria)
{
    supplyTypes.append(newSupplyCriteria);
 return true;
}
bool SupplyCriteria::addCriteriaSupplyType(QList<int> newSupplyCriteriaList)
{
    for(int i = 0; i < newSupplyCriteriaList.count(); i++)
    {
        supplyTypes.append(newSupplyCriteriaList .at(i));
    }
 return true;
}
bool SupplyCriteria::addCriteriaSupplyType(QString supplyTypeName)
{
    supplyTypeNames.insert(0,supplyTypeName);
    return true;
}
QList<City*> SupplyCriteria::getCriteriaLocations()
{
    return locations;
}
QList<int> SupplyCriteria::getCriteriaSupplyTypes()
{
    return supplyTypes;
}
QList<QString> SupplyCriteria::getCriteriaSupplyTypeNames()
{
    return this->supplyTypeNames;
}

int SupplyCriteria::getMin()
{
 return minSupplyQuantity;
}

bool SupplyCriteria::setMin(int newMin)
{
    if(newMin >= 0)
    {
        minSupplyQuantity = newMin;

    }
    if(minSupplyQuantity >= maxSupplyQuantity)
    {
        maxSupplyQuantity = minSupplyQuantity;
    }
    else
        {
            minSupplyQuantity = newMin;
        }
 return true;
}


int SupplyCriteria::getMax()
{
    return maxSupplyQuantity;
}

bool SupplyCriteria::setMax(int newMax)
{
    if(newMax >= 0)
    {
        maxSupplyQuantity = newMax;

    }
    if(maxSupplyQuantity <= minSupplyQuantity)
    {
       minSupplyQuantity =  maxSupplyQuantity;
    }
    else
    {
       this->maxSupplyQuantity = newMax;
    }
 return true;
}
