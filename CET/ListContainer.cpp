//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : E-Healthcare-Canada
//  @ File Name : ListContainer.cpp
//  @ Date : 11/9/2010
//  @ Author :
//
//


#include "include/ListContainer.h"

ListContainer::ListContainer()
{

//    // read in the cities file and add it to the listcontainer
    /*readCities("Locations.txt");

    // read in the disease types and store them in the container
    readDiseaseType("diseasetypes.ini");
    for( int i = 0; i < diseaseTypes.length(); i++ ) {
        dType = new DiseaseType(i, diseaseTypes[i]);
        diseaseTypeList.insert(diseaseTypeList.size(),dType);
    }
    // read in the supply types and store them in the container
    readSupplyType("supplytypes.ini");
    for( int i = 0; i < supplyTypes.length(); i++ ) {
        sType = new SupplyType(i, supplyTypes[i]);
        supplyTypeList.insert(supplyTypeList.size(),sType);


    }*/
revNum = 0;

}
ListContainer::~ListContainer()
{
    /*if( dType != NULL ) {
        delete dType;
        dType = 0;
    }
    if( sType != NULL ) {
        delete sType;
        sType = 0;
    }*/
}

//adds a disease to the diseaseTypeList if it is unique and if not, the disease case with that id is overwritten
bool ListContainer::addDiseaseCase(DiseaseCase* diseaseCase)
{
     if(checkForDiseaseCase(diseaseCase)){
         changeDiseaseCase(diseaseCase);
         /*qDebug() << "adjusting DiseaseCase info: ID: " << diseaseCase->getID()
                 << " Type: " << diseaseCase->getType()
                 << " Quantity: " << diseaseCase->getQuantity()
                 << " City: " << diseaseCase->getLocation()->getCity()
                 << "Date:" << diseaseCase->getDate();*/
         return true;
     }
     else
     {
        diseaseCaseList.append(diseaseCase);
        /*qDebug() << "Appending DiseaseCase: ID: " << diseaseCase->getID()
                << " Type: " << diseaseCase->getType()
                << " Quantity: " << diseaseCase->getQuantity()
                << " City: " << diseaseCase->getLocation()->getCity()
                << "Date:" << diseaseCase->getDate();*/
        return false;
     }
}


//check to see if the supply type exists in a city.
//if it exists then it adjusts the inventory otherwise
//it appends the supply
bool ListContainer::addToSupply(Supply* aSupply){
    if (checkForExistingSupply(aSupply))
    {
         adjustSupply(aSupply);
    }else
    {
        supplyList.append(aSupply);
    }
        return false;

}



//finds and overwrites the data members of a supply with
//the same id in the supplyTypeList
bool ListContainer::adjustSupply(Supply* aSupply){
    foreach(Supply* s, supplyList){
        if(s->getID()==aSupply->getID()){

            s->setLon(aSupply->getLon());
            s->setLat(aSupply->getLat());
            s->setQuantity(aSupply->getQuantity());
            s->setType(aSupply->getType());
            return true;
        }
    }
        return false;
}
//checks for duplication, if unique, add to list
//if not unique overwrite duplicate
bool ListContainer::addShipment(Shipment* newShipment){
    if(checkforExistingShipment(newShipment)) {

        updateShipment(newShipment);
        return true;
    }
    else {
        shipmentList.append(newShipment);
        return true;
    }

}






bool ListContainer::addDiseaseType(DiseaseType* newDiseaseIntoList){
    if(checkforExistingDiseaseType(newDiseaseIntoList)) {
        updateDiseaseType(newDiseaseIntoList);
        return true;
    }
    else {
        diseaseTypeList.append(newDiseaseIntoList);
        return true;
    }
}


bool ListContainer::addSupplyType(SupplyType* newSupplyType){
    if(checkforExistingSupplyType(newSupplyType)){
        return updateSupplyType(newSupplyType);

    } else
    {
        this->supplyTypeList.append(newSupplyType);
    }
    return true;
}

/*
  ====================================================================
  This section is for updating/overwriting data already in existence
  These functions should be internal cannot be used by other classes
  ====================================================================
*/

