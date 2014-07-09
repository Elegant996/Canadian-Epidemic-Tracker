#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>
#include <QTimer>
#include <marble/GeoDataPlacemark.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent, Model *client) :
    QMainWindow(parent), model(client),
    ui(new Ui::MainWindow)
{
        /// DO NOT MODIFY THIS CODE
        /// IF YOU CHANGE THE NEXT 5 LINES YOU DIE!!!!11!!1!
        QDir directory( qApp->applicationDirPath());
        directory.cd("maps");
        directory.cd("data");
        Marble::MarbleDirs::setMarbleDataPath(directory.absolutePath());
        qDebug() << Marble::MarbleDirs::marbleDataPath();

        zoomLevel = 1500;

        // create the models to populate the lists into the listviews and stuff
        knownCaseModel = new QStringListModel();
        knownLocationModel = new QStringListModel();
        supplyListModel = new QStringListModel();
        customCityListModel = new QStringListModel();
        customCityListModel_2 = new QStringListModel();
        customCityListModelMap = new QStringListModel();
        customCityListSupplyModel = new QStringListModel();
        shipmentModel = new QStringListModel();
        tableViewModel = new QStandardItemModel();
        tableViewModel->insertColumns(tableViewModel->columnCount(), 4 );
        tableViewModel->insertRows(0, 0);
        tableViewModel->setHeaderData(0, Qt::Horizontal, tr( "Location"));
        tableViewModel->setHeaderData(1, Qt::Horizontal, tr("Disease name"));
        tableViewModel->setHeaderData(2, Qt::Horizontal, tr("Quantity"));
        tableViewModel->setHeaderData(3, Qt::Horizontal, tr("Date"));



        //location
        //disease name
        //quantity
        //date

        //ui->setSizePolicy(sizePol);
        ui->setupUi(this);
        ui->MarbleWidget->zoomView(3000);

        // set the lineedit for NumberOfCases to digits only
        ui->NumberOfCasesEdit->setValidator(new QIntValidator(this));
        ui->lineEdit->setValidator(new QIntValidator(this));

        // loop through each floatable item in the MarbleWidget and deactivate the overview map
        foreach ( AbstractFloatItem * floatItem, ui->MarbleWidget->floatItems() )
            if ( floatItem && floatItem->nameId() == "overviewmap" ) {
                // set the map to invisible
                floatItem->setVisible(false);
            }

        drawHelper = new UIDrawHelper(ui->MarbleWidget);
        ui->MarbleWidget->map()->model()->addLayer(drawHelper);
        ui->MarbleWidget->installEventFilter(drawHelper);

        setBoxesInUI();
        setDates();
        setCanadaHome();
        UpdateUiOnSelectCases();
        UpdateUiOnSelectSupply();
        setUIRelatedConnections();
        checkShipmentSettings();
        checkInventorySettings();

       // updateLayerInterfaceCases();
       // LeighsTestStuff();

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sendNewDisease() {
    // get information from cityBox
    qDebug() << "Pressed sendNewDisease()";
    QString getCityComboBoxInformation = ui->cityBox->currentText();
    qDebug() << getCityComboBoxInformation;
    // get information from NumberOfCasesEdit
    QString getNumberOfCasesEdit = ui->NumberOfCasesEdit->text();
    float caseNumber = getNumberOfCasesEdit.toFloat();
    qDebug() << caseNumber;
    // get information from DiseaseComboBox
    QString getDiseaseComboBoxInformation = ui->DiseaseComboBox->currentText();
    qDebug() << getDiseaseComboBoxInformation;
    // get information from dateEdit
    QDate dateEditInformation = ui->dateEdit->date();
    qDebug() << dateEditInformation.currentDate();
    // get information from pushButton


}

void MainWindow::sendNewShipment() {
    // get information from shipmentsupplytypewidget
    QList<QListWidgetItem *> currentTextInWidget = ui->shipmentSupplyTypeWidget->selectedItems();
    QString bla = currentTextInWidget.at(0)->text();
    qDebug() << bla;
    // get information from shipmentcomboboxcity_2
    QString getShipmentComboBoxCity_2 = ui->shipmentComboBoxCity_2->currentText();
    qDebug() << getShipmentComboBoxCity_2;
    // get information from shipmentcomboboxregionbox_2
    QString getShipmentComboBoxRegionBox_2 = ui->shipmentComboBoxRegion_2->currentText();
    qDebug() << getShipmentComboBoxRegionBox_2;

    // get information from lineedit in shipment
    QString amountToShipLineEdit = ui->lineEdit->text();
    qDebug() << amountToShipLineEdit;
    // get information from dateedit2
    QDate getDateEdit_2 = ui->dateEdit_2->date();
    qDebug() << getDateEdit_2;
    // activate the submit button
    //connect( ui->submitShipmentButton, SIGNAL(pressed()), SLOT(LoadShipmentSettings(QModelIndex)));
    //LoadShipmentSettings(index);
}

void MainWindow::sendNewSupply() {

}

void MainWindow::setDates() {
    // set the dates to the current date for each date
    ui->dateEdit->setDate(QDate::currentDate());
    ui->fromDateEdit->setDate(QDate::currentDate());
    ui->ToDateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

void MainWindow::setCanadaHome() {
    GeoDataCoordinates home(-75.4124, 45.2515, 1500, GeoDataCoordinates::Degree);
    ui->MarbleWidget->setHome(home, 2000);
    ui->MarbleWidget->goHome();
}

void MainWindow::setMoon() {
    ui->MarbleWidget->setMapThemeId("moon/clementine/clementine.dgml");
}

void MainWindow::setBoxesInUI() {

    QStringList statusList;

    statusList.insert(statusList.size(), "PREPARED");
    statusList.insert(statusList.size(), "SENT");
    statusList.insert(statusList.size(), "RECEIVED");

    /// add items into the combo boxes
    ui->DiseaseComboBox->addItems(model->getContainer()->getDiseaseListName());
    ui->regionComboBox->addItems(model->getContainer()->getCities());
    ui->provinceComboBox_2->addItems(model->getContainer()->getProvinces());
    ui->SupplyComboBox->addItems(model->getContainer()->getSupplyTypeListName());
    ui->provinceBox->addItems(model->getContainer()->getProvinces());
    ui->provinceBox_2->addItems(model->getContainer()->getProvinces());
    //ui->provinceBox_3->addItems(model->getContainer()->getProvinces());
    ui->provinceComboBox_3->addItems(model->getContainer()->getProvinces());
    ui->cityBox->addItems(model->getContainer()->getCities());
    ui->shipmentComboBoxRegion->addItems(model->getContainer()->getCities());
    ui->shipmentComboBoxCity->addItems(model->getContainer()->getCities());
    // for the shipment tab
    ui->shipmentComboBoxRegion_2->addItems(model->getContainer()->getCities());
    ui->shipmentComboBoxCity_2->addItems(model->getContainer()->getCities());
    ui->shipmentStatusComboBox->addItems(statusList);



    // add information into the listboxes for Cases
    // add the known diseases first

    ui->diseaseListWidget->addItems(model->getContainer()->getDiseaseListName());
    //ui->diseaseListWidget->setModel(knownCaseModel);
    //ui->diseaseListView->setEditTriggers(QAbstractItemView::NoEditTriggers); // make it read only

    // add the knows locations
  //  knownLocationModel->setStringList(model->getContainer()->getCities());
  //  ui->locationListView->setModel(knownLocationModel);
   // ui->locationListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // set the tableview
    //ui->caseTableView->setModel(tableViewModel);
    //ui->caseTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList labels;
    labels.insert(labels.size(), "Location");
    labels.insert(labels.size(), "Disease Name");
    labels.insert(labels.size(), "Quantity");
    labels.insert(labels.size(), "Date");
    //ui->caseTableWidget->horizontalHeaderItem(0)->setText("UFF");
    ui->caseTableWidget->insertColumn(0);
    ui->caseTableWidget->insertColumn(1);
    ui->caseTableWidget->insertColumn(2);
    ui->caseTableWidget->insertColumn(3);
    ui->caseTableWidget->setHorizontalHeaderLabels(labels);

    QStringList labelsSupplyTable;
    labelsSupplyTable.insert(labelsSupplyTable.size(), "Supply ID");
    labelsSupplyTable.insert(labelsSupplyTable.size(), "Location");
    labelsSupplyTable.insert(labelsSupplyTable.size(), "Quantity");

    ui->knownSuppliesTable->insertColumn(0);
    ui->knownSuppliesTable->insertColumn(1);
    ui->knownSuppliesTable->insertColumn(2);

    ui->knownSuppliesTable->setHorizontalHeaderLabels(labelsSupplyTable);
  //  ui->caseTableWidget->setColumnCount(200);
    //ui->caseTableWidget->setRowCount(200);

    //ui->caseTableWidget->insertColumn(1);

    // set the known locations for the suppply management tab
    //knownLocationModel->setStringList(model->getContainer()->getCities());
    //ui->selectLocationField->setModel(knownLocationModel);
    ui->selectLocationField->addItems(model->getContainer()->getCities());

    /// insert supplies for the supply list widget in the map options tab

    //supplyListModel->setStringList(model->getContainer()->getSupplyTypeListName());
    //ui->selectSupplyField->setModel(supplyListModel);
    ui->selectSupplyField->addItems(model->getContainer()->getSupplyTypeListName());

   // supplyListModel->setStringList(model->getContainer()->getSupplyTypeListName());
   // ui->supplyListWidget->addItems(model->getContainer()->getSupplyTypeListName());

    // insert supplies for the cases in the map options tab
    ui->caseListWidget_2->addItems(model->getContainer()->getDiseaseListName());

    /// insert code here for the map settings tab
    //ui->supplyListView->setModel(supplyListModel);
    ui->supplyListWidget->addItems(model->getContainer()->getSupplyTypeListName());

    /// for the shipment tab
    ui->shipmentSupplyTypeWidget->addItems(model->getContainer()->getSupplyTypeListName());

    /// TESTING CODE FOR SHIPMENT
   /* QDate date(QDate::currentDate());
    QDate date2(QDate::currentDate());
    QDate date3(QDate::currentDate());
    QDate date4(QDate::currentDate());
    Shipment::SHIPMENT_STATUS gl;
    gl = Shipment::PREPARED;

    Shipment *as = new Shipment( 9002, 4, gl, 201, -75.6667, 45.3167, -75.6667, 45.3167, date, date2, date3, date4 );
    model->getContainer()->addShipment(as);
    Supply *bs = new Supply( 5, 4, 500, -75.6667, 45.3167 );
    model->getContainer()->addToSupply(bs);
    QString id = QString::number(as->getID());
    ui->shipmentExistingShipments->addItem(id);

    City *c = model->getContainer()->getSupplyByGeo(bs->getLon(), bs->getLat());

    QString gll = "Supply ID: " + QString::number(bs->getID()) + "    Location: " + c->getCity() + "    Quantity: " +
                  QString::number(bs->getQuantity());
    QString addItem = QString::number(bs->getID());*/
    //ui->knownSuppliesTable->addItem(addItem);

}

void MainWindow::checkInventorySettings() {
    connect (ui->knownSuppliesTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(LoadInventorySettings(QModelIndex)));
}

void MainWindow::checkShipmentSettings() {
    connect( ui->shipmentExistingShipments, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(LoadShipmentSettings(QModelIndex)));
}

void MainWindow::LoadInventorySettings(QModelIndex index) {
    Supply *bs;
    qDebug() << "INDEX" << index.data().toString();
        foreach( int id, this->model->getContainer()->getSupplyID() ) {
        qDebug() << "id:" << index.data().toInt();
        if( id = index.data().toInt() ) {

            Supply *s = model->getContainer()->getSupplyByID(id);
            bs = s;
            qDebug() << "IGOTHERE";
            break;
        }
    }
  //  qDebug() << "Supply" << bs->getID();
    Inventorysettings *i = new Inventorysettings(bs, model, this);
    i->setWindowModality(Qt::ApplicationModal);
    i->setModal(true);
    i->exec();
}

void MainWindow::LoadShipmentSettings( QModelIndex index ) {
    qDebug() << "index.data().toInt():" << index.data().toInt();
    Shipment *tempS; // create a tempshipment to be inserted in the shipmentlist
    Supply *bs;
    // search the shipment id
    foreach( int id, this->model->getContainer()->getShipmentID() ) {
        if( id == index.data().toInt()) {
            Shipment *as = model->getContainer()->getShipmentByID(id);
            tempS = as;
            qDebug() << "found shipment id: " << tempS->getID();
            break;
        }
    }
    foreach( Supply *s, this->model->getContainer()->getSupplies()) {
        qDebug() << "found" << s->getType();
        if( s->getType() == tempS->getType() ) {
            qDebug() << "found this" << s->getType() << tempS->getType();
            bs = model->getContainer()->getSupplyByID(s->getType());
            break;
        }
        else {
            qDebug() << "Supply type id not found";
        }
    }

    ShipmentSettings *s = new ShipmentSettings( tempS, bs, this->model, this );
    s->setWindowModality(Qt::ApplicationModal);
    s->setModal(true);
    s->exec();
}

void MainWindow::UpdateUiOnSelectCases() {
  //  drawHelper->clearCasesSelectionList();
    connect( ui->caseListWidget_2, SIGNAL(itemSelectionChanged()), this, SLOT(updateUIDrawHelperCases()) );

    //connect( ui->diseaseListView, SIGNAL())
}

void MainWindow::UpdateUiOnSelectSupply() {
    drawHelper->clearSupplySelectionList();
    connect( ui->caseListWidget_2, SIGNAL(itemSelectionChanged()), this, SLOT(updateUIDrawHelperSupply()) );
    //connect( ui->diseaseListView, SIGNAL())
}

void MainWindow::debug() {
    qDebug() << "gl";
    //updateLayerInterface();
}

void MainWindow::goToPosition(const QString &name ) {
    QString s1 = model->getContainer()->getCityByName(name);
    qDebug() << "City name: " << s1;
    // when the next line is used, the program produces a segfault
    // figure out why
    float s2 = model->getContainer()->getLatitude(name);
    qDebug() << "Latitude: " << s2;

    float s3 = model->getContainer()->getLonitude(name);
    qDebug() << "Longitude: " << s3;
    GeoDataCoordinates pos(s3, s2, 1500.0, GeoDataCoordinates::Degree);
    ui->MarbleWidget->centerOn(pos);
    //qDebug() << "PATH: " << MarbleDirs::marbleDataPath();
    // fix the zoomview
    connect( this, SIGNAL(setCustomZoom(int)), this, SLOT(setMapZoom(int)));

}

void MainWindow::setMapZoom(int zoom) {
    if( zoom != zoomLevel ) {        zoomLevel = zoom;
        emit setCustomZoom(zoom);
    }
}


void MainWindow::getCitiesFromProvince(const QString &name) {
    qDebug() << "slot getCitiesFromProvince: " << name;
    QStringList s1 = model->getContainer()->getCitiesByProvince(name);

    // make the citybox selection by selection the provinces from provincebox
    ui->cityBox->clear();
    ui->cityBox->addItems(s1);

    // make the locationlistview selection by selecting the provinces from provincebox_2
}

void MainWindow::getCitiesFromProvinceListView( const QString &name ) {
    // make the locationlistview selection by selecting the provinces from provincebox_2
    customCityListModel->setStringList(model->getContainer()->getCitiesByProvince(name));
    //ui->locationListWidget->setModel(customCityListModel);
    ui->locationListWidget->clear();
    ui->locationListWidget->addItems(model->getContainer()->getCitiesByProvince(name));
}

void MainWindow::getCitiesFromProvinceListView_2( const QString &name ) {
    // make the locationlistview selection by selecting the provinces from provincebox_2
    //ui->diseaseListView->setModel(customCityListModel_2);
   // ui->diseaseListWidget->clear();
   // ui->diseaseListWidget->addItems(model->getContainer()->getCitiesByProvince(name));
}

void MainWindow::getCitiesFromProvinceMapView( const QString &name ) {
    // make the locationlistview selection by selecting the provinces from provincebox_2
    customCityListModelMap->setStringList(model->getContainer()->getCitiesByProvince(name));
    ui->regionComboBox->setModel(customCityListModelMap);
}

void MainWindow::getCitiesFromSupplyTab(const QString &name) {
    customCityListSupplyModel->setStringList(model->getContainer()->getCitiesByProvince(name));
    //ui->selectLocationField->setModel(customCityListSupplyModel);
    ui->selectLocationField->clear();
    ui->selectLocationField->addItems(model->getContainer()->getCitiesByProvince(name));
}

void MainWindow::getCitiesForShipment(const QString &name) {
    shipmentModel->setStringList(model->getContainer()->getCitiesByProvince(name));
    ui->shipmentComboBoxCity->setModel(shipmentModel);
}

void MainWindow::updateUIDrawHelperSupply() {
    QList<QListWidgetItem*> supItems = ui->supplyListWidget->selectedItems();
    QList<Supply*>* supplies;
    SupplyCriteria supplySearchCriteria;
    ListContainer *localListContainer = model->getContainer();

    foreach( QListWidgetItem *item, supItems ) {
        supplySearchCriteria.addCriteriaSupplyType(item->text());
    }

    if(supplySearchCriteria.getCriteriaSupplyTypeNames().count() != 0)
    {
        supplies = localListContainer->search(supplySearchCriteria);//this performs search
    }else
    {
        supplies = new QList<Supply*>();
    }

    //supplies = localListContainer->search(supplySearchCriteria);//

    drawHelper->clearSupplySelectionList();
    foreach( Supply *s, *supplies ) {
        //qDebug() << s->getLon() << s->getLat();
        GeoDataCoordinates dat(s->getLon(), s->getLat(),
                               0.0,
                               GeoDataCoordinates::Degree);
        QColor color(QColor::fromRgb(255,0,0));
        drawHelper->setCoordinatesSupplies(dat, color);
    }

    supplies->clear();
}

void MainWindow::updateUIDrawHelperCases() {
    qDebug() << "THIS IS:" << ui->caseListWidget_2->selectedItems();
    QList<QListWidgetItem*> selItems=ui->caseListWidget_2->selectedItems();


    qDebug() << selItems;
    //if( supItems)

    ListContainer *localListContainer = model->getContainer();
    QList<DiseaseCase*>* diseases;

    DiseaseCriteria diseaseSearchCriteria;

    QString regionSelected = ui->regionComboBox->currentText();


    //for( int i = 0; i < selItems.count(); ++i ) {
     //   QListWidgetItem* newItem = selItems.at(i);
   //     diseaseSearchCriteria.addDiseaseType(newItem->text());//adding the disease Type to the search criteria
    //}
    foreach( QListWidgetItem *item, selItems ) {
        diseaseSearchCriteria.addDiseaseType(item->text());
    }
    qDebug() << diseaseSearchCriteria.getDiseaseTypeNames().count();
    if(diseaseSearchCriteria.getDiseaseTypeNames().count() != 0)
    {
        diseases = localListContainer->search(diseaseSearchCriteria);//this performs search
    }else
    {
        diseases = new QList<DiseaseCase*>();
    }

   drawHelper->clearCasesSelectionList();
   foreach( DiseaseCase *c, *diseases ) {
      //  qDebug() << c->getLon() << c->getLat();
        GeoDataCoordinates dat(c->getLon(), c->getLat(),
                               0.0,
                               GeoDataCoordinates::Degree);
        QColor color(QColor::fromRgb(0,0,255));
        drawHelper->setCoordinatesCases(dat, color);
   }

   diseases->clear();
    return;
}

void MainWindow::updateLayerInterfaceCases() {
    //drawHelper->clearSupplySelectionList();
    drawHelper->clearCasesSelectionList();
    connect( ui->caseListWidget_2, SIGNAL(itemSelectionChanged()), this, SLOT(updateUIDrawHelperCases()));
    connect( ui->caseListWidget_2, SIGNAL(itemSelectionChanged()), ui->MarbleWidget, SLOT(update()));
    //connect( ui->supplyListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(updateUIDrawHelper()));
//    connect( ui->diseaseListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(CreateAndUpdateTable()));
}

void MainWindow::updateLayerInterfaceSupply() {
    drawHelper->clearCasesSelectionList();
    connect( ui->supplyListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(updateUIDrawHelperSupply()));
    connect( ui->supplyListWidget, SIGNAL(itemSelectionChanged()), ui->MarbleWidget, SLOT(update()));
}

void MainWindow::connectToServer() {
    model->connectToServer();
}

void MainWindow::disconnectFromServer() {
    model->disconnectFromServer();
}

void MainWindow::setUIRelatedConnections() {
    // set the actions to connect/disconnect
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connectToServer()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnectFromServer()));

    // set case management related connections
    connect( ui->MaxCaseEdit, SIGNAL(textChanged(QString)), this, SLOT(getMaxItems(QString)));
    connect( ui->MinCaseEdit, SIGNAL(textChanged(QString)), this, SLOT(getMinItems(QString)));
    connect( ui->fromDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(getFromDateEdit(QDate)));
    connect( ui->ToDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(getToDateEdit(QDate)));

    connect( ui->minSupplyField, SIGNAL(textChanged(QString)), this, SLOT( getMinSupplyItems(QString)));
    connect( ui->maxSupplyField, SIGNAL(textChanged(QString)), this, SLOT( getMaxSupplyItems(QString)));

    connect( ui->actionConnect, SIGNAL(triggered(bool)), ui->actionDisconnect, SLOT(setEnabled(bool)));
}

