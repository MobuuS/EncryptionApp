#include <iostream>
#include <libpq-fe.h>
#include "App.h"


/*
 * PQconn = stores the connection information
 * PQstatus = shows connection status
 * PQfinish = closes all connections
 */

int main() {
    const char* connectionInfo = "dbname=localDB user=postgres password=admin host=localhost port=5432";
    PGconn* connection = PQconnectdb(connectionInfo);

    if (PQstatus(connection) != CONNECTION_OK) {
        cout << "Database connection failed with an error: " << PQerrorMessage(connection);
        PQfinish(connection);
    }
    std::cout << "Connected successfully!\n";
    PQfinish(connection);

    App::Start();
    return 0;
}