//overwrites aCase's data
bool ListContainer::changeDiseaseCase(DiseaseCase* aCase){
    foreach(DiseaseCase* c, diseaseCaseList){
        if(c->getID()==aCase->getID()){
            c->setDate(aCase->getDate());
            c->setLon(aCase->getLon());
            c->setLat(aCase->getLat());
            c->setQuantity(aCase->getQuantity());
            c->setType(aCase->getType());
            return true;
        }
    }
    return false;
}

bool ListContainer::updateShipment(Shipment* aShipment)
{
    for(int i = 0; i < shipmentList.count();i++)
    {
        if(shipmentList.at(i)->getID() == aShipment->getID())
        {
            shipmentList.at(i)->setQuantity(aShipment->getQuantity());
            shipmentList.at(i)->setType(aShipment->getType());
            shipmentList.at(i)->setSenderLon(aShipment->getSenderLon());
            shipmentList.at(i)->setSenderLat(aShipment->getSenderLat());
            shipmentList.at(i)->setRecieverLon(aShipment->getRecieverLon());
            shipmentList.at(i)->setRecieverLat(aShipment->getRecieverLat());
            shipmentList.at(i)->setExpectedDate(aShipment->getExpectedDate());
            shipmentList.at(i)->setCreatedDate(aShipment->getCreatedDate());
            shipmentList.at(i)->setReceivedDate(aShipment->getReceivedDate());
            shipmentList.at(i)->setSentDate(aShipment->getSentDate());
            shipmentList.at(i)->setCurrentStatus(aShipment->getCurrentStatus());

            return true;
        }
    }

    return false;
}

bool ListContainer::updateDiseaseType(DiseaseType *aDiseaseType)
{
    for(int i = 0; i < diseaseTypeList.count();i++)
    {
        if(diseaseTypeList.at(i)->getTypeID() == aDiseaseType->getTypeID())
        {
           diseaseTypeList.at(i)->overwriteWith(aDiseaseType);
        }
    }
    return false;
}

bool ListContainer::updateSupplyType(SupplyType *aSupplyType)
{
    for(int i = 0; i < supplyTypeList.count();i++)
    {
        if(supplyTypeList.at(i)->getTypeID() == aSupplyType->getTypeID())
        {
           supplyTypeList.at(i)->overwriteWith(aSupplyType);
        }
    }

    return false;
}

/*
  ====================================================================
  Duplication checkers
  ====================================================================
*/

//checks if a supply exists in the supplyTypeList
bool ListContainer::checkForExistingSupply(Supply *aSupply)
{
    /*for(int i = 0;i < supplyList.count();i++)
    {
        if(supplyList.at(i)->getID() == aSupply->getID())
        {
            return true;

        }
    }*/
    foreach( Supply *s, supplyList ) {
        if( s->getID() == aSupply->getID() ) {
            return true;
        }
    }

    return false;
}


bool ListContainer::checkForDiseaseCase(DiseaseCase * diseaseCase)
{
    foreach(DiseaseCase* d,diseaseCaseList)
    {
        if(d->getID() == diseaseCase->getID() )
        {

            return true;
        }
    }

    return false;
}


bool ListContainer::checkforExistingShipment(Shipment *aShipment)
{
    for(int i = 0; i < shipmentList.count();i++)
    {
        if(shipmentList.at(i)->getID() == aShipment->getID())
        {
            return true;
        }
    }
    return false;
}

bool ListContainer::checkforExistingDiseaseType(DiseaseType *aDiseaseType)
{
    for(int i = 0; i < diseaseTypeList.count();i++)
    {
        if(diseaseTypeList.at(i)->getTypeID() == aDiseaseType->getTypeID())
        {
            return true;
        }
    }
    return false;

}


bool ListContainer::checkforExistingSupplyType(SupplyType *aSupplyType)
{
    for(int i = 0; i < supplyTypeList.count();i++)
    {
        if(supplyTypeList.at(i)->getTypeID() == aSupplyType->getTypeID())
        {
            return true;
        }
    }
    return false;
}

