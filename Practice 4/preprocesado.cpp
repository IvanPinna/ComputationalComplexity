#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <math.h>
#include <limits> 

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

struct gen{
  vector<int> sequence_;
  double cost_;

  gen(vector<int> sequence):sequence_(sequence), cost_(-1) //Ojo con el -1
  {}
  
  gen()
  {}
};

struct pareja{
    int x_, y_;
    
    pareja(int x, int y):x_(x), y_(y)
    {}
    
    pareja()
    {}
};


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


gen generar_elemento(int ciudades)
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
  return gen(solucion); 
}

vector<gen> generar_poblacion(int tam_poblacion, int ciudades)
{
  vector<gen> poblacion;
  srand(time(NULL));
  for(int i = 0; i < tam_poblacion; ++i)
    poblacion.push_back(generar_elemento(ciudades));

  return poblacion;
}

double euclidea(const ciudad& c1, const ciudad& c2)
{
  return sqrt(pow(c2.x_ - c1.x_ , 2) + pow(c2.y_ - c1.y_, 2));
}

void evaluate_population(const vector<ciudad>& ciudades, vector<gen>& poblacion)
{
  vector<int> sequence;
  double distance;
  for(unsigned i = 0; i < poblacion.size(); ++i)
  {
    sequence = poblacion[i].sequence_;
    distance = 0; 
    //Calculate distance for each ciudad1 - ciudad2
    for(int i = 0; i < sequence.size()-1;++i)
    {
      distance += euclidea(ciudades.at(sequence.at(i)),
			   ciudades.at(sequence.at(i+1))); 
    }
 
    //Calculate distance for ciudadn -> ciudad1
    distance += euclidea(ciudades.at(sequence.at(sequence.size()-1)),
			  ciudades.at(sequence.at(0)));

    poblacion.at(i).cost_ = distance;
  }
}


double get_best_solution(const vector<gen>& population)
{
  double result = numeric_limits<double>::max();
  for(unsigned i = 0; i < population.size(); ++i)
  {
    //cout << "Elemento " << i << " coste -> " << population.at(i).cost_ << endl;
    if(population.at(i).cost_ < result)
      result = population.at(i).cost_; 
  }

  return result;
}

//FALTA ADAPTAR ESTA FUNCION AL CODIGO
vector<pareja> selectParents(const vector<gen>& genes, int num_parejas){
    vector<pareja> parejas; //Aqui dentro va el coste de cada ciudad. 
    vector<int> seleccionado;
    float *probabilidades = new float[genes.size()];
    
    //Calcular probabilidades de cada ciudad.
    float total = 0; 
    for(unsigned i = 0; i < genes.size(); ++i)
        total += genes.at(i).cost_;
    
    cout << "Coste total -> " << total << endl;  
    //Calcular la probabilidad de cada ciudad. 
    float suma = 0;
    for(unsigned i = 0; i < genes.size(); ++i)
    {
        probabilidades[i] = genes.at(i).cost_/total;
        cout << "Probabilidad de " << i << " -> " << probabilidades[i] << endl;
        suma+=probabilidades[i];
    }   
    
    //Generar numero aleatorio para seleccionar elemento
    int elemento = 0;
    float dado, acumulado;
    bool bandera =false;
    for(int i = 0; i < num_parejas*2; ++i) //Cada pareja tiene dos elementos. 
    {
        //Generar numero aleatorio para seleccionar elemento
        dado = (float)rand()/RAND_MAX;
        elemento = 0;
        acumulado = probabilidades[elemento];
        bandera = false;
        while(!bandera)
        {
            if(dado < acumulado)
            {
                bandera = true;
                seleccionado.push_back(elemento);
                cout << "Dado -> " << dado << " seleccionado " << seleccionado.at(i) << endl;
                cout << RAND_MAX << endl;
            }
            else
            {
                elemento++;
                acumulado+=probabilidades[elemento];
                
            }
        }
    }
    
    //Agrupamos en parejas los elementos seleccionados.
    for(int i = 0; i < num_parejas*2; i+=2)
    {
        cout << "Pareja -> " << seleccionado[i] << "," << seleccionado[i+1] << endl;
        parejas.push_back(pareja(seleccionado[i], seleccionado[i+1]));
    }
    
    delete probabilidades;
    return parejas;    
}


/***
 population_size -> Tamaño de la población
 population -> vector con los candidatos (posibles soluciones)
 condicion de parada -> 100 iteraciones
***/
int main(){
  string nombre = "kroA100.tsp";
  vector<ciudad> nodos = lectura_mapa(nombre);
  int population_size = 10, s_best; //, iteraciones = 0; //Numero de soluciones.
  vector<gen> population = generar_poblacion(population_size, nodos.size());
  evaluate_population(nodos, population);
  s_best = get_best_solution(population);
  cout << s_best << endl;
  
  int iteraciones = 0;
  while(iteraciones < 1) //Condicion de parada
  {
    selectParents(population, population_size);
    ++iteraciones;
  }
}
