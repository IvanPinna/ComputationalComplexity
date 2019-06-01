#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std; 

vector<gen> replace(vector<gen> population, vector<gen> hijos)
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
    resultado.erase(resultado.begin()+(dado-1));
  }

  return resultado;
}

int main(int argc, char *argv[]){
    vector<int> padre, madre;
    gen p(padre), m(madre);

    int vp[100] = {42,82,74,34,9,84,60,68,28,56,92,79,78,27,93,85,94,
		   49,41,0,90,30,47,87,5,57,52,97,40,25,80,88,7,12,4,54,
		   33,8,15,66,32,43,1,19,62,45,58,96,81,13,53,10,67,17,2,
		   91,95,72,71,37,50,48,22,44,86,76,6,99,51,59,26,20,11,23,
		   14,38,55,61,31,64,18,21,69,3,98,24,36,75,39,16,46,77,83,
		   89,65,35,73,29,63,70};

    int vm[100] = {77,85,62,86,46,84,24,61,16,32,94,79,60,39,17,0,21,48,90,
		   29,22,14,75,35,44,76,34,80,12,26,49,4,30,33,15,5,58,56,
		   55,67,8,88,40,28,98,43,82,27,64,96,74,2,3,37,47,91,11,45,
		   10,95,71,54,41,72,25,92,50,6,23,19,63,68,73,87,42,20,59,
		   93,13,31,83,53,7,65,89,38,18,78,57,51,9,97,70,66,69,52,36,
		   81,1,99};

    for(int  i = 0; i < 100; ++i)
    {
      p.push_back(vp[i]);
      m.push_back(vm[i]);
    }
				      
}
