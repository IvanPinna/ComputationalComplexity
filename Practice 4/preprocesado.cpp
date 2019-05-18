#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <math.h>


using namespace std;

struct ciudad{
  int id_;
  float x_, y_;

  ciudad()
  {}
  
  ciudad(int id, float x, float y):id_(id), x_(x), y_(y)
  {}

  void imprimir()
  {
    cout << "id: " << id_
	 << " x-> " << x_
	 << " y-> " << y_ << endl;
  }
};

struct candidate{
  vector<int> orden;
  double coste;
}

vector<ciudad> lectura_mapa(const string& nombre)
{
  ifstream fe("kroA100.tsp");
  string str;
  regex reg("[0-9]+");
  regex endfile("EOF");
  sregex_iterator end;
  int contador = 0, id, tope;
  vector<ciudad> ciudades;
  float x, y;
    
  for(int i = 0; i < 7; ++i) //Burn the first six lines
    getline(fe, str);

  while(!regex_search(str, endfile)){
      sregex_iterator it(str.begin(), str.end(), reg);
      id =  stoi((*it).str()); 
      x =  stoi((*(++it)).str());  
      y = stoi((*(++it)).str());
      
      ciudades.push_back(ciudad(id, x, y));
      //ciudades.at(contador).imprimir();
      getline(fe, str);
      ++contador;
    }
    
  fe.close();
  return ciudades;
}

vector<int> generar_poblacion(int tam)
{
  cout << "Tam " << "<- " << tam << endl;
  srand(time(NULL));
  //Falta inicializar semilla con los segundos del sistema. 
  bool *posiciones = new bool[tam];
  vector<int> resultado;
  int contador = 0, aleatorio;

  for(int i = 0; i < tam; ++i)
    posiciones[i] = false;
  
  while(contador < tam)
  {
    aleatorio = rand()%tam + 1; //Numeros entre 1 y tam
    if(!posiciones[aleatorio])
      {
	resultado.push_back(aleatorio);
	posiciones[aleatorio] = true;
	contador++;
      }
  }
  
  delete posiciones;
  return resultado;
}

double euclidea(const ciudad& c1, const ciudad& c2)
{
  return sqrt(pow(c2.x_ - c1.x_ , 2) + pow(c2.y_ - c1.y_, 2));
}

double evaluacion(const vector<ciudad>& nodos, const vector<int>& orden)
{
  double resultado = 0;
  ciudad c1, c2;
  //Calcular la distancia entre las distintas ciudades.
  for(int i = 0; i < orden.size()-1; ++i)
    resultado += euclidea(nodos.at(orden.at(i)-1),nodos.at(orden.at(i+1)-1));

  //Calcular distancia entre última ciudad y la primera.
  resultado += euclidea(nodos.at(orden.at(0)),
			nodos.at(orden.at(orden.size()-1)));

  resultado += euclidea(c1,c2);

  c1.imprimir(); c2.imprimir();
  cout << "Resultado " << resultado << endl;
  
  return resultado;
}
/***
 population_size -> Tamaño de la población
 population -> vector con los candidatos (posibles soluciones)
 condicion de parada -> 100 iteraciones
***/
int main(){
  string nombre = "kroA100.tsp";
  vector<ciudad> nodos = lectura_mapa(nombre);
  int population_size = 10, iteraciones = 0; //Numero de soluciones.
  vector<candidate> population = generar_poblacion(nodos.size());
  vector<int> mejor = get_best_solution(population);
  //evaluacion(nodos, orden);
  
  while(iteraciones < 100) //Condicion de parada
  {
    parents = selectParents(population, population_size);
    ++iteraciones;
  }
  
}
