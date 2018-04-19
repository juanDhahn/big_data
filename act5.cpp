/* Compile: g++ act5.cpp -o act5.exe -lpq && ./act5.exe */
#include <iostream>
#include <string.h>
#include <map>
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
  else {
    cout << "Connection to database OK\n";
  }

  // Execute query
  PGresult *query; 
  query = PQexec(dbconn, "BEGIN");
  PQclear(query);
  query = PQexec(dbconn, "DECLARE cur_edad CURSOR FOR SELECT edad FROM personas1");

  // Declare map for results
  map<string,int> map_edades;

  for (int i = 0; i < 10000; i++) {
    PQclear(query);
    query = PQexec(dbconn, "FETCH FORWARD 3500 in cur_edad");
    
    for (int j = 0; j < int(PQntuples(query)); j++) {

      string key = PQgetvalue(query, j, 0);
      
      // Check if key exist in map
      if(map_edades.find(key) != map_edades.end()) {
        map_edades[key] = map_edades[key] + 1;
      }
      // if not create new key
      else {
        map_edades.insert(make_pair(key,1));
      }

    }


    /*
    // Check if query is OK
    if (strlen(PQresultErrorMessage(query)) == 0) {
      
      // Print result
      for (int j = 0; j < int(PQntuples(query)); j++) {
        cout << PQgetvalue(query, j, 0) << endl;
      }

      cout << "Fetched rows: " << PQntuples(query) << endl;

    }
    else {  
      cout << PQresultErrorMessage(query);
    }
    */
  }
  
  for (map<string,int>::iterator it = map_edades.begin(); it != map_edades.end(); ++it){
    cout << it -> first << " -> " << it -> second << endl;
  }
    
  
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