/*
  ====================================================================
  Create the get functions to retrieve information from the containers

  ====================================================================
*/
// return the disease names
QStringList ListContainer::getDiseaseListName() {
    QStringList names;

    foreach( DiseaseType *d, diseaseTypeList) {
        names += d->getName();
    }
    return names;
}

// return the supply types
QStringList ListContainer::getSupplyTypeListName() {
    QStringList names;

    foreach( SupplyType *t, supplyTypeList) {
        names += t->getName();
    }

    return names;
}

// TODO:
// Fill out the code for reading the regions
QStringList ListContainer::getRegionNames() {
    QStringList names;
    //QListIterator}
    return names;
}

QStringList ListContainer::getCities() {
    QStringList names;
    QListIterator<City*> i(cityList);

    foreach( City *c, cityList ) {

        names.append(c->getCity());
    }

    names.sort();
    return names;
}

QStringList ListContainer::getProvinces() {
    QStringList names;

    QSet<QString> mySet;

    foreach( City *c, cityList ) {
        mySet.insert(c->getProvince());
    }

    // take the names list and convert the set into a list
    names = names.fromSet(mySet);
    qSort(names);
    return names;
}

QStringList ListContainer::getCitiesByProvince( const QString &name) {
    QStringList provinceList;
    QList<QString> values = listMap.values(name);
    for( int i = 0; i < values.size(); ++i ) {
        provinceList += values.at(i);

    }
    qSort(provinceList);
    return provinceList;
}

QString ListContainer::getCityByName(QString name) {
    QString retName;
    foreach( City *c, cityList ) {
        if( c->getCity() == name ) {
            retName += name;
        }
    }
    return retName;
}

City *ListContainer::getCity(const QString &name) {
    City *tempCity;
    foreach( City *c, cityList ) {
        if( c->getCity() == name ) {
            tempCity = c;
        }
    }
    return tempCity;
}
//finds the city based on location
City* ListContainer::findCity(float lon,float lat)
{
    foreach(City *c, cityList)
    {
        if(c->getLat() == lat && c->getLong() == lon)
        {
            return c;
        }
    }

    qDebug() << "THERE WAS NO CITY AT THAT LOCATION, RETURNING ERROR CITY";
    return new City("ERROR PROVINCE","ERROR CITY",-1,-1);

}

//assignes the city with the var 'name' to the cityPtr
bool ListContainer::getCityByName(QString name,City *cityPtr) {
    foreach( City *c, cityList ) {
        if( c->getCity() == name ) {
            cityPtr = c;
            return true;
        }
    }
    return false;
}

QList<City*>* ListContainer::getCities(QList<City*>* returnPtr)
{
    returnPtr = &this->cityList;
    return returnPtr;
}

float ListContainer::getLatitude(const QString &name) {
    float retVal = 0;
    foreach( City* c, cityList) {
        if( c->getCity() == name ) {
            retVal = c->getLat();
        }
    }
    return retVal;
}

float ListContainer::getLonitude(const QString &name) {
    float retVal = 0;
    foreach( City* c, cityList) {
        if( c->getCity() == name ) {
            retVal = c->getLong();
        }
    }
    return retVal;
}

// return the shipment ids
QList<int> ListContainer::getShipmentID() {
    QList<int> ids;

    foreach( Shipment *s, shipmentList ) {
        ids += s->getID();
    }

    return ids;
}

QList<int> ListContainer::getShipmentQuantity() {
    QList<int> quantities;

    foreach( Shipment *s, shipmentList ) {
        quantities += s->getQuantity();
    }

    return quantities;
}

QList<int> ListContainer::getShipmentType() {
    QList<int> type;

    foreach( Shipment *s, shipmentList ) {
        type += s->getType();
    }

    return type;
}

DiseaseType *ListContainer::getDiseaseTypeByID( int id ) {

    foreach( DiseaseType *d, diseaseTypeList ) {
        if( d->getTypeID() == id ) {

            return d;
        }
    }
    qDebug() << "There no disease with this TypeID";
    return   new DiseaseType(0,"INVALID DISEASE");
}

