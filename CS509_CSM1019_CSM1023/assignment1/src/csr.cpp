#include "../include/csr.h"

CSR make_csr(const vector<vector<Edge>>& graph)
{
    CSR csr;

    //First row always starts at position 0
    csr.row_ptr.push_back(0);

    //Go through every vertex
    for(int i = 0; i < graph.size(); i++)
    {
        //Go through all neighbours of vertex i
        for(int j = 0; j < graph[i].size(); j++)
        {
            csr.col_idx.push_back(graph[i][j].neighbour);
            csr.values.push_back(graph[i][j].weight);
        }

        // Store where the next vertex will start
        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}
