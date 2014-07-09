#include "../Common/include/Supply.h"
#include <QDebug>

Supply::Supply(int id,int type,int quantity,float lon,float lat, QDate theDate)
    :Trackables(id,type,quantity,lon,lat,theDate)

{}

//copy constructor
Supply::Supply(const Supply &copySupply):
        Trackables(copySupply.ID,copySupply.Type,copySupply.Quantity, copySupply.longitude,copySupply.latitude, copySupply.theDate){}

Supply::~Supply(){}

int Supply::getID()
{
    return this->ID;

}
QString Supply::print()
{

    QString returnString = "Supply: ID: ";
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


QString Supply::toXML(){
    QString sID;
    if (this->getID()==NULL){
        sID = "new";
         }
    else{
        sID = "se" + QString::number(this->getID());
    }

    QString theString ="<SupplyEntry supplyEntryID =\"";
            theString+= sID;
            theString+= "\"><SupplyTypeID>st";
            theString+= QString::number(this->getType());
            theString+= "</SupplyTypeID><Location><latitude>";
            theString+= QString::number(this->getLat());
            theString+= "</latitude><longitude>";
            theString+= QString::number(this->getLon());
            theString+= "</longitude></Location><Date>";
            theString+= this->getDate().toString(Qt::ISODate);
            theString+= "</Date><quantity>";
            theString+= QString::number(this->getQuantity());
            theString+= "</quantity></SupplyEntry>";
   return theString;
}
