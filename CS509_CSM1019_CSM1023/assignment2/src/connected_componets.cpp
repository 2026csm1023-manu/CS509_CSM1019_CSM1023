#include "../include/connected_components.h"

using namespace std;

void ConnectedComponents::dfs(int u,
                              const CSR &csr,
                              vector<bool> &visited,
                              vector<int> &component,
                              int componentID)
{
    visited[u] = true;
    component[u] = componentID;

    int start = csr.row_ptr[u];
    int end = csr.row_ptr[u + 1];

    for(int i = start; i < end; i++)
    {
        int v = csr.col_idx[i];

        if(!visited[v])
        {
            dfs(v, csr, visited, component, componentID);
        }
    }
}

int ConnectedComponents::findComponents(const CSR &csr,
                                        vector<int> &component)
{
    int V = csr.vertices;

    vector<bool> visited(V, false);

    component.assign(V, -1);

    int componentCount = 0;

    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            dfs(i,
                csr,
                visited,
                component,
                componentCount);

            componentCount++;
        }
    }

    return componentCount;
}