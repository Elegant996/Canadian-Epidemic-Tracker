#ifndef INVENTORYSETTINGS_H
#define INVENTORYSETTINGS_H

#include <QDialog>
#include "include/Model.h"
#include "../Common/include/Supply.h"
#include "../Common/include/City.h"

namespace Ui {
    class Inventorysettings;
}

class Inventorysettings : public QDialog
{
    Q_OBJECT

public:
    explicit Inventorysettings(QWidget *parent = 0);
    Inventorysettings(Supply *supply, Model *model, QWidget *parent);
    ~Inventorysettings();

private slots:
    void updateInventory(QString text);


private:
    Ui::Inventorysettings *ui;
    QString inventoryName;
    QString location;
    int quantity;

    Supply *supply;
    Model *model;
};

#endif // INVENTORYSETTINGS_H
