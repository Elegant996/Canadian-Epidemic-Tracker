#include "../Common/include/DiseaseCase.h"
#include <QDebug>
#include <string>

DiseaseCase::DiseaseCase(int id, int type, int quantity,float lon, float lat, QDate theDate)
    :Trackables(id,type,quantity,lon,lat,theDate) {
}

DiseaseCase::~DiseaseCase() {

}

int DiseaseCase::getID() {
    return this->ID;
}

QString DiseaseCase::print()
{
    QString returnString = "Disease: ID: ";
    returnString += QString::number(this->getID());
    returnString += " Type: ";
    returnString += QString::number(this->getType());
    returnString +=  " Location: ";
    //returnString += this->location->getCity();
    returnString += " Quantity: ";
    returnString += QString::number(this->Quantity);
    returnString += " Date: ";
    returnString += this->getDate().toString("ddd MMMM d yyyy");
    return returnString;
}

// function to take the object and convert it to XML for the message
QString DiseaseCase::toXML(){
    qDebug()<<"trying to convert to xml";
    QString deID;
    if(this->getID()==NULL){
        deID = "new";
    }
    else
        deID = "de" + QString::number(this->getID());

    QString theString ="<DiseaseEntry diseaseEntryID=\"";
            theString+= deID;
            theString+= "\"><DiseaseTypeID>dt";
            theString+= QString::number(this->getType());
            theString+= "</DiseaseTypeID><Location><latitude>";
            //theString+= QString::number(this->getLocation()->getLat());
            theString+= "</latitude><longitude>";
            //theString+= QString::number(this->getLocation()->getLong());
            theString+= "</longitude></Location><Date>";
            theString+= this->getDate().toString(Qt::ISODate);
            theString+= "</Date><incidents>";
            theString+= QString::number(this->getQuantity());
            theString+= "</incidents></DiseaseEntry>";

            return theString;
}