void MainWindow::getMinSupplyItems(const QString &text) {
    minSupplyItems = text.toFloat();
}

void MainWindow::getMaxSupplyItems(const QString &text ) {
    maxSupplyItems = text.toFloat();
}

void MainWindow::getMaxItems(const QString &text) {
    maxCases = text.toFloat();
}

void MainWindow::getMinItems(const QString &text) {
    qDebug() << text;
    minCases = text.toFloat();
}

void MainWindow::getFromDateEdit(QDate date) {
    fromDateCase = date;
}

void MainWindow::getToDateEdit(QDate date) {
    toDateCase = date;
}

void MainWindow::CreateAndUpdateSupplyTable() {
    QList<QListWidgetItem*> selItems = ui->selectSupplyField->selectedItems();
    QList<QListWidgetItem*> locItems = ui->selectLocationField->selectedItems();


    ui->knownSuppliesTable->setColumnCount(3);
    int row = 0;
    ui->knownSuppliesTable->setRowCount(row);

    QList<Supply*> *localSupplies;
    ListContainer* localListContainer = model->getContainer();
    QList<City*>* localCityList = model->getContainer()->getCities(localCityList);
    SupplyCriteria supplyCriteria;
    //find selected supplies
    foreach( QListWidgetItem *locItem, locItems ) {
        foreach( QListWidgetItem *selItem, selItems ) {
            QTableWidgetItem *lItem = new QTableWidgetItem();//region name
            QTableWidgetItem *sItem = new QTableWidgetItem();//supply
            lItem->setText(locItem->text());
            sItem->setText(selItem->text());

            supplyCriteria.addCity(locItem->text());
            supplyCriteria.addCriteriaSupplyType(sItem->text());

            lItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        }
    }

    supplyCriteria.setMin(this->minSupplyItems);
    supplyCriteria.setMax(this->maxSupplyItems);



    localSupplies = localListContainer->search(supplyCriteria);

    //present searched supplies
    foreach(Supply *s, *localSupplies)
    {
        QTableWidgetItem *lItem = new QTableWidgetItem();//region name
        QTableWidgetItem *sItem = new QTableWidgetItem();//supply
        QTableWidgetItem *qItem = new QTableWidgetItem();//supply
        lItem->setText(localListContainer->findCity(s->getLon(),s->getLat())->getCity());
        sItem->setText(localListContainer->getSupplyTypeByID(s->getType())->getName());
        qItem->setText(QString::number(s->getQuantity()));

        ui->knownSuppliesTable->insertRow(row);
        ui->knownSuppliesTable->setItem(row, 0, lItem );
        ui->knownSuppliesTable->setItem(row, 1, sItem );
        ui->knownSuppliesTable->setItem(row, 2, qItem );
        row++;
    }

    qDebug() << "number of supplies returned from search:" << localSupplies->count();
    qDebug() << "supplies return from search";
    foreach(Supply *s,*localSupplies)
    {
       qDebug() << s->print();
    }


}


