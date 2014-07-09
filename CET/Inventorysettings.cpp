#include "Inventorysettings.h"
#include "ui_Inventorysettings.h"

Inventorysettings::Inventorysettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inventorysettings)
{
    ui->setupUi(this);
}

Inventorysettings::Inventorysettings(Supply *supply, Model *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inventorysettings),
    supply(supply),
    model(model)
{
    ui->setupUi(this);

    // get the supply Quantity
    QString sQuantity = QString::number(supply->getQuantity());
    City *c = model->getContainer()->getSupplyByGeo(supply->getLon(), supply->getLat());

    QString supplyID = QString::number(supply->getID());

    ////ui->supplyLocation->setText(model;
    ui->supplyLine->setText(supplyID);
    ui->quantityLine->setText(sQuantity);
    ui->locationLine->setText(c->getCity());
}

Inventorysettings::~Inventorysettings()
{
    delete ui;
}

void Inventorysettings::updateInventory(QString text) {
    QString value = text;
    int val = value.toInt();
    Supply *newSupply = new Supply(supply->getID(), supply->getType(), val, supply->getLon(),
                                   supply->getLat(), supply->getDate() );
    model->getContainer()->addToSupply(newSupply);
}
