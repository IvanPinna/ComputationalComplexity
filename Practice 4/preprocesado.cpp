#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

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

int main(){
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

  while(!regex_search(str, endfile))
  {
    sregex_iterator it(str.begin(), str.end(), reg);

    id =  stoi((*it).str()); 
    x =  stoi((*(++it)).str());  
    y = stoi((*(++it)).str());

    ciudades.push_back(ciudad(id, x, y));
    ciudades.at(contador).imprimir();
    getline(fe, str);
    ++contador;
  }

  fe.close();
}
