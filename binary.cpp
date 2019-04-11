#include <iostream>
#include <math.h>

#define INF 2147483647

using namespace std;

int main(){
  int tam = 5;
  bool array[tam];
  for(int i = 0; i < tam; ++i)
    array[i] = false;

  int contador = 0;
  int limite = pow(2,tam) - 1;
  bool bandera;
  while(contador != limite)
  {
    bandera = false;
    for(int i = tam-1; i >= 0 && !bandera; --i)
    {
      if(array[i])
	array[i] = false;
      else
      {
	array[i] = true;
	bandera = true;
      }
    }

    //Visualizacion del array
    for(int i = 0; i < tam; ++i)
      cout << array[i];
    cout << " " << endl;

    ++contador;
  }
}

