#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QStringListModel>
#include <marble/AbstractFloatItem.h>
#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <marble/MarbleDirs.h>
#include <QListWidget>
#include <QComboBox>
#include <QTimer>

#include "include/ListContainer.h"
#include "include/Model.h"
#include "include/UIDrawHelper.h"
#include "../Common/include/Shipment.h"
#include "ShipmentSettings.h"
#include "Inventorysettings.h"

//included for testing comment this out when you
//remove testing stuff below
#include "../Common/include/Handler.h"
#include <QtXml/QXmlSimpleReader>

using namespace Marble;

namespace Ui {
    class MainWindow;
    class ShipmentSettings;
    class Inventorysettings;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Model *client = 0);
    ~MainWindow();

private slots:
    // go to longitude/latitude of selection
    void goToPosition(const QString &name); // go to province in the map
    void getCitiesFromProvince( const QString &name );
    void getCitiesFromProvinceListView( const QString &name ); // for the locationlistwidget
    void getCitiesFromProvinceListView_2( const QString &name ); // for the diseaselistwidget
    void getCitiesFromProvinceMapView( const QString &name );
    void getCitiesFromSupplyTab( const QString &name ); // get the cities from supplytab
    void getCitiesForShipment( const QString &name ); // get cities from shipment tab
    void LoadShipmentSettings( QModelIndex index );
    void LoadInventorySettings( QModelIndex index );

    // make all the needed functions for the connections tab only
    void getMaxItems( const QString &text );
    void getMinItems( const QString &text );

    void getMaxSupplyItems(const QString &text );
    void getMinSupplyItems(const QString &text );

    void getFromDateEdit( QDate date );
    void getToDateEdit( QDate date );

    // retrieve and send information from the casemanagement bug
    void sendNewDisease();
    void sendNewShipment();
    void sendNewSupply();



    // create a new shipment setting window
    void checkShipmentSettings();
    void checkInventorySettings();


    void setMapZoom( int );

    void updateLayerInterfaceCases();
    void updateLayerInterfaceSupply();

    void debug();
    void updateUIDrawHelperCases();
    void updateUIDrawHelperSupply();
    void connectToServer();
    void disconnectFromServer();

    void CreateAndUpdateTable();
    void CreateAndUpdateSupplyTable();

    void setMoon();




signals:
    void setCustomZoom(int);
    void setCaseTableView();


private:
    Ui::MainWindow *ui;


    void setDates(); // set the dates in the boxes
    void setCanadaHome(); // set the marblewidget's home to canada
    void setBoxesInUI(); // fill the widgets with information
    void setUIRelatedConnections(); // setup the connect information for pushbuttons and actions
    void setupModels(); // setup the models for filling in the listwidgets and tables
    void setupDrawHelper(); // setup the drawhelper to draw on the map
    void setDataPath(); // set the data path of marble
    void setFloatItems(); // set the float items in the marblewidget

    // draw some test functions
    void customPaint(GeoPainter *painter);
    void setLayerInterface( UIDrawHelper *drawHelper );

    void refreshContainer();

    /// get the selections for the table from Case Management Tab
    void SearchCaseManagementObjects();
    QList<QString> returnDiseaseListView(); // diseaselistview field
    QList<QString> diseaseSearchObjects;
    QList<QString> returnLocationListView(); // locationlistview field
    QList<QString> locationSearchObjects;
    QDate returnLocationListDate(); // TO DATE
    QDate returnDiseaseListDate(); //  FROM DATE

    // update the Map when a region/city is selected
    void UpdateUiOnSelectCases();
    void UpdateUiOnSelectSupply();
    Model *model;
    QStringListModel *knownCaseModel;
    QStringListModel *knownLocationModel;
    QStringListModel *customCityListModel;
    QStringListModel *customCityListModel_2;
    QStringListModel *customCityListModelMap;
    QStringListModel *customCityListSupplyModel;

    QStringListModel *shipmentModel;

    QStandardItemModel   *tableViewModel;

    QStringListModel *supplyListModel;

    // variables to hold the values for MinItems and MaxItems in the Case Management tab
    int minCases, maxCases;
    int maxSupplyItems, minSupplyItems;
    // hold the date for the case management tab
    QDate toDateCase, fromDateCase;


    UIDrawHelper *drawHelper;
    int zoomLevel;

    //Testing Related Stuff
    void LeighsTestStuff();
    void populateContainer();
    void testDiseaseCaseCriteria();
    void testSupplyCriteria();
    void testShipmentCriteria();
    void testXML();
    int getRandNum(int min,int max);



};

#endif // MAINWINDOW_H
