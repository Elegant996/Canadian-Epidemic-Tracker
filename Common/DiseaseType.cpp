#include "../Common/include/DiseaseType.h"


DiseaseType::DiseaseType(int typeID, QString name) {
    this->dTypeId = typeID;
    this->name = name;
}

QString DiseaseType::getName() {
    return name;
}

int DiseaseType::getTypeID(){
    return dTypeId;
}
bool DiseaseType::overwriteWith(DiseaseType *newData)
{
    this->name = newData->name;
    this->dTypeId = newData->dTypeId;

    return true;
}

QString DiseaseType::toXML()
{
    QString theString =  "<DiseaseType diseaseTypeID =\"dt";
                theString += QString::number(this->dTypeId);
                    theString += "\"><diseaseName>";
                        theString += this->getName();
                    theString += "</diseaseName>";
                theString += "</DiseaseType>";
    return theString;
}
