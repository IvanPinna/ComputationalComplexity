#include <iostream>
#include <vector>
#include <list>

#define INF 2147483647

using namespace std;

int main(){
  int rows, cols;
  rows = cols = 8;
  int oblig = 4;
  int nodes = 8;
  int matrix[rows][cols] = {{   0,   4,   3, INF,  1, INF, INF, INF},
			    {   4,   0, INF,   5,INF,   1, INF, INF},
			    {   3, INF,   0,   6,  1, INF, INF, INF},
			    { INF,  5,   6,   0, INF, INF, INF,   1},
			    {   1,INF,   1, INF,   0,   2,   3, INF},
			    { INF,  1, INF, INF,   2,   0, INF,   1},
			    { INF,INF, INF, INF,   3, INF,   0,   2},
			    { INF,INF, INF,   1, INF,   1,   2,   0}};
			    
  //Suppose combination 0100
  int contador = 0;
  //                0      1      2     3     4      5      6     7
  bool opt[8] = {true, false, false, true ,true, false, false, true};
  for(int i = 0; i < nodes; ++i)
    if(opt[i])
      contador++;

  //Create submatrix
  int** subMatrix = new int*[rows];
  for(int i = 0; i < nodes; ++i)
    subMatrix[i] = new int[cols];

  //Insert values into submatrix for Prim
  int s_x = 0, s_y = 0;
  for(int i = 0; i < nodes; ++i)
  {
    s_y = 0;
    for(int j = 0; j < nodes; ++j)
    {
      if(opt[i] and opt[j])
      {
	subMatrix[s_x][s_y] = matrix[i][j];
	++s_y;
      }
    }
    if(opt[i]) //Se ha escrito
      ++s_x;
  }
  
  for(int i = 0; i < contador; ++i)
  {
    for(int j = 0; j < contador; ++j)
      cout << subMatrix[i][j] << " ";
    cout << " " << endl;
  }
  //deleting dinamic subMatrix
  for(int i = 0; i < cols;++i)
    delete[] subMatrix[i];
  delete[] subMatrix;
}
