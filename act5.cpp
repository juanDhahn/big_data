/* Compile: g++ act5.cpp -o act5.exe -lpq && ./act5.exe */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <postgresql/libpq-fe.h>
using namespace std;

int main() 
{
  clock_t time_init;
  clock_t time_end;

  time_init = clock();

  // Initiate connection
  PGconn *dbconn = PQconnectdb("user=postgres dbname=postgres");

  // Test connection
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    cout << "Unable to connect to database\n";
    cout << PQerrorMessage(dbconn);
  }
  else {
    cout << "Connection to database OK\n";
  }

  // Execute query
  PGresult *query; 
  query = PQexec(dbconn, "BEGIN");
  PQclear(query);
  query = PQexec(dbconn, "DECLARE cur_edad CURSOR FOR SELECT edad FROM personas1");

  // Initialize array with 0
  int edades [100] = {};

  for (int i = 0; i < 175000; i++) {
    PQclear(query);
    query = PQexec(dbconn, "FETCH FORWARD 200 in cur_edad");
    
    for (int j = 0; j < int(PQntuples(query)); j++) {

      int key = atoi(PQgetvalue(query, j, 0));
      edades[key] += 1;     
      
    }
  }
  
  time_end = clock();

  // Print results
  int sum = 0;
  for (int i = 1; i < 100; i++){
    // cout << i << " -> " << edades[i] << endl;
    sum = sum + edades[i];
  }  

  cout << "Total: " << sum << endl;
  cout << "Tiempo: " << (double) (time_end - time_init) / CLOCKS_PER_SEC << " seg" << endl;
    
  // Close cursor and clear query
  PQclear(query);
  query = PQexec(dbconn, "CLOSE cur_edad");
  PQclear(query);
  query = PQexec(dbconn, "COMMIT");
  PQclear(query);

  // Close connection
  PQfinish(dbconn);

  return 0;
}
