/* Compile: g++ act5b.cpp -o act5b.exe -lpq && time ./act5b.exe */
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main() 
{
  // Open file
  ifstream file("millones2");

  if (file.is_open()){
    cout << "File open OK" << endl;
  }
  
  // Rut|Nombre|Edad|Direccion
  string rut;
  string nombre;
  string edad; 
  string direccion;
    
  // Initialize array with 0
  int edades [100] = {};

  // Read file
  while (file.good()){

      getline(file, rut, '|');
      getline(file, nombre, '|');
      getline(file, edad, '|');
      getline(file, direccion, '\n');

      edades[atoi(edad.c_str())] += 1;     
  }
  
  // Print results
  int sum = 0;
  for (int i = 1; i < 100; i++){
    cout << i << " -> " << edades[i] << endl;
    sum = sum + edades[i];
  }  

  cout << "Total: " << sum << endl;
    
  // Close file
  file.close();

  return 0;
}