DiseaseType *ListContainer::getDiseaseTypeByName( const QString &id ) {
    DiseaseType *tempType;
    foreach( DiseaseType *d, diseaseTypeList ) {
        if( d->getName() == id ) {
            tempType = d;
            return tempType;
        }
    }
    qDebug() << "There no disease with this DiseaseTypeName";
    return tempType = new DiseaseType(0,"INVALID DISEASE");
}

int ListContainer::getDiseaseTypeID( const QString &id ) {
    foreach( DiseaseType *d, diseaseTypeList ) {
        if( d->getName() == id ) {
            return d->getTypeID();
        }
    }
    return -1;
}

SupplyType* ListContainer::getSupplyTypeByID(int typeID)
{
    foreach(SupplyType *s, supplyTypeList)
    {
        if(s->getTypeID() == typeID)
        {
            return s;
        }
    }
    qDebug() <<  QString("THERE IS NO SUPPLYTYPE WITH THIS ID: %1  . CREATING DEFAULT SUPPLYTYPE").arg(QString::number(typeID));
    return new SupplyType(-1,"ERROR NO SUPPLY TYPE FOUND");
}
SupplyType* ListContainer::getSupplyTypeByName(QString aSupplyName)
{
    foreach(SupplyType *s, supplyTypeList)
    {
        if(s->getName().toLower() == aSupplyName.toLower())
        {
            //qDebug() << "you have found the SupplyType";
            return s;
        }
    }
    qDebug() <<  QString("THERE IS NO SUPPLYTYPE WITH THIS Name: %1  . CREATING DEFAULT SUPPLYTYPE").arg(aSupplyName);
    return new SupplyType(-1,"ERROR NO SUPPLY TYPE FOUND");
}

Shipment *ListContainer::getShipmentByID(const int &id) {
    Shipment *tempS;
    foreach( Shipment *s, shipmentList ) {
        if( s->getID() == id ) {
            tempS = s;
            return s;
        }
    }
    return tempS = new Shipment();
}

City *ListContainer::getCityByGeo(float lon, float lat) {
    City *name;
    foreach( City *c, cityList ) {
        if( c->getLong() == lon && c->getLat() == lat ) {
            name = c;
            return name;
        }
    }
    return name = new  City();
}

QList<Supply*> ListContainer::getSupplies() {
    QList<Supply*> supply;
    foreach( Supply *c, supplyList ) {
        supply += c;
    }
    return supply;
}

QList<SupplyType*>* ListContainer::getSupplyTypes()
{
    return &this->supplyTypeList;
}

QList<DiseaseType*>* ListContainer::getDiseaseTypes()
{
    return &this->diseaseTypeList;
}

QList<Shipment*> ListContainer::getShipments()
{
    return this->shipmentList;
}

Supply *ListContainer::getSupplyByID(int id) {
    Supply *suppl;
    qDebug() << " ID IS " << id;
    foreach( Supply *s, supplyList ) {
        qDebug() << "looking id" << s->getID();
        if( s->getID() == id ) {
            qDebug() << "Found id:" << s->getID();
            suppl = s;
            return suppl;
        }
    }
}

QString ListContainer::getSupplyNameByID(int id) {
    QString tempString;
    foreach( Supply *s, supplyList ) {
        if( s->getType() == id ) {
          //  tempString = s->g
        }
    }
    return tempString;
}

City *ListContainer::getSupplyByGeo(float lon, float lat) {
    City *c;
    Supply *sup;
    foreach( Supply *s, supplyList ) {
        if( s->getLon() == lon && s->getLat() == lat ) {
            sup = s;
            c = getCityByGeo(sup->getLon(), s->getLat());
            return c;
        }
    }
}

QList<int> ListContainer::getSupplyID() {
    QList<int> ids;

    foreach( Supply *s, supplyList ) {
        ids += s->getID();
    }

    return ids;
}

/*
  ====================================================================
  Search Functions
  ====================================================================
*/

