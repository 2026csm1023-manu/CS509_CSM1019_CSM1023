#ifndef MAXFLOW_H
#define MAXFLOW_H

#include<vector>
#include "csr.h"

using namespace std;

struct CutEdge
{
    int u;
    int v;
    int capacity;
};

struct MaxflowResult
{
    int maximum_flow;
    int minimum_cut_capacity;
    vector<int>source_side;
    vector<int>sink_side;
    vector<CutEdge>cut_edges;
};

MaxflowResult maxflow(const CSR&csr,int source,int sink);

#endif
