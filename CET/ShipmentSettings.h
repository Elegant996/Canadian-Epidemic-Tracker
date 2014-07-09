#ifndef SHIPMENTSETTINGS_H
#define SHIPMENTSETTINGS_H

#include <QDialog>
#include <QDate>
#include "../Common/include/City.h"
#include "../Common/include/SupplyType.h"
#include "../Common/include/Supply.h"
#include "../Common/include/Shipment.h"
#include "include/Model.h"

namespace Ui {
    class ShipmentSettings;
}

class ShipmentSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ShipmentSettings(QWidget *parent = 0);
    ShipmentSettings(int id, int supplyType, int amount, QDate fromDate, QDate toDate,
                     QString fromRegion, QString toRegion, QWidget *parent = 0);
    ShipmentSettings(Shipment *shipment, Supply *supply, Model *model, QWidget *parent = 0);

    ~ShipmentSettings();

    // get information
    QDate getPreparedDate() { return preparedDate; }
    QDate getSentDate() { return sentDate; }
    QDate getExpectedDate() { return expectedDate; }
    QDate getReceivedDate() { return receivedDate; }
    int getAmountToShip() { return amountToShip; }
    QString getFromRegion() { return fromRegion; }
    QString getToRegion() { return toRegion; }
    int getSupplyType() { return supplyType; }
    int getShipmentID() { return id; }
    float getSenderLon() { return senderLon; }
    float getSenderLat() { return senderLat; }
    float getReceiverLon() { return receiverLon; }
    float getReceiverLat() { return receiverLat; }

    // set information
    void setSentDate(QDate date) { this->sentDate = date;}
    void setExpectedDate( QDate date) { this->expectedDate = date; }
    void setAmountToShip( int amount ) { this->amountToShip = amount; }
    void setFromRegion( QString city ) { this->fromRegion = city; }
    void setToRegion( QString city ) { this->toRegion = city; }
    void setSupplyType( int supply ) { this->supplyType = supply; }
    void setSenderLon( float lon ) { this->senderLon = lon; }
    void setSenderLat( float lat ) { this->senderLat = lat ; }
    void setReceiverLon( float lon ) { this->receiverLon = lon; }
    void setReceiverLat( float lat ) { this->receiverLat = lat; }

private slots:
    void updateShipment( QString text );

private:
    Ui::ShipmentSettings *ui;
    QString fromRegion;
    QString toRegion;
    int amountToShip;
    QDate preparedDate;
    QDate sentDate;
    QDate expectedDate;
    QDate receivedDate;
    int supplyType;
    int id;

    float senderLon, senderLat;
    float receiverLon, receiverLat;

    QString oldState;

    Shipment *ship;
    Supply *supply;

    void setUIFields();
    Model *model;
};

#endif // SHIPMENTSETTINGS_H