// set and update the table for searching the objects
void MainWindow::CreateAndUpdateTable() {
        QList<QListWidgetItem*> selItems = ui->diseaseListWidget->selectedItems();
        QList<QListWidgetItem*> locItems = ui->locationListWidget->selectedItems();

        if( selItems.isEmpty() && locItems.isEmpty() ) {

        }

        if( !diseaseSearchObjects.isEmpty() )
            diseaseSearchObjects.clear();

        if( !locationSearchObjects.isEmpty() )
            locationSearchObjects.clear();

        ui->caseTableWidget->setColumnCount(4);

        QList<DiseaseCase*> *localDiseaseCases;
        ListContainer* localListContainer = model->getContainer();
        QList<City*>* localCityList = model->getContainer()->getCities(localCityList);
        DiseaseCriteria diseaseCriteria;

        int row = 0;
       //this adds gets the selected items and adds them to the criteria object
        ui->caseTableWidget->setRowCount(row);


        foreach( QListWidgetItem *locItem, locItems ) {

            foreach( QListWidgetItem *selItem, selItems ) {
                QTableWidgetItem *lItem = new QTableWidgetItem();
                QTableWidgetItem *dItem = new QTableWidgetItem();
                lItem->setText(locItem->text());
                dItem->setText(selItem->text());

                diseaseCriteria.addCity(lItem->text());
                diseaseCriteria.addDiseaseType(dItem->text());

            }
        }
            row = 0;

        diseaseCriteria.setMaxQuantity(this->maxCases);
        diseaseCriteria.setMinQuantity(this->minCases);

        diseaseCriteria.setStartDate(this->fromDateCase); qDebug()<< "Date Range: start:" << this->fromDateCase.toString("ddd MMMM d yyyy") << "end:" << this->toDateCase.toString("ddd MMMM d yyyy");
        diseaseCriteria.setEndDate(this->toDateCase);

       localDiseaseCases = localListContainer->search(diseaseCriteria);
       qDebug() << diseaseCriteria.print();
       qDebug() << "localDiseaseCases Count:" << localDiseaseCases->count();

       //place text into table
        ui->caseTableWidget->setRowCount(row);
        foreach(DiseaseCase *d, *localDiseaseCases ) {

                QTableWidgetItem *lItem = new QTableWidgetItem();
                QTableWidgetItem *dItem = new QTableWidgetItem();
                QTableWidgetItem *quantItem = new QTableWidgetItem();
                QTableWidgetItem *dateItem = new QTableWidgetItem();
                lItem->setText(localListContainer->findCity(d->getLon(),d->getLat())->getCity());
                dItem->setText(localListContainer->getDiseaseTypeByID(d->getType())->getName());
                quantItem->setText(QString::number(d->getQuantity()));
                dateItem->setText(d->getDate().toString("ddd MMMM d yyyy"));

                ui->caseTableWidget->insertRow(row);

                ui->caseTableWidget->setItem(row, 0, lItem );
                ui->caseTableWidget->setItem(row, 1, dItem);
                ui->caseTableWidget->setItem(row, 2, quantItem);
                ui->caseTableWidget->setItem(row, 3, dateItem);
                row++;
        }

}

