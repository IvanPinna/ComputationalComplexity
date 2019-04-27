#include <iostream>
#include <vector>
#include <fstream> 
#include <string>

using namespace std;


int main()
{
  
  vector<vector<int> > ady_list;
  string str, delimiter = ":";
  bool bandera;
  ifstream fe("grafo");
  
  int posicion, contador;
  size_t pos = 0;
  while(getline(fe, str))
  {
    cout << str << endl;
    bandera = true;
    delimiter = ":";
    while(!str.empty()) //Split by spaces
    {
      ++contador;
      if(bandera)
      {
	int iterador = str.find(delimiter);
	posicion = stoi(str.substr(0,iterador));
	cout << "Nodo: " << posicion << endl;
	str.erase(0, iterador + 1);
	bandera = false;
	delimiter = ",";
      }

      pos = str.find(delimiter);
      cout << "conexion: " << str.substr(0,pos) << endl;
      str.erase(0, pos + 1); //En este caso delimiter vale 1
    }
    
  }
}
