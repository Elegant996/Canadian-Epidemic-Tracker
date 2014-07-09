#include "include/DiseaseCriteria.h"
#include <QDebug>

DiseaseCriteria::DiseaseCriteria()
{
        minQuantity = 0;
        maxQuantity = 99999999;
        startDate = QDate::currentDate();
        startDate.setDate(1500,1,1);
        endDate.setDate(3000,1,1);

}
bool DiseaseCriteria::addDiseaseTypeList(QList<int> listToAdd)
{
    for(int i = 0; i < listToAdd.count();i++)
    {
        addDiseaseType(listToAdd.at(i));
    }
    return true;
}
void DiseaseCriteria::addDiseaseType(int diseaseToAdd)
{

    types.insert(types.size(), diseaseToAdd);

}
void DiseaseCriteria::addDiseaseType(QString diseaseName){
  typeNames.insert(0,diseaseName);
}
QList<QString> DiseaseCriteria::getDiseaseTypeNames()
{
    return this->typeNames;
}
QList<int> DiseaseCriteria::getDiseaseTypeList()
{

    return this->types;
}
bool DiseaseCriteria::addCity(QString cityToAdd)
{
    cityNames.insert(0, cityToAdd);
    return true;
}
bool DiseaseCriteria::addCity(City *cityToAdd)
{
    this->locations.insert(0,cityToAdd);
    return true;
}

QList<City*> DiseaseCriteria::getLocationList()
{
    return locations;
}
QList<QString> DiseaseCriteria::getCityNames()
{
    return this->cityNames;
}
bool DiseaseCriteria::setStartDate(QDate newStartDate)
{
    startDate = newStartDate;
    if(endDate < startDate)
    {
        endDate = startDate;
    }else
    {
        startDate = newStartDate;
    }
    return true;
}
QDate DiseaseCriteria::getStartDate()
{
    return startDate;
}
bool DiseaseCriteria::setEndDate(QDate newEndDate)
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
QDate DiseaseCriteria::getEndDate()
{
    return endDate;
}
bool DiseaseCriteria::setMaxQuantity(int newMax)
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
bool DiseaseCriteria::setMinQuantity(int newMin)
{
    if(newMin < 0)
    {
       minQuantity = 0;
    }
    if(maxQuantity < minQuantity)
    {
        maxQuantity = minQuantity;
    }else
    {
        minQuantity = newMin;
    }
    return true;
}
int DiseaseCriteria::getMinQuantity()
{
   return minQuantity;
}
int DiseaseCriteria::getMaxQuantity()
{
    return maxQuantity;
}
QString DiseaseCriteria::print()
{
    QString returnString;
    returnString = QString("Printing Disease Searching Criteria\n");
    returnString += QString("Printing City Criterias\n");
    foreach(City *c, this->locations)
    {
        returnString += c->printCity();
        returnString += "\n";
    }
    returnString += QString("Printing City Names Criteria\n");
    foreach(QString c, this->cityNames)
    {
        returnString += QString("%1, ").arg(c);
    }

    returnString += QString("\nDisease TypeID Numbers;");
    foreach(int t, this->types)
    {
        returnString += QString(" %1,").arg(QString::number(t));
    }
    returnString += QString("\nDisease Type Names:");
    foreach(QString t, this->typeNames)
    {
       returnString += QString(" %1,").arg(t);
    }

    returnString += QString("\nDate Range: %1 to %2").arg(this->startDate.toString("ddd MMMM d yyyy")).arg(this->endDate.toString("ddd MMMM d yyyy"));
    returnString += QString("\nQuantity Range: %1 to %2").arg(this->minQuantity).arg(QString::number(this->maxQuantity));

    return returnString;
}
