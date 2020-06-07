#include <iostream>
#include <vector>
#include <set>
#include <fstream> 
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

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
  ifstream fe("petersen_1");

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

  //Write in format DIMACS the boolean equations
  int colores = 3;
  int num_var = nodos.size()*colores;
  int incremento = 0, ecuaciones = 0;
  stringstream ss; //stream where i put the results equation before dumping in the file.
  
  //Each node must take only 1 color
  for(size_t i = 1; i <= num_var; i=i+colores)
  {
      for(size_t j = 0; j < colores; ++j)
	ss << i + j << " ";
      ss << "0" << endl;
      ++ecuaciones;
      for(size_t j = i; j <= colores + incremento*colores; ++j)
      {
	  for(size_t z = j+1; z <= colores + incremento*colores; ++z)
	    {
	      ss << "-" << j << " " << "-" << z << " " << 0 << endl;
	      ++ecuaciones;
	    }
	}
      ++incremento;
    }

  int left, right;
  //Represent connections between nodes
  for(size_t i = 0; i < nodos.size(); ++i)
    {
      for(size_t j = 0; j < conexiones[i].size(); ++j)
	{
	  //Check nodos[i] conexiones[i][j]
	  left = nodos[i];
	  right = conexiones[i][j];
	  for(size_t z = 1; z <= colores; ++z)
	    {
	      ss << "-" << z + (left-1)*colores << " -" << z + (right-1)*colores
		 << " 0" << endl;
	      ++ecuaciones;
	    }
	}
    }

  //cout << "Ecuaciones " << ecuaciones << endl;
  ofstream fs("output");
  fs << "p cnf " <<  num_var <<  " " <<  ecuaciones << "\n";
  fs << ss.str();
  fs.close();
}
