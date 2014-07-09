#include "../Common/include/SupplyType.h"

SupplyType::SupplyType(int typeID, QString name) {
    this->typeId = typeID;
    this->name = name;
}

QString SupplyType::getName() {
    return name;
}

int SupplyType::getTypeID(){
    return typeId;
}
bool SupplyType::overwriteWith(SupplyType *newData)
{
    this->name = newData->getName();
    this->typeId = newData->typeId;

    return true;
}
QString SupplyType::toXML()
{
    QString theString = "<SupplyType supplyTypeID =\"st";
    theString += QString::number(this->getTypeID());
        theString += "\"><supplyName>";
            theString += this->getName();
        theString += "</supplyName>";
    theString += "</SupplyType>";

    return theString;

}
