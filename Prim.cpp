#include <iostream>
#include <vector>
#include <list>

#define INF 2147483647

using namespace std;

struct solution{
  vector<pair<int,int>> aristas;
  int coste_total = 0;
};

int select(const list<int>& C, int *d)
{
  int k, v = INF;
  k = 0;
 
  for(auto j = C.begin(); j != C.end(); ++j)
  {
    if(d[*j] < v)
    {
      v = d[*j];
      k = *j;
    }
 }

 return k;
}

void update(int *c, int *d, const list<int>& C, int k, int **p)
{
  for(auto j = C.begin(); j != C.end(); ++j) // j = 0; j < C.size(); ++j)
  {
    if(p[k][*j] < d[*j])
    {
      c[*j] = k;
      d[*j] = p[k][*j];
    }
  }
}

solution Prim(int **p, int n){
  list<int> C;
  solution S;
  int *c, *d;
  c = new int[n]; d = new int[n];
  c[0] = -1; d[0] = 0; //Initialize first position
  for(int j = 1; j < n; ++j)
  {
    C.push_back(j);
    c[j] = 0; //First node it's 0
    d[j] = p[0][j];
  }
  
  int k;
  while(!C.empty())
  {
    k = select(C,d);
    cout << "vertice -> " << k << endl;
    C.remove(k); //Comprueba esta parte
    S.aristas.push_back(make_pair(c[k],k));
    S.coste_total+=p[c[k]][k]; //Volcamos el coste de la arista
    update(c,d,C,k,p); //Importante como se pasan los parametros

    /*
    cout << "visualizando c " << endl;
    for(int i = 0; i < 7; ++i)
      cout << " " << c[i] << " ";
    cout << endl;
    cout << "visualizando d " << endl;
    for(int i = 0; i < 7; ++i)
      cout << " " << d[i] << " ";
    cout << endl;
    */
  }

  return S;
}

int main(){
  int rows, cols;
  rows = cols = 7;
  int matrix[rows][cols] = {{  0,   1, INF,INF,  INF, INF, INF},
			    {  1,   0,   8,  8,    8, INF, INF},
			    {INF,   8,   0,  7,  INF, INF, INF},
			    {INF,   8,   7,  0,    6,   9, INF},
			    {INF,   8, INF,  6,    0,   9, INF},
			    {INF, INF, INF,  9,    9,   0,   4},
			    {INF, INF, INF, INF, INF,   4,   0}}; //Falta asignarle valores

  int** subMatrix = new int*[rows];
  for(int i = 0; i < cols; ++i)
    subMatrix[i] = new int[cols];

  //Copy values of principal matrix
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      subMatrix[i][j] = matrix[i][j];

  solution S = Prim(subMatrix, rows);

  cout << "Aristas Seleccionadas" << endl;
  for(int i = 0; i < S.aristas.size(); ++i)
  {
    cout << "(" << S.aristas[i].first << "," << S.aristas[i].second << ")" << endl;
  }
  cout << "Coste total: " << S.coste_total << endl;
  //deleting dinamic subMatrix
  for(int i = 0; i < cols;++i)
    delete[] subMatrix[i];
  delete[] subMatrix;
}
