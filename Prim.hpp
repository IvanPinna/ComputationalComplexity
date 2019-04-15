#include <vector>
#include <list> 
#include <iostream>

#define INF 2147483647

using namespace std;

class Prim{
public:
  struct solution{
    vector<pair<int,int>> aristas;
    int coste_total = 0;
  };

  Prim() {}
  int select(const list<int>& C, int *d);
  void update(int *c, int *d, const list<int>& C, int k, int **p);
  solution algPrim(int **p, int n);  
};
