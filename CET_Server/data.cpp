#include "data.h"

data::data()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "myDB.sqlite" );
    if( !db.open() )
    {
        qDebug() << "Not opened"; //db.lastError();
        qFatal( "Failed to connect." );
    }

    QSqlQuery qry;

    //create SupplyType table

    if( !qry.exec( "CREATE TABLE IF NOT EXISTS 'SupplyType' ('ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , 'Name' CHAR NOT NULL, 'Revision' INTEGER NOT NULL)" ))
        qDebug() << "error creating Supply table"; //qry.lastError();
    else
        qDebug() << "Supply Table created!";

    //create DiseaseType table

    if( !qry.exec( "CREATE TABLE IF NOT EXISTS 'DiseaseType' ('ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , 'Name' CHAR NOT NULL, 'Revision' INTEGER NOT NULL)" ))
        qDebug() << "error creating Disease table";
    else
        qDebug() << "Disease Table created!";

    //create Disease case table
    if(!qry.exec("CREATE TABLE IF NOT EXISTS 'DiseaseCases' ('ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , 'Type' INTEGER NOT NULL , 'Quantity' INTEGER NOT NULL , 'Lat' FLOAT NOT NULL , 'long' FLOAT NOT NULL , 'Date' DATETIME NOT NULL, 'Revision' INTEGER NOT NULL )")){
        qDebug() << "error creating DiseaseCases table";
    }else{
        qDebug() << "DiseaseCases Table created!";
    }

    //create Inventory table
    if(!qry.exec("CREATE TABLE IF NOT EXISTS 'Inventory' ('ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , 'Type' INTEGER NOT NULL , 'Quantity' INTEGER NOT NULL , 'Lat' FLOAT NOT NULL , 'long' FLOAT NOT NULL , 'Date' DATETIME NOT NULL, 'Revision' INTEGER NOT NULL )")){
        qDebug() << "error creating DiseaseCases table";
    }else{
        qDebug() << "Inventory Table created!";
    }

    //create shipment table
    if(!qry.exec("CREATE TABLE IF NOT EXISTS 'Shipments' ('ID' INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , 'Type' INTEGER NOT NULL , 'Status' CHAR NOT NULL , 'Quantity' INTEGER NOT NULL, 'Revision' INTEGER NOT NULL , 'OriginLat' FLOAT, 'OriginLong' FLOAT, 'DestLat' REAL, 'DestLong' FLOAT, 'Expected' DATETIME, 'Created' DATETIME, 'Sent' DATETIME, 'Received' DATETIME)")){
        qDebug() << "error creating Shipments table";
    }else{
        qDebug() << "Shipments Table created!";
    }

    //Create Cities table
    if(!qry.exec("CREATE TABLE IF NOT EXISTS 'Cities' ('Province' CHAR, 'City' CHAR, 'Lat' FLOAT NOT NULL , 'Long' FLOAT NOT NULL, 'Revision' INTEGER NOT NULL , PRIMARY KEY ('Lat', 'Long'))")){
        qDebug() << "error creating Cities table";
    }else{
        qDebug() << "Cities Table created!";
    }
    //set current revision
    fill();
    setLatestRev(findLatestRev());

}

data::~data(){
    db.close();
}

void data::setLatestRev(int lr){
    this->latestRev=lr;
}

int data::getLatestRev(){
    return this->latestRev;
}

