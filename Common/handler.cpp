#include "../Common/include/Handler.h"
#include <QDebug>




Handler::Handler(){
    update = new UpdateReply();
    theStack = QStack<QString>();
    clean();
}

Handler::~Handler(){
//delete update;
}

Reply* Handler::getReply(){
    return this->theReply;
}

UpdateReply* Handler::getUpdate()
{
    return update;
}

bool Handler::startDocument(){
    qDebug()<<"starting Document";
    return true;
}

bool Handler::startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs){

    theStack.push(name);
 //qDebug()<<"Pushing:" << theStack.top();
     if (name == "Logout"){
        theReply = new LogoutMsg(attrs.value(0).remove("sid").toInt());
    }
    else if (name == "LogoutReply"){
        theReply = new LogoutReply(attrs.value(0).toInt());
    }
    else if (name == "ReadUpdate"){
        string1 = attrs.value(0);
        string2 = attrs.value(1);
        theReply = new ReadUpdate(string1,string2);
    }
    else if (name == "ReadUpdateReply"){
        theReply = new ReadUpdateReply(attrs.value(1),attrs.value(2),attrs.value(0).toInt());
    }
    else if (name == "LoginReply"){
        string1 = attrs.value(0);
        string2 = attrs.value(1);
    }
    else if (name == "WriteUpdate"){
        string1 = attrs.value(0);
        string2 = attrs.value(1);
        theReply = new WriteUpdate(string1,string2);
    }
    else if (name == "SupplyType"){
           string1 = attrs.value(0);
    }
    else if (name == "DiseaseType"){
        string1 = attrs.value(0);
    }
    else if (name == "DiseaseEntry"){
        string1=attrs.value(0);
    }
    else if (name == "SupplyEntry"){
        string1 = attrs.value(0);
    }
   else if (name =="Shipment"){
        string1= attrs.value(0);
    }
    else if(name == "ShipmentDestination"){
        isShipmentDest = true;
    }
    else if(name =="ExpectedDate"){
        expectedDate = true;
     }
    else if(name =="Created"){
        createdDate = true;
     }
    else if(name =="Sent"){
        sentDate = true;
    }
    else if (name == "Received"){
        received = true;
    }
    else if (name =="WriteUpdateReply"){
        theReply= new WriteUpdateReply(attrs.value(0).toInt());
    }
    else if (name == "NewRevision"){
        theReply = new NewRevisionMsg(attrs.value(0));
    }
    else if (name == "MessageError"){
        theReply = new MessageError(attrs.value(0).toInt());
    }

    return true;
}

bool Handler::characters(const QString &ch){
    //qDebug()<<ch;

    if(theStack.top()=="userName"){
        string1 = ch;
    }
    else if(theStack.top()=="password"){
        string2 = ch;
    }
    else if(theStack.top()=="supplyName"){
        string2 = ch;
    }
    else if(theStack.top()=="diseaseName"){
        string2 = ch;
    }

    else if (theStack.top()=="DiseaseTypeID"){
        string2 = ch;
    }

    else if (theStack.top()=="longitude"){
        if (!isShipmentDest){
            lng=ch.toFloat();
        }
        else{
            lngDest = ch.toFloat();
        }
    }
    else if (theStack.top()=="latitude"){
        if(!isShipmentDest){
            lat=ch.toFloat();
        }
        else{
            latDest = ch.toFloat();
        }
    }
    else if (theStack.top()=="Date"){

        if (expectedDate){
            expected = QDate::fromString(ch, Qt::ISODate);
            expectedDate = false;
        }
        if(received){
            theDate= QDate::fromString(ch, Qt::ISODate);
        }
        if (sentDate){
            sent= QDate::fromString(ch, Qt::ISODate);
        }
        if (createdDate){
            created= QDate::fromString(ch, Qt::ISODate);
        }
    }
    else if (theStack.top()=="incidents"){
        x = ch.toInt();
    }
    else if (theStack.top()=="SupplyTypeID"){
        string2 = ch;
    }
    else if (theStack.top()=="quantity"){
        x = ch.toInt();
    }
    else if (theStack.top()=="authLevel"){
        x = ch.toInt();
    }
    return true;
}

bool Handler::endElement(const QString &, const QString &localName, const QString &){
   // qDebug()<<"localName"<<localName;

    if(theStack.top()!=localName){
        qDebug()<<localName<<" not closed properly";
        return false;
    }
    //qDebug()<<"Popping:" << theStack.top();
    theStack.pop();

    if(localName == "Login"){
            theReply = new LoginMsg(string1,string2);
    }
    else if (localName == "LoginReply"){
        theReply = new LoginReply(string1.toInt(),string2.remove("sid").toInt(),x);
    }
    else if (localName=="SupplyType"){    
            int x = string1.remove("st").toInt();
            update->addSType(new SupplyType(x,string2));         
 }

    else if (localName=="DiseaseType"){
        int x = string1.remove("dt").toInt();
        update->addDType(new DiseaseType(x,string2));
    }
    else if (localName=="DiseaseEntry"){
        int dID;
        if (string1 == "new"){
            dID = NULL;
        }
        else{
            dID = string1.remove("de").toInt();
        }
        update->addDCase(new DiseaseCase(dID,string2.remove("dt").toInt(),x,lng,lat,theDate));
    }
    else if (localName =="SupplyEntry"){
        int sID;
        if (string1 == "new"){
            sID = NULL;
        }
        else{
            sID = string1.remove("se").toInt();
        }
        update->addSupplyUpdate(new Supply(sID,string2.remove("st").toInt(),x,lng,lat,theDate));
    }
    else if (localName =="ShipmentDestination"){
            isShipmentDest = false;
    }
    else if (localName == "ExpectedDate"){
            expectedDate = false;
    }
    else if (localName == "Created"){
            createdDate = false;
    }
    else if (localName == "Sent"){ 
            sentDate = false;      
    }
    else if (localName == "Shipment"){
         Shipment::SHIPMENT_STATUS Status;

         if(received){
             Status = Shipment::RECEIVED;
         }
         if (sentDate){
             Status = Shipment::SENT;
         }
         if (createdDate){
             Status = Shipment::PREPARED;
         }
       // qDebug()<<"adding teh shipment";
        int shipID;
        if (string1 == "new"){
            shipID = NULL;
        }
        else{
            shipID = string1.remove("sh").toInt();
        }

        update->addShipment(new Shipment(shipID , string2.remove("st").toInt(), Status, x, lng, lat, lngDest, latDest, created,sent,  expected, theDate));
        //qDebug()<<update->getShipments().last()->toXML();
    }
    else if (localName == "CETUpdate"){
        clean();
    }

    return true;
}

bool Handler::error(const QXmlParseException &exception){
    qDebug()<<"error:"<<exception.message();
return false;
}

bool Handler::fatalError(const QXmlParseException &exception){
    qDebug()<<"encountered an error" <<exception.message();
    return true;
}

bool Handler::endDocument(){
    qDebug()<<"end of document";
    return true;
}

void Handler::clean(){
    string1="";
    string2="";
    errormsg="";
    lat=0;
    lng=0;
    latDest=0;
    lngDest=0;
    theDate = QDate();
    created = QDate();
    sent = QDate();
    expected = QDate();
    x = 0;
    isShipmentDest=false;
    expectedDate=false;
    createdDate=false;
    sentDate=false;
    received=false;
}
