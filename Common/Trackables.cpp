#include "../Common/include/Trackables.h"
#include "../Common/include/City.h"
#include <QDate>


Trackables::Trackables( int id, int type, int quantity, float lon,float lat, QDate date) : ID(id), Type(type),
Quantity(quantity), longitude(lon),latitude(lat), theDate(date){}

Trackables::~Trackables() {

}

int Trackables::getType() {
    return Type;
}

int Trackables::getQuantity() {
    return Quantity;
}


void Trackables::setType(int type){
    this->Type = type;

}

float Trackables::getLon()
{
    return this->longitude;
}
void  Trackables::setLon(float newLon)
{
    this->longitude = newLon;
}
float Trackables::getLat()
{
    return this->latitude;
}
void  Trackables::setLat(float newLat)
{
    this->latitude = newLat;
}

void Trackables::setQuantity(int q){

    this->Quantity = q;
    if(Quantity < 0){this->Quantity = 0;}
}


int Trackables::getID(){
    return this->ID;
}

QDate Trackables::getDate(){
    return theDate;
}

void Trackables::setDate(QDate date){
    if(date > QDate::currentDate())
    {
        date = QDate::currentDate();
        return;
    }
    this->theDate=date;
}

