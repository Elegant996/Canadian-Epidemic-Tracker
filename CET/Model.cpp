#include "include/Model.h"
#include "include/ClientParser.h"

Model::Model() {
    managerMade = false;
    container = new ListContainer();
    //p = new ClientParser();

    // set up the connection management
    //connection = new ConnectionManagement();

}

Model::~Model() {
    if( container != NULL ) {
        delete container;
        container = 0;
    }
}

// dummy comment
ListContainer *Model::getContainer() {
    return container;
}

void Model::connectToServer() {
    if (!managerMade)
    {
        connection = new ConnectionManagement(container);
        managerMade = true;
    }
    connection->connectToServer();
}

void Model::disconnectFromServer() {
    if (connection->disconnectedByClient())
    {
        managerMade = false;
        delete connection;
    }
}
