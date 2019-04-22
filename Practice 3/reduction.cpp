#include <iostream>
#include <vector>
#include <fstream> 
#include <string>

using namespace std;


int main()
{
  
  vector<vector<int> > ady_list;
  string str, delimiter = " ";
  bool bandera;
  ifstream fe("grafo");

  int posicion;
  size_t pos = 0;
  while(getline(fe, str))
  {
    bandera = true;
    while((pos = str.find(delimiter)) != string::npos) //Split by spaces
    {
      if(bandera)
      {
	posicion = stoi(str.substr(0,pos));
	//cout << "Posicion ->" << posicion << endl;
	bandera = false;
      }else
      {
	//Comprueba como le puedes insertar valores al vector. 
	//ady_list[posicion].push_back(stoi(str.substr(0,pos)));
	int xd = stoi(str.substr(0,pos));
	cout << xd; 
      }
      str.erase(0, pos + delimiter.length());
    }
    
  }
}
