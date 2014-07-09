#ifndef CITY_H
#define CITY_H

#include <QString>

class City
{
public:
    City() {}
    City(QString province, QString city, float la, float lon);
    QString getCity();
    void setCity(QString city);
    QString getProvince();
    void setProvince( QString province );
    float getLat();
    void setLat(float);
    float getLong();
    void setLong(float);
    QString printCity();

private:
    QString Province;
    QString Town;
    float lat;
    float lng;
};
#endif // CITY_H