int data::findLatestRev(){
    int x=0;
    QSqlQuery qry;
    if(!qry.exec("SELECT MAX ('Revision') from 'Cities'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    if(!qry.exec("SELECT MAX ('Revision') from 'SupplyType'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    if(!qry.exec("SELECT MAX ('Revision') from 'DiseaseType'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    if(!qry.exec("SELECT MAX ('Revision') from 'DiseaseCases'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    if(!qry.exec("SELECT MAX ('Revision') from 'Inventory'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    if(!qry.exec("SELECT MAX ('Revision') from 'Shipments'")){
        qDebug() << "can't get max";
    }
    else{
        while(qry.next()){
            if(qry.value(0).toInt()>x)
                x=qry.value(0).toInt();
        }
    }
    return x;
}


// inserting a city into the database

//deal with revision number

void data::add(City *newCity){
    QSqlQuery query;
    query.prepare("REPLACE INTO Cities (Province, City, Lat,Long,Revision)"
                  "VALUES (:Province, :City, :Lat,:Long,:Revision)");
    query.bindValue(":Province", newCity->getProvince());
    query.bindValue(":City", newCity->getCity());
    query.bindValue(":Lat", newCity->getLat());
    query.bindValue(":Long", newCity->getLong());
    query.bindValue("Revision", getLatestRev());
    if(!query.exec()){
        qDebug() << "couldnt insert city" << newCity->getCity();
    }
}

//insert a list of citys
void data::add(QList<City*> cList){
    foreach(City* c, cList){
        add(c);
    }
}

//Inserting supplytype
void data::add(SupplyType* st){
    QSqlQuery query;
    query.prepare("REPLACE INTO SupplyType (ID, Name, Revision)"
                  "VALUES (:ID, :Name, :Revision)");
    if(st->getTypeID() != NULL){
        query.bindValue(":ID", st->getTypeID());
    }
    query.bindValue(":Name", st->getName());
    query.bindValue("Revision", getLatestRev());
    if (!query.exec())
        qDebug()<< "can't insert SupplyType";
}


//insert list of supplytypes
void data::add(QList<SupplyType*> stList){
    foreach(SupplyType* st, stList){
        add(st);
    }
}

//Inserting Diseasetype
void data::add(DiseaseType* dt){
    QSqlQuery query;
    query.prepare("REPLACE INTO DiseaseType (ID, Name, Revision)"
                  "VALUES (:ID, :Name, :Revision)");
    if(dt->getTypeID()!=NULL){
        query.bindValue(":ID", dt->getTypeID());
    }
    query.bindValue(":Name", dt->getName());
    query.bindValue("Revision", getLatestRev());
    if (!query.exec())
        qDebug()<< "can't insert DiseaseType";
}

//inserting DiseaseType List
void data::add(QList<DiseaseType*> dtList){
    foreach (DiseaseType* dt, dtList){
        add(dt);
    }
}

//inserting DiseaseCase
void data::add(DiseaseCase* dc){
    QSqlQuery query;
    query.prepare("REPLACE INTO DiseaseCases (ID, Type, Quantity, Lat, long, Date, Revision)"
                  "VALUES (:ID, :Type, :Quantity, :Lat, :long, :Date, :Revision)");
    if(dc->getID()!=NULL){
        query.bindValue(":ID", dc->getID());
    }
    query.bindValue(":Type", dc->getType());
    query.bindValue(":Quantity", dc->getQuantity());
    query.bindValue(":Lat",dc->getLat());
    query.bindValue(":long", dc->getLon());
    query.bindValue(":Date", dc->getDate().toString(Qt::ISODate));
    query.bindValue(":Revision", getLatestRev());
    if(!query.exec()){
        qDebug() << "can't insert DiseaseCase";
    }
}

void data::add(QList<DiseaseCase *> dcList){
    foreach(DiseaseCase* dc, dcList){
        add(dc);
    }
}

void data::add(Shipment * s){
    QSqlQuery query;
    query.prepare("REPLACE INTO Shipments(ID, Type, Status, Quantity, Revision, OriginLat, OriginLong, DestLat, DestLong, Expected, Created, Sent, Received)"
                  "Values(:ID, :Type, :Status, :Quantity, :Revision, :OriginLat, :OriginLong, :DestLat, :DestLong, :Expected, :Created, :Sent, :Received)");
    if(s->getID()!=NULL){
        query.bindValue(":ID", s->getID());
    }
    query.bindValue(":Type",s->getType());
    query.bindValue(":Status",s->getCurrentStatus());
    query.bindValue(":Quantity",s->getQuantity());
    query.bindValue(":Revision", getLatestRev());
    query.bindValue(":OriginLat",s->getSenderLat());
    query.bindValue(":OriginLong", s->getSenderLon());
    query.bindValue(":DestLat",s->getRecieverLat());
    query.bindValue(":DestLong",s->getRecieverLon());
    query.bindValue(":Expected", s->getExpectedDate().toString(Qt::ISODate));
    query.bindValue(":Created",s->getCreatedDate().toString(Qt::ISODate));
    query.bindValue(":Sent",s->getSentDate().toString(Qt::ISODate));
    query.bindValue(":Received",s->getReceivedDate().toString(Qt::ISODate));
    if(!query.exec()){
        qDebug()<< "can't insert shipment";
    }
}

void data::add(QList<Shipment *> sList){
    foreach(Shipment* s, sList){
        add(s);
    }
}

void data::add(Supply * s){
    QSqlQuery query;
    query.prepare("REPLACE INTO Inventory (ID, Type, Quantity, Lat, long, Date, Revision)"
                  "VALUES (:ID, :Type, :Quantity, :Lat, :long, :Date, :Revision)");
    if(s->getID()!=NULL){
        query.bindValue(":ID", s->getID());
    }
    query.bindValue(":Type", s->getType());
    query.bindValue(":Quantity", s->getQuantity());
    query.bindValue(":Lat",s->getLat());
    query.bindValue(":long",s->getLon());
    query.bindValue(":Date", s->getDate().toString(Qt::ISODate));
    query.bindValue(":Revision", getLatestRev());
    if(!query.exec()){
        qDebug() << "can't insert Inventory";
    }

}

void data::add(QList<Supply *> sList){
    foreach (Supply* s, sList){
        add(s);
    }
}

QString data::getCityName(float lat, float lng){
    City* city;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cities WHERE (Lat = :la) AND (long = :lng)");
    qry.bindValue(":la",lat);
    qry.bindValue(":lng",lng);

    if(!qry.exec()){
        qDebug() << "can't get CityName";
    }
    else{
        while(qry.next()){
            city = new City(qry.value(0).toString(),qry.value(1).toString(),qry.value(2).toFloat(),qry.value(3).toFloat());
        }
    }
    return city->getCity();

}

City* data::getCity(float lat, float lng){
    City* city;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cities WHERE (Lat = :la) AND (long = :lng)");
    qry.bindValue(":la",lat);
    qry.bindValue(":lng",lng);

    if(!qry.exec()){
        qDebug() << "can't get exec";
    }
    else{
        while(qry.next()){
            city = new City(qry.value(0).toString(),qry.value(1).toString(),qry.value(2).toFloat(),qry.value(3).toFloat());
        }
    }
    return city;

}
QList<City*>* data::getCitiesUpdate(int revNum){
    QList<City*>* cities = new QList<City*>();
    QSqlQuery query;
    query.prepare("SELECT * FROM Cities WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get cities rev list";
    }
    else{
        while(query.next()){
            cities->append(new City(query.value(0).toString(),query.value(1).toString(),query.value(2).toFloat(),query.value(3).toFloat()));
        }
    }
    return cities;
}

QList<SupplyType*>* data::getSupplyTypeUpdate(int revNum){
    QList<SupplyType*>* supplies = new QList<SupplyType*>();
    QSqlQuery query;
    query.prepare("SELECT * FROM SupplyType WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get supplyType rev list";
    }
    else{
        qDebug()<<"query size *************:"<< query.size();
        while(query.next()){
            supplies->append(new SupplyType(query.value(0).toInt(),query.value(1).toString()));
        }
    }
    return supplies;
}

QList<DiseaseType*>* data::getDiseaseTypeUpdate(int revNum){
    QList<DiseaseType*>* dTypes = new QList<DiseaseType*>();
    QSqlQuery query;
    query.prepare("SELECT * FROM DiseaseType WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get DiseaseType rev list";
    }
    else{
        while(query.next()){
            dTypes->append(new DiseaseType(query.value(0).toInt(),query.value(1).toString()));
        }
    }
    return dTypes;
}

QList<DiseaseCase*>* data::getDiseaseCaseUpdate(int revNum){
    QList<DiseaseCase*>* dCases = new QList<DiseaseCase*>();
    QSqlQuery query;

    query.prepare("SELECT * FROM DiseaseCases WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get DiseaseType rev list";
    }
    else{

        while(query.next()){
              dCases->append(new DiseaseCase(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toFloat(),query.value(4).toFloat(), query.value(5).toDate()));
        }
    }
    return dCases;
}

QList<Shipment*>* data::getShipmentUpdate(int revNum){
    QList<Shipment*>* shipments = new QList<Shipment*>();
    QSqlQuery query;
    query.prepare("SELECT * FROM Shipments WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get Shipment rev list";
    }
    else{
            while(query.next()){

            shipments->append(new Shipment(query.value(0).toInt(),query.value(1).toInt(),(Shipment::SHIPMENT_STATUS)(query.value(2).toInt()),query.value(3).toInt(),query.value(6).toFloat(),query.value(5).toFloat(),query.value(8).toFloat(),query.value(7).toFloat(),query.value(10).toDate(),query.value(11).toDate(),query.value(9).toDate(),query.value(12).toDate()));
        }
    }
    return shipments;
}

QList<Supply*>* data::getSupplyUpdate(int revNum){
    QList<Supply*>* supplys = new QList<Supply*>();
    QSqlQuery query;

    query.prepare("SELECT * FROM Inventory WHERE (Revision >= :rNum)");
    query.bindValue(":rNum", revNum);
    if(!query.exec()){
        qDebug()<<"Can't get Inventory rev list";
    }
    else{
        while(query.next()){
            supplys->append(new Supply(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(4).toFloat(),query.value(3).toFloat(), query.value(5).toDate()));
        }
    }
    return supplys;
}

UpdateReply* data::getUpdate(int rev){
    UpdateReply* update = new UpdateReply();
    update->addSTypeList(this->getSupplyTypeUpdate(rev));
    update->addDCaseList(this->getDiseaseCaseUpdate(rev));
    update->addDTypeList(this->getDiseaseTypeUpdate(rev));
    update->addShipmentList(this->getShipmentUpdate(rev));

    update->addSupplyUpdateList(this->getSupplyUpdate(rev));
    return update;
}
/*
  ====================================================================
  Functions to read from file
  ====================================================================
*/

bool data::sortHelper( const QString &s1, const QString &s2 ) {
    return (s1.toLower() < s2.toLower());
}

void data::readCities(const QString &fileName) {
    QFile file(fileName);
    QStringList tempList;
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
//        QMessageBox::warning(this, QObject::tr("Application"),
//                             QObject::tr( "Cannot read file %1:\n%2.")
//                             .arg(fileName)
//                             .arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    while( !in.atEnd() ) {
        // read in line by line
            cities += in.readLine(2000);
        //    qDebug() << "Add city: " << cities;
            // split the line by spaces
            QString sec1 = cities[0];
            tempList = sec1.split(",");
    /*        qDebug() << "TempList at 0: " << tempList.at(0);
            qDebug() << "TempList at 1: " << tempList.at(1);
            qDebug() << "TempList at 2: " << tempList.at(2);
            qDebug() << "TempList at 3: " << tempList.at(3);
            // entry 1 is for city name
            // entry 2 is for latitude
            // entry 3 is for longitude*/
            QString prov = tempList.at(0);

       //     qDebug() << "Prov is: " << prov;
            prov = prov.trimmed();
            QString cit = tempList.at(1);


        //    qDebug() << "city is: " << cit;
            cit = cit.trimmed();
            QString latitude = tempList.at(2);
            float lat = latitude.toFloat();
       //     qDebug() << "Lat: " << lat;

            QString longitude = tempList.at(3);
            float lon = longitude.toFloat();
      //      qDebug() << "Lon: " << lon;

            // insert the cities into the object
            City* aCity = new City(prov, cit, lat, lon);
           this->add(aCity);;
         //   qDebug() << "This city is:" << aCity->getProvince() << aCity->getCity() << aCity->getLat() << aCity->getLong();
            //listMap.insertMulti(aCity->getProvince(), aCity->getCity());
            cities.clear();
            tempList.clear();
    }

    //qSort( cities.begin(), cities.end(), sortHelper );
}

void data::readDiseaseType(const QString &fileName) {
    QFile file(fileName);
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
//        QMessageBox::warning(this, QObject::tr("Application"),
//                             QObject::tr( "Cannot read file %1:\n%2.")
//                             .arg(fileName)
//                             .arg(file.errorString()));
//        return;
    }
    QTextStream in(&file);
    while( !in.atEnd() ) {
        diseaseTypes += in.readLine(2000);
      //  qDebug() << "Add Disease types: " << diseaseTypes;
    }
    diseaseTypes.sort();
}

void data::readSupplyType(const QString &fileName) {
    QFile file(fileName);
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
//        QMessageBox::warning(this, QObject::tr("Application"),
//                             QObject::tr( "Cannot read file %1:\n%2.")
//                             .arg(fileName)
//                             .arg(file.errorString()));
//        return;
    }
    QTextStream in(&file);
    while( !in.atEnd() ) {
        supplyTypes += in.readLine(2000);


    //  qDebug() << "Add Supply types: " << supplyTypes;
    }
    supplyTypes.sort();
}

void data::fill()
{
    setLatestRev(0);
    // read in the cities file and add it to the listcontainer
    readCities("Locations.txt");

    // read in the disease types and store them in the container
    readDiseaseType("diseasetypes.ini");
    for( int i = 0; i < diseaseTypes.length(); i++ ) {
        DiseaseType* dType = new DiseaseType(i, diseaseTypes[i]);
        this->add(dType);
    }
    // read in the supply types and store them in the container
    readSupplyType("supplytypes.ini");
    for( int i = 0; i < supplyTypes.length(); i++ ) {
        SupplyType* sType = new SupplyType(i, supplyTypes[i]);
        this->add(sType);
    }

}
