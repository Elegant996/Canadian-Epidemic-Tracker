#include "ShipmentSettings.h"
#include "ui_ShipmentSettings.h"
#include <QDebug>

ShipmentSettings::ShipmentSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShipmentSettings)
{
    ui->setupUi(this);
}

ShipmentSettings::ShipmentSettings( int id, int supplyType, int amount, QDate fromDate, QDate toDate, QString fromRegion, QString toRegion, QWidget *parent) :
    QDialog(parent),
    ui( new Ui::ShipmentSettings ),
    id(id),
    supplyType(supplyType),
    amountToShip(amount),
    sentDate(fromDate),
    expectedDate(toDate),
    fromRegion(fromRegion),
    toRegion(toRegion)
{
    ui->setupUi(this);

    // set the id
    QString sID = QString::number(id);
    ui->shipmentIDEdit->setText(sID);

    // store the supply in the field
    QString quantity = QString::number(supplyType);
    ui->supplyTypeEdit->setText(quantity);

    // store the amount in the field
    QString str = QString::number(amountToShip);// = amountToShip;
    ui->shippedAmountEdit->insert(str);

    // store the date in the field
    ui->datePrepared->setDate(fromDate);
    ui->dateShipped->setDate(toDate);
    ui->fromRegionEdit->setText(fromRegion);
    ui->toRegionEdit->setText(toRegion);
}

ShipmentSettings::ShipmentSettings(Shipment *shipment, Supply *supply, Model *model, QWidget *parent) :
        QDialog(parent),
        ui( new Ui::ShipmentSettings ),
        ship(shipment),
        supply(supply),
        model(model)
{
    QStringList state;
    state.append("PREPARED");
    state.append("SENT");
    state.append("RECEIVED");
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    QString id = QString::number(ship->getID());

    QString type = QString::number(ship->getType());

    QString amount = QString::number(ship->getQuantity());


    // set the dates
    receivedDate = ship->getReceivedDate();
    preparedDate = ship->getCreatedDate();
    expectedDate = ship->getExpectedDate();
    sentDate = ship->getSentDate();



    // set the status
    Shipment::SHIPMENT_STATUS status = ship->getCurrentStatus();

    // from region
    qDebug() << ship->getSenderLon();
    qDebug() << ship->getSenderLat();

    setSenderLon(ship->getSenderLon());
    setSenderLat(ship->getSenderLat());
    setReceiverLon(ship->getRecieverLon());
    setReceiverLat(ship->getRecieverLat());
    City *c = model->getContainer()->getCityByGeo(ship->getSenderLon(), ship->getSenderLat());
    QString cityName = c->getCity();
    qDebug() << "cname" << cityName;

    // to region
    City *cc = model->getContainer()->getCityByGeo(ship->getRecieverLon(), ship->getRecieverLat());
    QString cityNameReceived = cc->getCity();

    ui->shipmentIDEdit->setText(id);
    ui->supplyTypeEdit->setText(type);
    ui->shippedAmountEdit->setText(amount);

    ui->datePrepared->setDate(preparedDate);
    ui->dateShipped->setDate(sentDate);
    ui->dateExpected->setDate(expectedDate);
    ui->dateReceived->setDate(receivedDate);

    ui->fromRegionEdit->setText(cityName);
    ui->toRegionEdit->setText(cityNameReceived);

    ui->statusComboBox->addItems(state);

    if( ship->getCurrentStatus() == Shipment::PREPARED ) {
        ui->statusComboBox->setCurrentIndex(0);
        oldState += "PREPARED";
        qDebug() << "ostate" << oldState;
    }
    else if( ship->getCurrentStatus() == Shipment::SENT ) {
        ui->statusComboBox->setCurrentIndex(1);
        oldState += "SENT";
        qDebug() << oldState;
    }
    else if( ship->getCurrentStatus() == Shipment::RECEIVED ) {
        ui->statusComboBox->setCurrentIndex(2);
        oldState += "RECEIVED";
        qDebug() << oldState;
    }

    //ui->fromRegionEdit->setText(fromRegion);
   // ui->toRegionEdit->setText(toRegion);
}

ShipmentSettings::~ShipmentSettings()
{
    delete ui;
}

// set the UI fields
void ShipmentSettings::setUIFields() {
    // shipped amount edit
    QString str(amountToShip);// = amountToShip;
    ui->shippedAmountEdit->setText(str);
}

void ShipmentSettings::updateShipment(QString text) {
    // update the shipment
    // edate = date + 5 days





    QString newstate = text;
    qDebug() << "oldstate" << oldState << "newstate" << newstate;
    if( newstate == "RECEIVED" && oldState == "PREPARED"   ) {
        qDebug() << "Not allowed";
    }
    else if ( oldState == "PREPARED" && newstate == "SENT" ) {

        QDate sentDate(QDate::currentDate());
        QDate eDate(QDate::currentDate());
        eDate = eDate.addDays(5);
        qDebug() << "lon/lat" << ship->getSenderLon() << ship->getSenderLat();
        Shipment *newShipment = new Shipment(ship->getID(), ship->getType(), Shipment::SENT,
                                         ship->getQuantity(),
                                         ship->getSenderLon(),ship->getSenderLat(),
                                         ship->getRecieverLon(), ship->getRecieverLat(), getPreparedDate(),
                                         sentDate, eDate, ship->getReceivedDate());
        float xQ = supply->getQuantity() - ship->getQuantity();
        if( xQ == 0 ) {
            xQ = 0;
        }
        Supply *newSupply = new Supply(supply->getID(), supply->getType(), xQ,
                                       ship->getSenderLon(), ship->getSenderLat()); // update the supply
        model->getContainer()->addShipment(newShipment);

        model->getContainer()->addToSupply(newSupply);
    }
    else if ( oldState == "SENT" && newstate == "RECEIVED" ) {

        QDate sentDate(QDate::currentDate());
        QDate eDate(QDate::currentDate());
        QDate recDate(QDate::currentDate());
        qDebug() << ship->getCurrentStatus();
        Shipment *newShipment = new Shipment(ship->getID(), ship->getType(), Shipment::RECEIVED,
                                         ship->getQuantity(),
                                         ship->getSenderLon(),ship->getSenderLat(),
                                         ship->getRecieverLon(), ship->getRecieverLat(), getPreparedDate(),
                                         sentDate, eDate, recDate);
        float xQ = supply->getQuantity() + ship->getQuantity();

        Supply *newSupply = new Supply(supply->getID(), supply->getType(), xQ,
                                       ship->getSenderLon(), ship->getSenderLat()); // update the supply

        model->getContainer()->addShipment(newShipment);
        model->getContainer()->addToSupply(newSupply);

    }
    else if( newstate == "PREPARED" && oldState == "SENT" ) {
        qDebug() << "Not allowed";
    }
    else if( ( newstate == "PREPARED" || newstate == "SENT" ) && oldState == "RECEIVED "  ) {
        qDebug() << "Not allowed";
    }




}
