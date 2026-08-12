#include "../include/betweenness.h"

#include <queue>
#include <stack>

using namespace std;

vector<double> BetweennessCentrality::compute(const CSR &csr)
{
    int V = csr.vertices;

    // Final BC value of every vertex
    vector<double> BC(V, 0.0);

    // Run Brandes from every source
    for (int source = 0; source < V; source++)
    {
        // predecessor list
        vector<vector<int>> pred(V);

        // number of shortest paths
        vector<double> sigma(V, 0.0);

        // shortest distance
        vector<int> dist(V, -1);

        // dependency (used later)
        vector<double> delta(V, 0.0);

        // BFS queue
        queue<int> Q;

        // Stores BFS order
        stack<int> S;

        //--------------------------------------------------
        // Initialization
        //--------------------------------------------------

        sigma[source] = 1.0;
        dist[source] = 0;

        Q.push(source);

        //--------------------------------------------------
        // BFS
        //--------------------------------------------------

        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();

            S.push(u);

            int start = csr.row_ptr[u];
            int end = csr.row_ptr[u + 1];

            // Visit every neighbour of u
            for (int i = start; i < end; i++)
            {
                int v = csr.col_idx[i];

                //------------------------------------------
                // First time visiting v
                //------------------------------------------

                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    Q.push(v);
                }

                //------------------------------------------
                // Is (u,v) on a shortest path?
                //------------------------------------------

                if (dist[v] == dist[u] + 1)
                {
                    sigma[v] += sigma[u];
                    pred[v].push_back(u);
                }
            }
        }

        //--------------------------------------------------
        // Dependency accumulation comes here
        //--------------------------------------------------
       while(!S.empty())
        {
            int w = S.top();
            S.pop();

            // Give dependency to predecessors
            for(int v : pred[w])
            {
                delta[v] += (sigma[v] / sigma[w]) * (1.0 + delta[w]);
            }

            // Do not count the source vertex
            if(w != source)
            {
                BC[w] += delta[w];
            }
        }
        }
        return BC;
    }
    