void MainWindow::refreshContainer() {

}







///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////TEST ZONE BEGINS/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void MainWindow::LeighsTestStuff()
{
    populateContainer();
   //testDiseaseCaseCriteria();
    //testSupplyCriteria();
    testShipmentCriteria();
    //testXML();
}

void MainWindow::populateContainer()
{
    //populate diseaseCases
    ListContainer *localContainer = this->model->getContainer();
    QList<City*>* localCityList = localContainer->getCities(localCityList);
    int numberToAdd = 2000;
    for(int i = 0;i < numberToAdd;i++)
    {
        int id = getRandNum(0,10000);
        int type = getRandNum(0,localContainer->getDiseaseTypes()->count()-1);

        int quantity = getRandNum(0,100);

        City *city = localCityList->at(getRandNum(0,localCityList->count()-1));

        QDate date(getRandNum(2010,2010),getRandNum(1,12),getRandNum(1,28));
        DiseaseCase *newCase = new DiseaseCase(id,type,quantity,city->getLong(),city->getLat(),date);
        localContainer->addDiseaseCase(newCase);
    }
    qDebug() << "number of DiseaseCases Added: " << numberToAdd;


    //populates SupplyList


    numberToAdd = 2000;
    for(int i = 0;i < numberToAdd;i++)
    {
        int id = getRandNum(0,10000);
        int type = getRandNum(0,localContainer->getSupplyTypes()->count()-1);
        int quantity = getRandNum(0,100);
        City *city = localCityList->at(getRandNum(0,localCityList->count()-1));
        Supply *newSupply = new Supply(id,type,quantity,city->getLong(),city->getLat(),QDate(getRandNum(1401,3500),getRandNum(1,12),getRandNum(1,28)));
        localContainer->addToSupply(newSupply);
        //qDebug() << newSupply->print();

    }
    numberToAdd = 2000;
    for(int i = 0;i < numberToAdd;i++)
    {
        int id = getRandNum(0,10000);
        int type = getRandNum(0,localContainer->getSupplyTypes()->count()-1);
        Shipment::SHIPMENT_STATUS status = Shipment::PREPARED;

        int quantity = getRandNum(0,100);
        City *destination = localCityList->at(getRandNum(0,localCityList->count()-1));
        City *sender      = localCityList->at(getRandNum(0,localCityList->count()-1));

        QDate sentDate(getRandNum(1401,3500),getRandNum(1,12),getRandNum(1,28));
        QDate expectedDate(getRandNum(1401,3500),getRandNum(1,12),getRandNum(1,28));
        QDate createdDate(getRandNum(1401,3500),getRandNum(1,12),getRandNum(1,28));
        QDate receivedDate(getRandNum(1401,3500),getRandNum(1,12),getRandNum(1,28));
        Shipment *newShipment = new Shipment(id,type,status,quantity,sender->getLong(),sender->getLat(),destination->getLong(),destination->getLat(),createdDate,sentDate,expectedDate,receivedDate);
                                             //destination->getLong(), destination->getLat(),createdDate,sentDate,expectedDate,receivedDate);
        localContainer->addShipment(newShipment);


    }

    return;
}

