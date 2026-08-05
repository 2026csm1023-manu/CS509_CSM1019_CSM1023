#include "../include/bfs.h"
#include <queue>

BFSResult bfs(const CSR& csr, int source)
{
    int n = csr.row_ptr.size() - 1;

    vector<int> visited(n, 0);
    BFSResult result;

    result.distance.resize(n, -1);

    queue<int> q;

    q.push(source);
    visited[source] = 1;
    result.distance[source] = 0;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        result.traversal.push_back(u);

        for(int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; i++)
        {
            int v = csr.col_idx[i];

            if(visited[v] == 0)
            {
                visited[v] = 1;
                result.distance[v] = result.distance[u] + 1;
                q.push(v);
            }
        }
    }

    return result;
}