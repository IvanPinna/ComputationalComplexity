#include <iostream>
#include <vector>
#include <set>
#include <fstream> 
#include <string>
#include <cstdlib>

using namespace std;

struct pareja{
    int a_, b_;
    pareja(int a, int b):a_(a),b_(b)
    {}
    
};

bool operator<(const pareja& x, const pareja& y)
{
    return x.a_ < y.a_;
}

bool operator==(const pareja& x, const pareja& y)
{
    bool bandera = false;
    if(x.a_ == y.a_ and x.b_ == y.b_)
        bandera = true;
    if(x.b_ == y.a_ and x.a_ == y.b_)
        bandera = true;
    if(x.a_ == y.b_ and x.b_ == y.a_)
        bandera = true;
    return bandera;
}

void visualizar_vectores(const vector<int>& nodos, const vector<vector<int>>& conexiones)
{
  for(size_t i = 0; i < nodos.size(); ++i)
  {
    cout << nodos[i] << ":";
    for(size_t j = 0; j < conexiones[i].size(); ++j)
      cout << conexiones[i][j] << ",";
    cout << " " << endl;
  }
}


void leer_fichero(vector<int>& nodos, vector<vector<int>>& conexiones)
{
  string str, delimiter = ":";
  bool bandera;
  ifstream fe("grafo");

  size_t pos, contador = 0;
  int nodo;
  while(getline(fe, str))
  {
    //cout << str << endl;
    bandera = true;
    delimiter = ":";
    while(!str.empty()) //Split by spaces
    {
      if(bandera)
      {
	pos = str.find(delimiter);
	nodo = atoi(str.substr(0,pos).c_str());
	nodos.push_back(nodo);
	conexiones.push_back(vector<int>()); 
	str.erase(0, pos + 1);
	bandera = false;
	delimiter = ",";
      }

      pos = str.find(delimiter);
      //cout << "conexion: " << str.substr(0,pos) << endl;
      conexiones[contador].push_back(atoi(str.substr(0,pos).c_str()));
      str.erase(0, pos + 1); //En este caso delimiter vale 1
    }
    ++contador;
  }
}

int main()
{
  vector<int> nodos;
  vector<vector<int> > conexiones;

  //Load de graph in memory from file.
  leer_fichero(nodos, conexiones);
  cout << "VISUALIZANDO FICHERO" << endl;
  visualizar_vectores(nodos, conexiones);
  cout << "FIN VISUALIZACION" << endl;
  //Write in format DIMACS the boolean equations
  int colores = 3;
  int num_var = nodos.size()*colores;
  int incremento = 0;
  
  //Each node must take only 1 color
  for(size_t i = 1; i <= num_var; i=i+colores)
  {
    for(size_t j = 0; j < colores; ++j)
      cout << i + j << " ";
    cout << "0" << endl;

    for(size_t j = i; j <= colores + incremento*colores; ++j)
    {
      for(size_t z = j+1; z <= colores + incremento*colores; ++z)
      {
	cout << "-" << j << " " << "-" << z << " " << 0 << endl;
      }
    }
    ++incremento;
  }
  

  int left, right;
  //set<pareja> lista;
    //Represent connections between nodes
    for(size_t i = 0; i < nodos.size(); ++i)
    {
      for(size_t j = 0; j < conexiones[i].size(); ++j)
      {
	//Check nodos[i] conexiones[i][j]
	left = nodos[i];
	right = conexiones[i][j];
	//if(lista.insert(pareja(left,right)).second) //The connection isn't written
	//{
	  for(size_t z = 1; z <= colores; ++z)
	    cout << "-" << z + (left-1)*colores << " -" << z + (right-1)*colores
		 << " 0" << endl;
	//}
      }
    }
}