void MainWindow::testDiseaseCaseCriteria()
{
    ListContainer *localContainer = this->model->getContainer();

    QList<DiseaseCase*> *localDiseaseCases;
    QList<City*>* localCityList = localContainer->getCities(localCityList);
    DiseaseCriteria diseaseCriteria;
    //add any things you want to search into the criteria object then pass it into the list container search function

    //diseaseCriteria.addCity("Toronto");

    //qDebug() << diseaseCriteria.print();

    localDiseaseCases = localContainer->search(diseaseCriteria);


    //used for printing the disease cases returned from the search
    for(int i = 0; i < localDiseaseCases->count();i++)
    {
    DiseaseCase *diseaseCase = localDiseaseCases->at(i);
    qDebug() << diseaseCase->print();
    qDebug() << "City " <<localContainer->findCity(diseaseCase->getLon(),diseaseCase->getLat())->getCity();

    }
    qDebug() << "number of DiseaseCases returned from search: " << localDiseaseCases->count();
    return;
 }
void MainWindow::testSupplyCriteria()
{

    //get Supplies by TypeName            works
    //get Supplies by TypeID              works
    //get Supplies Within Min max Range   works
    //get Supplies by city names          works
    //get Supplies by city objects        works
    //all functionality works properly in combination with eachother
    ListContainer *localContainer = this->model->getContainer();
    QList<Supply*> *supplies;
    QList<City*>* localCityList = localContainer->getCities(localCityList);
    SupplyCriteria supplyCriteria;
    //add supplies criteria you want to test here

    //supplyCriteria.addCriteriaCity(localCityList->at(2));

    qDebug() << "searching City: " << localCityList->at(2)->getCity();


    supplies = localContainer->search(supplyCriteria);
    foreach(Supply* s, *supplies)
    {
        qDebug() << s->print();
    }
    qDebug() << QString("There were %1 supplies returned from search").arg(supplies->count());
    return;
}