//Finished, do not change!
QList<Supply*>* ListContainer::search(SupplyCriteria criteria)
{
    bool criteriaPassed = false;
    QList<Supply*>* returnList = new QList<Supply*>();

    //min max criteria
    for(int i = 0; i < supplyList.count();i++)
    {
        if(supplyList.at(i)->getQuantity() >= criteria.getMin() && supplyList.at(i)->getQuantity() <= criteria.getMax())
        {
            returnList->append(supplyList.at(i));
        }
    }

    //Test City Criteria by Name

bool hasCityCriteria = false;
    for(int i = 0; i < returnList->count(); i++)
    {
        QString city = this->findCity(returnList->at(i)->getLon(),returnList->at(i)->getLat())->getCity();
        foreach(QString criteriaCityName, criteria.getCityNames())
        {
            if(city == criteriaCityName)
            {
                hasCityCriteria = true;
            }
        }
        if(hasCityCriteria == false && criteria.getCityNames().count() != 0){
            returnList->removeAt(i);
            --i;
        }
        hasCityCriteria = false;
    }

    //Test City Criteria by City Object

    hasCityCriteria = false;
    for(int i = 0; i < returnList->count(); i++)
    {
        QString city = findCity(returnList->at(i)->getLon(),returnList->at(i)->getLat())->getCity();
        //qDebug() << "criteria city object size" << criteria.getCriteriaLocations().count();
        foreach(City* criteriaCity, criteria.getCriteriaLocations())
        {
            QString criteriaCityName = criteriaCity->getCity();


            if(city == criteriaCityName)
            {
                hasCityCriteria = true;
            }
        }
        if(hasCityCriteria == false && criteria.getCriteriaLocations().count() != 0){
            returnList->removeAt(i);
            --i;
        }
        hasCityCriteria = false;
    }



    //test for supply typeID criteria
    criteriaPassed = false;
    for(int i = 0;i < returnList->count();i++)
    {
        int typeID = returnList->at(i)->getType();
        foreach(int criteriaTypeID, criteria.getCriteriaSupplyTypes())
        {

            if(typeID == criteriaTypeID)
            {
                qDebug() << "supply ID match found" << typeID << "and" << criteriaTypeID;
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getCriteriaSupplyTypes().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        //reset criteria
        criteriaPassed = false;

    }
    //Test for Supply Type Name
    criteriaPassed = false;
    for(int i = 0;i < returnList->count();i++)
    {
        int typeID = this->getSupplyTypeByID(returnList->at(i)->getType())->getTypeID();
        foreach(QString typeName, criteria.getCriteriaSupplyTypeNames())
        {
            int criteriaTypeID = this->getSupplyTypeByName(typeName)->getTypeID();
            if(typeID == criteriaTypeID)
            {

                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getCriteriaSupplyTypeNames().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }

        //reset criteria
        criteriaPassed = false;

    }


    return returnList;
}




QList<DiseaseCase*>* ListContainer::search(DiseaseCriteria criteria)
{
    bool criteriaPassed = false;
    QList<DiseaseCase*>* returnList = new QList<DiseaseCase*>();

    //checks quantity, if it is within the boundries, if it is, then add to returnlist
    int min = criteria.getMinQuantity();
    int max = criteria.getMaxQuantity();
    qDebug() << min << "and max" << max;
    foreach(DiseaseCase *d, diseaseCaseList)
    {
        if(d->getQuantity() >= min && d->getQuantity() <= max)

        {
            returnList->insert(0,d);
        }
    }


    //location criteria BY City object

    for(int i = 0; i < returnList->count();i++)
    {
        QString city = this->findCity(returnList->at(i)->getLon(),returnList->at(i)->getLat())->getCity();

        foreach(City *c, criteria.getLocationList())
        {
               QString criteriaCity = c->getCity();
               if(criteriaCity == city)
               {
                   criteriaPassed = true;
               }
        }
        //if the criteria citylist is empty then return everything
        if(criteriaPassed == false && criteria.getLocationList().count() != 0)
        {
          returnList->removeAt(i);
          --i;
        }
        criteriaPassed = false;
    }



    //test disease type criteria
    criteriaPassed = false;
    for(int i = 0; i < returnList->count();i++)
    {
        int id = returnList->at(i)->getType();

        foreach( int j, criteria.getDiseaseTypeList() )
        {
            int criteriaID = j;

            if(id == criteriaID)
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getDiseaseTypeList().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }

    //Test DiseaseType by Name
    criteriaPassed = false;
    for(int i = 0; i < returnList->count();i++)
    {
        QString diseaseTypeName = this->getDiseaseTypeByID(returnList->at(i)->getType())->getName();

        foreach( QString criteriaTypeID, criteria.getDiseaseTypeNames())
        {
            if(diseaseTypeName.toLower() == criteriaTypeID.toLower())
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getDiseaseTypeNames().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }

    //Test date range
    QDate startDate = criteria.getStartDate();
    QDate endDate   = criteria.getEndDate();
    criteriaPassed = false;
    for(int i = 0; i < returnList->count();i++)
    {
        QDate date = returnList->at(i)->getDate();

        if(date <= endDate && date >= startDate )
        {
            criteriaPassed = true;
        }

        if(criteriaPassed == false)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }

    //Search City By names
    for(int i = 0; i < returnList->count();i++)
    {//find the city name  by their longitude and latitude
        QString cityName = findCity(returnList->at(i)->getLon(),returnList->at(i)->getLat())->getCity();

        foreach(QString criteriaCityName, criteria.getCityNames())
        {
               if(criteriaCityName == cityName)
               {
                   criteriaPassed = true;
               }
        }
        //if the criteria citylist is empty then return everything
        if(criteriaPassed == false && criteria.getCityNames().count() != 0)
        {
          returnList->removeAt(i);
          --i;
        }
        criteriaPassed = false;
    }

   return returnList;

}





//Stub: Returns all values in local database of this type
QList<Shipment*>* ListContainer::search(ShipmentCriteria criteria)
{
    QList<Shipment*>* returnList = new QList<Shipment*>();
    bool criteriaPassed = false;

    //test senders by City objects
    for(int i = 0; i < shipmentList.count();i++)
    {
        QString sendingCity = this->findCity(shipmentList.at(i)->getSenderLon(),shipmentList.at(i)->getSenderLat())->getCity();

        foreach(City*c, criteria.getSenderList())
        {
            QString criteriaSendingCity = c->getCity();

            if(sendingCity.toLower() == criteriaSendingCity.toLower())
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == true || criteria.getSenderList().count() == 0)
        {
            returnList->insert(0,shipmentList.at(i));

        }
        criteriaPassed = false;
    }

    //test senders by City Name
    for(int i = 0; i < returnList->count(); i++)
    {
        QString sendingCity = this->findCity(returnList->at(i)->getSenderLon(),returnList->at(i)->getSenderLat())->getCity();
        foreach(QString c, criteria.getSenderCityNames())
        {
            if(sendingCity.toLower() == c.toLower())
            {

                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getSenderCityNames().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }


    //test destinations by City Object
    for(int i = 0; i < returnList->count(); i++)
    {
        QString sendingCity = this->findCity(returnList->at(i)->getRecieverLon(),returnList->at(i)->getRecieverLat())->getCity();
        foreach(City* c, criteria.getDestinationList())
        {
            if(sendingCity.toLower() == c->getCity().toLower())
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getDestinationList().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }
    //test destinations by City Name
    for(int i = 0; i < returnList->count(); i++)
    {
        QString sendingCity = this->findCity(returnList->at(i)->getRecieverLon(),returnList->at(i)->getRecieverLat())->getCity();
        foreach(QString c, criteria.getDestinationCityNames())
        {
            if(sendingCity.toLower() == c.toLower())
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getDestinationCityNames().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }
    //test disease typeID
    for(int i = 0; i < returnList->count(); i++)
    {
        int typeID = returnList->at(i)->getType();
        foreach(int c, criteria.getTypeList())
        {
            if(typeID == c)
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getTypeList().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }

    //test disease type name
   for(int i = 0; i < returnList->count(); i++)
    {
        QString typeName = this->getSupplyTypeByID(returnList->at(i)->getType())->getName();
        foreach(QString c, criteria.getTypeNames())//need to add shipment criteria function for getting type string
        {

            if(typeName.toLower() == c.toLower())
            {
                criteriaPassed = true;
            }
        }
        if(criteriaPassed == false && criteria.getTypeNames().count() != 0)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }



    int minQuantity = criteria.getMinQuantity();
    int maxQuantity = criteria.getMaxQuantity();
    for(int i = 0; i < returnList->count();i++)
    {
        int currentQuantity = returnList->at(i)->getQuantity();
        if(currentQuantity >= minQuantity && currentQuantity >= maxQuantity)
        {
            returnList->removeAt(i);
            --i;
        }
    }

    //test date range
    QDate startDate = criteria.getStartDate();
    QDate endDate = criteria.getEndDate();
    criteriaPassed = false;
    for(int i = 0; i < returnList->count();i++)
    {
        QDate shipmentSentDate = returnList->at(i)->getSentDate();
        QDate shipmentExpectedDate = returnList->at(i)->getExpectedDate();
        QDate shipmentCreatedDate = returnList->at(i)->getCreatedDate();
        //if any of the returnList shipment dates fall between the start and end date then the criteria passes.
        if(shipmentSentDate     >= startDate && shipmentSentDate     <= endDate){criteriaPassed = true;}
        if(shipmentExpectedDate >= startDate && shipmentExpectedDate <= endDate){criteriaPassed = true;}
        if(shipmentCreatedDate  >= startDate && shipmentCreatedDate  <= endDate){criteriaPassed = true;}

        if(criteriaPassed == false)
        {
            returnList->removeAt(i);
            --i;
        }
        criteriaPassed = false;
    }

    //test shipment status
     for(int i = 0; i < returnList->count();i++)
    {
         Shipment::SHIPMENT_STATUS status = returnList->at(i)->getCurrentStatus();
         for(int j = 0;j < criteria.getStatus().count();j++)
         {
             Shipment::SHIPMENT_STATUS criteriaStatus = criteria.getStatus().at(j);
             if(status == criteriaStatus){criteriaPassed = true;}
         }
         if(criteriaPassed == false && criteria.getStatus().count() != 0)
         {
             returnList->removeAt(i);
             --i;
         }
         criteriaPassed = false;

    }/**/
    return returnList;

}




/*
  ====================================================================
  Functions to read from file
  ====================================================================
*/

bool ListContainer::sortHelper( const QString &s1, const QString &s2 ) {
    return (s1.toLower() < s2.toLower());
}

void ListContainer::readCities(const QString &fileName) {
    QFile file(fileName);
    QStringList tempList;
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::warning(this, QObject::tr("Application"),
                             QObject::tr( "Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
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
            aCity = new City(prov, cit, lat, lon);
            cityList.append(aCity);
         //   qDebug() << "This city is:" << aCity->getProvince() << aCity->getCity() << aCity->getLat() << aCity->getLong();
            listMap.insertMulti(aCity->getProvince(), aCity->getCity());
            cities.clear();
            tempList.clear();
    }

    //qSort( cities.begin(), cities.end(), sortHelper );
}

void ListContainer::readDiseaseType(const QString &fileName) {
    QFile file(fileName);
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::warning(this, QObject::tr("Application"),
                             QObject::tr( "Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    while( !in.atEnd() ) {
        diseaseTypes += in.readLine(2000);
      //  qDebug() << "Add Disease types: " << diseaseTypes;
    }
    diseaseTypes.sort();
}

void ListContainer::readSupplyType(const QString &fileName) {
    QFile file(fileName);
    if( !file.open( QFile::ReadOnly | QFile::Text ) ) {
        QMessageBox::warning(this, QObject::tr("Application"),
                             QObject::tr( "Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    while( !in.atEnd() ) {
        supplyTypes += in.readLine(2000);
      //  qDebug() << "Add Supply types: " << supplyTypes;
    }
    supplyTypes.sort();
}

int ListContainer::getRevNum() {
    return revNum;
}


void ListContainer::setRevNum(int number) {
    revNum = number;
}
