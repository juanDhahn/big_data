#include <iostream>
#include <postgresql/libpq-fe.h>
using namespace std;

int main() 
{
  // Initiate connection
  PGconn *dbconn = PQconnectdb("user=postgres dbname=postgres");

  // Test connection
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    cout << "Unable to connect to database\n";
    cout << PQerrorMessage(dbconn);
  }
  else{
    cout << "Connection to database OK\n";
  }


  // Result holder
  // PGresult *query;

  // Execute a query
  // query = PQexec(dbconn, "select * from mytable");

  // Use the values
  // printf ("%s\n", PQgetvalue(query, 0, 1));

  // Close connection
  PQfinish(dbconn);

  return 0;
}
