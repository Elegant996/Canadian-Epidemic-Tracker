#include "../Common/include/Shipment.h"

Shipment::Shipment() {

}

Shipment::Shipment(int shipmentID, int type, SHIPMENT_STATUS Status, int shipmentQuantity,float senderLon,float senderLat,
                   float destinationLon,float destinationLat, QDate CreatedDate,
                   QDate sentDate, QDate eDate, QDate receivedDate):ID(shipmentID),type(type), currentStatus(Status),
                    destinationLongitude(destinationLon),destinationLatitude(destinationLat),
                    senderLongitude(senderLon),senderLatitude(senderLat),
                    quantity(shipmentQuantity), expectedDate(eDate),sentDate(sentDate),
                    receivedDate(receivedDate),createdDate(CreatedDate){}

int Shipment::getID() { return ID; }

int Shipment:: getType() { return type; }
void Shipment::setType(int newType){this->type = newType;}

int Shipment::getQuantity() { return quantity;}
void Shipment::setQuantity(int newQuantity){
    if(newQuantity < 0)
    {
        this->quantity = 0;
    }
    this->quantity = newQuantity;
}

Shipment::SHIPMENT_STATUS Shipment::getCurrentStatus(){return this->currentStatus;}
void Shipment::setCurrentStatus(SHIPMENT_STATUS newStatus){this->currentStatus = newStatus;}

QDate Shipment::getExpectedDate(){
    return this->expectedDate;
}

void Shipment::setExpectedDate(QDate eDate){

    this->expectedDate=eDate;
}

QDate Shipment::getSentDate(){
    return this->sentDate;
}

void Shipment::setSentDate(QDate sDate){
    if(sDate > QDate::currentDate())
    {
        sDate = QDate::currentDate();
    }
    this->sentDate=sDate;
}

QDate Shipment::getCreatedDate(){
    return this->createdDate;
}

void Shipment::setCreatedDate(QDate cDate){
    if(cDate > QDate::currentDate())
    {
        cDate = QDate::currentDate();
    }
    this->createdDate=cDate;
}

QDate Shipment::getReceivedDate(){
    return this->receivedDate;
}

void Shipment::setReceivedDate(QDate rDate){
    if(rDate > QDate::currentDate())
    {
        rDate = QDate::currentDate();
    }
    this->receivedDate=rDate;
}

float Shipment::getSenderLon()
{
    return this->senderLongitude;
}
void  Shipment::setSenderLon(float newLon)
{
    this->senderLongitude = newLon;
}
float Shipment::getSenderLat()
{
    return this->senderLatitude;
}
void  Shipment::setSenderLat(float newLat)
{
    this->senderLatitude = newLat;
}
float Shipment::getRecieverLon()
{
    return this->destinationLongitude;
}
void  Shipment::setRecieverLon(float newLon)
{
    this->destinationLongitude = newLon;
}
float Shipment::getRecieverLat()
{
    return this->destinationLatitude;
}
void  Shipment::setRecieverLat(float newLat)
{
    this->destinationLatitude = newLat;
}
void Shipment::send(){
}
QString Shipment::print()
{

    QString returnString =  QString("%1").arg("Shipment: ID: ");
     returnString += QString("%1").arg(QString::number(this->ID),5);
     returnString += QString(" Type: %1").arg(QString::number(this->type),3);
     returnString += QString(" Origin: Lon:%1 Lat %2").arg(this->senderLongitude,8).arg(this->senderLatitude,8);
     returnString += " Destination: ";
     returnString +=QString(" Dest: Lon:%1 Lat %2 Quantity ").arg(this->destinationLongitude,8).arg(this->destinationLatitude,8);
     returnString += QString::number(this->quantity);

            if(this->currentStatus ==   this->RECEIVED
                ||this->currentStatus == this->SENT
                ||this->currentStatus == this->PREPARED)
            {

                returnString += "\n Created Date:";
                returnString += this->getCreatedDate().toString("ddd MMMM d yy");

            }
             if(this->currentStatus ==   this->RECEIVED
                ||this->currentStatus == this->SENT)
             {
                returnString    += " Sent Date:" ;
                returnString    += this->getSentDate().toString("ddd MMMM d yy");
             }
             if(this->currentStatus == this->RECEIVED)
             {
             returnString += " Recieved Date: ";
             returnString += this->getReceivedDate().toString("ddd MMMM d yy");

             }
             return returnString;
}

void Shipment::receive(){
}

QString Shipment::toXML(){
    QString shID;
    if(this->getID()==NULL){
        shID = "new";
    }
    else{
        shID = "sh" + QString::number(this->getID());
    }
    QString theString ="<Shipment shipmentID =\"";
            theString+= shID;
                theString+= "\"><ShipmentOrigin><Location><longitude>";
                    theString+= QString::number(this->getSenderLon());
                theString+= "</longitude><latitude>";
                    theString+= QString::number(this->getSenderLat());
                theString+= "</latitude></Location></ShipmentOrigin><ShipmentDestination><Location><longitude>";
                    theString+= QString::number(this->getRecieverLon());
                theString+= "</longitude><latitude>";
                    theString+= QString::number(this->getRecieverLat());
                theString+= "</latitude></Location></ShipmentDestination><SupplyTypeID>st";
                    theString+= QString::number(this->getType());
                theString+= "</SupplyTypeID><quantity>";
                    theString+= QString::number(this->getQuantity());
                theString+= "</quantity><ExpectedDate>";
                    theString+= this->getExpectedDate().toString(Qt::ISODate);
                theString+= "</ExpectedDate><ShipmentStatus><Created><Date>";
                    theString+= this->getCreatedDate().toString(Qt::ISODate);
                theString+= "</Date></Created>";
              if (this->getCurrentStatus()== Shipment::RECEIVED){
                theString += "<Sent><Date>";
                theString += this->getSentDate().toString(Qt::ISODate);
                theString += "</Date></Sent><Received><Date>";
                theString += this->getReceivedDate().toString(Qt::ISODate);
                theString += "</Date></Received>";
            }
            else if (this->getCurrentStatus()== Shipment::SENT){
                theString += "<Sent><Date>";
                theString += this->getSentDate().toString(Qt::ISODate);
                theString += "</Date></Sent>";
            }
            theString+= "</ShipmentStatus></Shipment>";

            return theString;

}
