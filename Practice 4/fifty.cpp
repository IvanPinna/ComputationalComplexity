#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

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
}; 


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

  for(int i = 0; i < padre.size(); ++i)
    cout << hijo.at(i) << endl;
  return hijo;
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

    
    int resultado = 0;
    //Checkear que tiene todos los valores. 
    for(int i = 0; i < 100; ++i)
    {
      for(int j = 0; j < 100; ++j)
	if(i == vm[j])
	  resultado++;
    }
    cout << resultado << endl;

    for(int i = 0; i < 100; ++i)
    {
      padre.push_back(vp[i]);
      madre.push_back(vm[i]);
    }

    //Bien, el programa detecta el fallo. 
    /*
    madre.push_back(1);
    madre.push_back(3);
    madre.push_back(2);
    madre.push_back(4);
    madre.push_back(5);
    
    
    padre.push_back(5);
    padre.push_back(2);
    padre.push_back(1);
    padre.push_back(4);
    padre.push_back(3);
    */
    
    gen hijo = splitter(padre, madre);
    resultado = 0;
    for(int i = 0; i < 100; ++i)
    {
      for(int j = 0; j < 100; ++j)
	if(i == vm[j])
	  resultado++;
    }

    cout << "resultado " << resultado <<   endl;
}
