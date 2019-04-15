#include "Prim.hpp"

using namespace std;

int Prim::select(const list<int>& C, int *d)
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

void Prim::update(int *c, int *d, const list<int>& C, int k, int **p)
{
  for(auto j = C.begin(); j != C.end(); ++j) 
  {
    if(p[k][*j] < d[*j])
    {
      c[*j] = k;
      d[*j] = p[k][*j];
    }
  }
}

Prim::solution Prim::algPrim(int **p, int n){
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
    //cout << "vertice -> " << k << endl;
    C.remove(k); 
    S.aristas.push_back(make_pair(c[k],k));
    S.coste_total+=p[c[k]][k]; 
    update(c,d,C,k,p); 
  }

  return S;
}