void MainWindow::testXML()
{

}

void MainWindow::testShipmentCriteria()
{

    //testing by Sendin City Objects        works
    //testing by Sendin City Names          works
    //testing by recieving City Object      works
    //testing by recieving City Name        works
    //testing by supplyType                 works
    //testing by supplytypeNames            works
    //testing by quantity range             works
    //testing by date range                 works
    //testing by shipment status


    ListContainer *localContainer = this->model->getContainer();

    QList<Shipment*> *localShipments;
    QList<City*>* localCityList = localContainer->getCities(localCityList);
    ShipmentCriteria shipmentCriteria;
    //add any things you want to search into the criteria object then pass it into the list container search function


    localShipments = localContainer->search(shipmentCriteria);
    //used for printing the disease cases returned from the search
    foreach(Shipment *s,*localShipments)
    {

       qDebug() << s->print();
    //qDebug() << "City " <<localContainer->findCity(s->getLon(),s->getLat())->getCity();

    }
    qDebug() << "number of shipments returned from search: " << localShipments->count();
    return;
}
//returns a random number between min and max
int MainWindow::getRandNum(int min, int max)
{

    if(min >= max){return 0;}
    int randNumber =(qrand()%(max+1-min))+min;
    return randNumber;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////TEST ZONE ENDS/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*
#include <marble/MarbleNavigator.h>
#include <marble/MarbleWidget.h>
 */
/// TODO:
/**
  TABLE VIEW: TYPE, QUANTITY, LOCATION, LAST UPDATED

  **/
