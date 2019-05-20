#include <iostream>
#include <vector>

using namespace std;

vector<int> generar_elemento(int ciudades)
{
  vector<int> array, solucion;
  int aleatorio;
  
  for(int i = 0; i < ciudades; ++i)
    array.push_back(i);

  while(array.size() > 0){
    aleatorio = rand()%array.size(); //Genera valores entre 0 y tam.
    solucion.push_back(array[aleatorio]);
    array.erase(array.begin() + aleatorio); //Borramos posicion del array. 
  }
  return solucion; 
}

vector<vector<int>> generar_poblacion(int tam_poblacion, int ciudades)
{
  vector<vector<int>> poblacion;
  srand(time(NULL));
  for(int i = 0; i < tam_poblacion; ++i)
    poblacion.push_back(generar_elemento(ciudades));

  return poblacion;
}

void mostrar_elemento(const vector<int>& elemento){
  for(unsigned i = 0; i < elemento.size(); ++i)
    cout << elemento[i] << " ";
  cout << endl;
}

void calcula_distancia(vector<int> ciudades, vector<vector<int>> poblacion)
{
  vector<int> elemento;
  double dist = 0;
  
  for(int i = 0; i < poblacion.size(); ++i)
  {
    elemento = poblacion.at(i);
    cout << "Elemento " << i << endl;
    for(int i = 0; i < elemento.size()-1; ++i)
    {
      cout << "Comparando ciudad " << ciudades.at(elemento.at(i))
	   << " con ciudad " << ciudades.at(elemento.at(i+1)) << endl;
    }
    cout << "Comparando ciudad "<< ciudades.at(elemento.at(elemento.size()-1))
	 << " con ciudad " << ciudades.at(elemento.at(0)) << endl;
    
  }
}

int main(){
  int tam_ciudades = 10, tam_poblacion = 2;
  
  vector<vector<int>> poblacion;
  vector<int> ciudades;
  
  srand(time(NULL));
  poblacion = generar_poblacion(tam_poblacion, tam_ciudades);

  for(unsigned i = 0; i < tam_ciudades; ++i)
    ciudades.push_back(i+1);
  
  for(unsigned i = 0; i < poblacion.size(); ++i)
  {
    cout << "Elemento " << i  << endl;
    mostrar_elemento(poblacion[i]);
  }

  calcula_distancia(ciudades, poblacion);
}
