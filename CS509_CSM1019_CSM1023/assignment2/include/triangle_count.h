//declaration
#ifndef TRIANGLE_COUNT_H
#define TRIANGLE_COUNT_H
//inclue csr because arg using it
#include "csr.h"
//include files
#include <vector>
//tuple for generic structure 
#include <tuple>
using namespace std;

class triangleCount
{
  public:
  static vector<tuple<int,int,int>> countTriangles(const CSR &csr);  
  private:
    static bool hasEdge(const CSR &csr,int u,int v);
};

#endif