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
    
  int size() const 
  {
    return sequence_.size();
  }
    
  int at(int index) const 
  {
    return sequence_.at(index);
  }
    
  void push_back(int element)
  {
    sequence_.push_back(element);
  }
    
  vector<int>::iterator begin()
  {
    return sequence_.begin();
  }
    
  vector<int>::iterator end() 
  {
    return sequence_.end();
  }

  int &operator[](int index)
  {
    return sequence_[index];
  }

  void show() const{
    for(int i = 0; i < sequence_.size();++i)
      cout << i << "->" << sequence_.at(i) << endl;
    cout << "" << endl;
  }
};

struct pareja{
    int x_, y_;
    
    pareja(int x, int y):x_(x), y_(y)
    {}
    
    pareja()
    {}
};

//Se encarga de comprobar que un gen tenga todos los alelos correctos. 
void tester(const gen& p)
{
  int resultado = 0; 
  for(int i = 0; i < p.size(); ++i)
  {
    for(int j = 0; j < p.size(); ++j)
      if(p.at(j) ==i)
	resultado+=1;
  }

  if(resultado == p.size())
    cout << "True" << endl;
  else
    cout << "False" << endl;
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
  //gen sol(solucion);
  //tester(sol);
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


vector<pareja> selectParents(const vector<gen>& genes, int num_parejas){
    vector<pareja> parejas; //Aqui dentro va el coste de cada ciudad. 
    vector<int> seleccionado;
    float *probabilidades = new float[genes.size()];
    
    //Calcular probabilidades de cada ciudad.
    float total = 0; 
    for(unsigned i = 0; i < genes.size(); ++i)
        total += genes.at(i).cost_;
    
    //cout << "Coste total -> " << total << endl;  
    //Calcular la probabilidad de cada ciudad. 
    float suma = 0;
    for(unsigned i = 0; i < genes.size(); ++i)
    {
        probabilidades[i] = genes.at(i).cost_/total;
        //cout << "Probabilidad de " << i << " -> " << probabilidades[i] << endl;
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
      parejas.push_back(pareja(seleccionado[i], seleccionado[i+1]));
    }
    
    delete probabilidades;
    return parejas;    
}

gen SCX(const gen& padre, const gen& madre, const vector<ciudad>& ciudades)
{
    int c_padre = 0, c_madre = 0;   //Contadores para padre y madre. 
    gen hijo;
    vector<int>::iterator it_p, it_m;
    
    hijo.push_back(padre.at(0));
    ++c_padre;
    int iter = 0;
    bool bandera;
    while(hijo.size() < padre.size())
    {
      ++iter;
        it_p = find(hijo.begin(), hijo.end(), padre.at(c_padre));
        it_m = find(hijo.begin(), hijo.end(), madre.at(c_madre));

        if(it_p == hijo.sequence_.end() and it_m == hijo.sequence_.end())
        {
	  //Buscamos el que esta más cerca. 
	  if(euclidea(ciudades.at(hijo.at(hijo.size()-1)), ciudades.at(padre.at(c_padre))) <
	     euclidea(ciudades.at(hijo.at(hijo.size()-1)), ciudades.at(madre.at(c_madre))))
          {
	    //cout << "Ambos no estan, insertando padre ->" << padre.at(c_padre) << endl; 
	    hijo.push_back(padre.at(c_padre));
	    if(c_padre < 99)
	      c_padre++;
	  } 
	  else
          {
	    //cout << "Ambos no estan, insertando madre ->" << madre.at(c_madre) << endl;
	    hijo.push_back(madre.at(c_madre));
	    if(c_madre < 99)
	      c_madre++;
	  }
	 
        }
        else
        {
	  bandera = false; 
            if(it_p == hijo.sequence_.end())
            {
	      //cout << "Insertando elemento del padre ->  " << padre.at(c_padre) << endl;
	      hijo.push_back(padre.at(c_padre));
	      if(c_madre < 99)
		c_madre++;
	      if(c_padre < 99)
		c_padre++;
	      bandera = true;
	      
            }
	    
            if(it_m == hijo.sequence_.end() and !bandera)
	    {
	      //cout << "Insertando elemento de la madre -> " << madre.at(c_madre) << endl;
	      hijo.push_back(madre.at(c_madre));
	      if(c_madre < 99)
		c_madre++;
	      if(c_padre < 99)
		c_padre++;
	      bandera = true;
            }
	    
	    //Padre y madre ya están en el hijo, se avanza. 
	    if(it_p != hijo.sequence_.end() and it_m != hijo.end() and !bandera)
	    {
	      cout << "Contador del padre " << c_padre << endl;
	      cout << "Contador de la madre " << c_madre << endl; 
	      cout << "Hijo" << endl;
	      hijo.show();
	      cout << "Padre" << endl;
	      padre.show();
	      cout << "Madre" << endl;
	      madre.show();
	      throw std::invalid_argument("entrando en padre y madre ya estan" );
	      if(c_madre < 99)
		c_madre++;
	      if(c_padre < 99)
		c_padre++;
	      bandera = true;
	    }
	}
    }

    /*
    for(int i = 0; i < hijo.size(); ++i)
        cout << hijo.at(i) << endl;
    */
    return hijo;    
}
    

gen splitter(const gen& padre, const gen& madre)
{
  int contador = 0;
  gen hijo;
  for(int i = 0; i < padre.size()/2;++i) //Volcamos mitad del padre.
    hijo.push_back(padre.at(i));

  while(hijo.size() < padre.size())
  {
    if(find(hijo.begin(), hijo.end(), madre.at(contador)) == hijo.end())
      hijo.push_back(madre.at(contador));
   
    contador++;
  }
  
  return hijo;
}

/*
  Candidato -> Gen que va a sufrir la mutación 
  Probabilidad -> Probabilidad de que sufra la mutacion.
  Porcentaje -> En caso de que sufra la mutación, cuantos elementos 
                se van a ver afectados.
 */
void mutation(gen& candidato, float probabilidad, float porcentaje)
{
  int  posicion1, posicion2, aux, elementos;//0.20;
  float dado = (float)rand()/RAND_MAX;
  
  elementos = candidato.size()*porcentaje;
  if(dado < probabilidad)
  {
    //Calcular el porcentaje max de candidatos a mutar. 
   for(int i = 0; i < elementos; ++i)
   {
    //Generar un aleatorio entre 0 y candidato.size()
     posicion1 = rand() % (candidato.size());
     posicion2 = rand() % (candidato.size());
     aux = candidato[posicion1];
     candidato[posicion1] = candidato.at(posicion2);
     candidato[posicion2] = aux;
   }
  }
}

vector<gen> replace(const vector<gen>& population, const vector<gen>& hijos)
{
  //Volcar todos los elementos en el resultado
  vector<gen> resultado(population);
  int dado;
  for(int i = 0; i < hijos.size(); ++i)
    resultado.push_back(hijos.at(i));
  
  //Eliminar elementos hasta que tenga el tamaño de la población
  while(resultado.size() > population.size())
  {
    dado = rand()%resultado.size();
    resultado.erase(resultado.begin()+(dado));
  }

  //cout << "Tamaño población " << resultado.size() << endl;
  return resultado;
}

vector<gen> replace_elitist(const vector<gen>& population, const vector<gen>& hijos)
{
  //Volcar todos los elementos en el resultado
  vector<gen> resultado(population);
  int dado;
  for(int i = 0; i < hijos.size(); ++i)
    resultado.push_back(hijos.at(i));

  //Eliminar elementos hasta que tenga el tamaño de la población
  while(resultado.size() > population.size())
  {
    dado = rand()%resultado.size();
    resultado.erase(resultado.begin()+(dado));
  }
  
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
  int population_size = 1000, s_best; //, iteraciones = 0; //Numero de soluciones.
  vector<gen> population = generar_poblacion(population_size, nodos.size());
  evaluate_population(nodos, population);
  s_best = get_best_solution(population);
  //cout << s_best << endl;
  
  int iteraciones = 0;
  vector<pareja> parejas;
  vector<gen> hijos;
  gen hijo;
  while(iteraciones < 1) //Condicion de parada
  {
    hijos.clear(); //Resetear hijos
    parejas = selectParents(population, population_size); 
    for(unsigned i = 0; i < parejas.size();++i) //Para generar 50% de hijos
    {
      hijo = SCX(population.at(parejas.at(i).x_),
		 population.at(parejas.at(i).y_), nodos);
      tester(hijo);
      mutation(hijo, 0.9, 0.8);
      hijos.push_back(hijo); //Añadimos el hijo a la poblacion de hijos. 
    }

    population = replace(population, hijos);
    //Explicar por qué evaluas después. 
    evaluate_population(nodos, population); //Evalúa cada hijo. 
    s_best = get_best_solution(population);
    ++iteraciones;
    cout << "iteraciones -> " << iteraciones << endl;
  }
  cout << "iteraciones -> " << iteraciones << endl;

  cout << "s_best = " << s_best << endl;
}
