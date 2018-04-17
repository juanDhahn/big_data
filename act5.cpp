#include <iostream>
#include "libpq-fe.h"
using namespace std;

/* Close connection to database */
void CloseConn(PGconn *conn)
{
  PQfinish(conn);
  getchar();
}

/* Establish connection to database */
PGconn *ConnectDB()
{
  PGconn *conn = NULL;

  // Make a connection to the database
  conn = PQconnectdb("user=postgres password=postgres dbname=postgres hostaddr=127.0.0.1 port=5432");

  // Check to see that the backend connection was successfully made
  if (PQstatus(conn) != CONNECTION_OK)
  {
    cout << "Connection to database failed.\n";
    CloseConn(conn);
  }

  cout << "Connection to database - OK\n";

  return conn;
}

int main() 
{
    cout << "Hello, World!"<<endl;
    return 0;
}