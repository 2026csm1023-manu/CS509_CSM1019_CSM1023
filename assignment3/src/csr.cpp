#include "../include/csr.h"

CSR make_csr(const vector<vector<Edge>>& graph)
{
    CSR csr;

    csr.vertices = graph.size();

    // First vertex starts at index 0
    csr.row_ptr.push_back(0);

    for(int i = 0; i < graph.size(); i++)
    {
        for(int j = 0; j < graph[i].size(); j++)
        {
            csr.col_idx.push_back(graph[i][j].neighbour);
            csr.values.push_back(graph[i][j].weight);
        }

        // End position of current vertex
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}