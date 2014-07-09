#include "../Common/include/City.h"

City::City(QString province, QString city, float la, float lon)
    : Province(province), Town(city),lat(la),lng(lon){}

QString City::getCity(){
    return this->Town;
}

void City::setCity(QString city){
    this->Town=city;
}

QString City::getProvince() {
    return this->Province;
}

void City::setProvince(QString province) {
    this->Province = province;
}

float City::getLat(){
    return this->lat;
}

void City::setLat(float l){
    this->lat=l;
}

float City::getLong(){
    return this->lng;
}

void City::setLong(float l){
    this->lng=l;
}

QString City::printCity() {
    QString retString;
    retString = QString("City: %1").arg(this->getCity(),10);
    retString += QString("Province: %1").arg(this->getProvince(),10);
    retString += QString("Latitude: %1 Longitude %2").arg(this->lat,7).arg(this->lng,7);
    return retString;
}
