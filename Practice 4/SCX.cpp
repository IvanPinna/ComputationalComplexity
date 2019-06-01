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

gen SCX(const gen& padre, const gen& madre)
{
    int c_padre = 0, c_madre = 0;   //Contadores para padre y madre. 
    gen hijo;
    vector<int>::iterator it_p, it_m;
    
    hijo.push_back(padre.at(0));
    ++c_padre;
    while(hijo.size() < padre.size())
    {
        it_p = find(hijo.begin(), hijo.end(), padre.at(c_padre));
        it_m = find(hijo.begin(), hijo.end(), madre.at(c_madre));

	//cout << "Iterador del padre " << *it_p << endl;
	//cout << "Iterador de la madre " << *it_m << endl;
	//cout << "Ultimo elemento del hijo " << *hijo.end() << endl;
	
        if(it_p == hijo.sequence_.end() and it_m == hijo.sequence_.end())
        {
            //Buscar el más cercano al que ya hay. 
            cout << "shit, ambos no están en el hijo" << endl;
	    cout << abs(hijo.at(hijo.size()-1) - padre.at(c_padre)) << " (" << padre.at(c_padre) << ") "
		 << " < "
		 << abs(hijo.at(hijo.size()-1) - madre.at(c_madre)) << " (" << madre.at(c_madre) << ") " << endl;

	    if(abs(hijo.at(hijo.size()-1) - padre.at(c_padre))  < abs(hijo.at(hijo.size()-1) - madre.at(c_madre)))
            {
                hijo.push_back(padre.at(c_padre));
                c_padre++;
            }
            else
            {
                hijo.push_back(madre.at(c_madre));
                c_madre++;
            }
        }
        else
        {
            if(it_p == hijo.sequence_.end())
            {
                cout << "Insertando elemento del padre" << endl;
                hijo.push_back(padre.at(c_padre));
                c_padre++;
		c_madre++; //Porque significa que la madre ya esta en el hijo. 
                
            }
	    
            if(it_m == hijo.sequence_.end())
            {
                cout << "Insertando elemento de la madre" << endl;
                hijo.push_back(madre.at(c_madre));
                c_madre++;
		c_padre++; //Porque significa que el padre ya esta en hijo. 
            }

	    //Padre y madre ya están en el hijo, se avanza. 
	    if(it_p == hijo.sequence_.end() and it_m == hijo.end())
	    {
	      c_madre++;
	      c_padre++;
	    }
	}
    }
    
    for(int i = 0; i < hijo.size(); ++i)
        cout << hijo.at(i) << endl;
    
    return hijo;    
}


int main(int argc, char *argv[]){
    vector<int> padre, madre;
    gen p(padre), m(madre);
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
    
    
    SCX(padre, madre);
    
}
