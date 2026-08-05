#ifndef CSR_H
#define CSR_H

#include <vector>
#include <utility>
using namespace std;

struct Edge
{
    int neighbour;
    int weight;
};

struct CSR
{
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

//adjacency list into CSR conversion function
//adjacency list is in pair of <neighbours, weight>
CSR make_csr(const vector<vector<Edge>>& adj_list);

#endif