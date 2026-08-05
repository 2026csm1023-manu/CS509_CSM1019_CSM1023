#include "../include/sssp.h"

#include <queue>
#include <climits>
#include <utility>
#include <functional>

vector<int> sssp(const CSR& csr, int source)
{
    int n = csr.row_ptr.size() - 1;

    vector<int> distance(n, INT_MAX);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    distance[source] = 0;
    pq.push({0, source});

    while(!pq.empty())
    {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(dist != distance[u])
            continue;

        for(int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; i++)
        {
            int v = csr.col_idx[i];
            int weight = csr.values[i];

            if(distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}