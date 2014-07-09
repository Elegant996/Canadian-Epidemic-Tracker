#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QtDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>
#include <QSqlField>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "../Common/include/City.h"
#include "../Common/include/SupplyType.h"
#include "../Common/include/DiseaseType.h"
#include "../Common/include/DiseaseCase.h"
#include "../Common/include/Shipment.h"
#include "../Common/include/Supply.h"
#include "../Common/include/Trackables.h"
#include "../Common/ReplyObjectHeaders/updatereply.h"

class data
{
public:
    data();
    ~data();
    int findLatestRev();
    void setLatestRev(int);
    int getLatestRev();

    void add(City*);
    void add(QList<City*>);
    void add(SupplyType*);
    void add(QList<SupplyType *>);
    void add(DiseaseType*);
    void add(QList<DiseaseType*>);
    void add(DiseaseCase*);
    void add(QList<DiseaseCase*>);
    void add(Shipment*);
    void add(QList<Shipment*>);
    void add(Supply*);
    void add(QList<Supply*>);
    void fill();
    City* getCity(float,float);
    QList<City*>* getCitiesUpdate(int revNum);
    QList<SupplyType*>* getSupplyTypeUpdate(int revNum);
    QList<DiseaseType*>* getDiseaseTypeUpdate(int revNum);
    QList<DiseaseCase*>* getDiseaseCaseUpdate(int revNum);
    QList<Shipment*>* getShipmentUpdate(int revNum);
    QList<Supply*>* getSupplyUpdate(int revNum);
    UpdateReply* getUpdate(int);

    void readCities( const QString &fileName );
    QStringList cities;
    void readSupplyType( const QString &fileName );
    QStringList supplyTypes;
    void readDiseaseType( const QString &fileName );
    QStringList diseaseTypes;
bool sortHelper( const QString &s1, const QString &s2 ) ;

static QString getCityName(float,float);

private:
   QSqlDatabase db;
   int latestRev;

};

#endif // DATA_H
