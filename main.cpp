#include <iostream>
#include <math.h>
#include "Prim.hpp"

using namespace std;

/* 
   Devuelve la siguiente permutacion de una cadena binaria. La cadena 
   binaria se implementa como un vector de booleanos llamado 'array'.
*/
void permutation(bool* array, int tam)
{
  bool bandera = false;
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
}

int main(){
  Prim objeto;
  int rows, cols;
  int allnodes = 4; //Numero de nodos
  int opcionales = 2;
  int matrix[allnodes][allnodes] = {{  0, 1, INF, 5},
			    {  1, 0,   4, 5},
			    {INF, 4,   0, 2},
			    {  5, 5,   2, 0}};

  //Bool array to determine which allnodes are selected
  bool *selected = new bool[allnodes];
  int activenodes = 0;
  for(int i = 2; i < allnodes; ++i){
    selected[i] = true; //{false, false, true, true};
    selected[i-2] = false; 
  }

  //Create submatrix
  int** subMatrix = new int*[allnodes];
  for(int i = 0; i < allnodes; ++i)
    subMatrix[i] = new int[allnodes];
  
  //Si declaramos espacio de mas no hace falta sobreescribir.
  int limite = pow(2,opcionales)-1;
  int contador = 0;
  int costeMin = INF;
  while(contador <= limite) //La primera vuelta es sin nodos opcionales
  {
    //Insert values into submatrix for Prim
    int s_x = 0, s_y = 0;
    for(int i = 0; i < allnodes; ++i)
    {
      s_y = 0;
      for(int j = 0; j < allnodes; ++j)
      {
	if(selected[i] and selected[j])
	{
	  subMatrix[s_x][s_y] = matrix[i][j];
	  ++s_y;
	}
      }
      if(selected[i]) //Se ha escrito
	++s_x;
    }

    activenodes = 0;
    for(int i = 0; i < allnodes; ++i)
      if(selected[i])
	++activenodes;

    // allnodes se usa para conocer el tam. de la matriz.
    Prim::solution S = objeto.algPrim(subMatrix, activenodes);
    if(S.coste_total < costeMin)
      costeMin = S.coste_total;
    
    //Generamos la siguiente permutacion
    permutation(selected, opcionales);
    
    //PostProcesado de la informacion. 
    /*cout << "Aristas Seleccionadas" << endl;
    for(int i = 0; i < S.aristas.size(); ++i)
    {
      cout << "(" << S.aristas[i].first << "," << S.aristas[i].second
	   << ")" << endl;
	   }*/
    cout << "Coste total: " << S.coste_total << endl;

    ++contador;
  }

  cout << "Coste minimo: " << costeMin << endl;
  
  //deleting dinamic subMatrix
  for(int i = 0; i < allnodes;++i)
    delete[] subMatrix[i];
  delete[] subMatrix;
}
