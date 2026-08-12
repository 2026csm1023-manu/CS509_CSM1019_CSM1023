#include "../include/triangle_count.h"

#include <algorithm>

using namespace std;

bool triangleCount::hasEdge(const CSR &csr, int u, int v)
{
    int start = csr.row_ptr[u];
    int end = csr.row_ptr[u + 1];

    return binary_search(
        csr.col_idx.begin() + start,
        csr.col_idx.begin() + end,
        v
    );
}

vector<tuple<int,int,int>> triangleCount::countTriangles(const CSR &csr)
{
    vector<tuple<int,int,int>> triangles;

    int V = csr.vertices;

    for(int u=0;u<V;u++)
    {
        int start = csr.row_ptr[u];
        int end   = csr.row_ptr[u+1];

        for(int i=start;i<end;i++)
        {
            int v = csr.col_idx[i];

            if(v<=u)
                continue;

            for(int j=i+1;j<end;j++)
            {
                int w = csr.col_idx[j];

                if(w<=v)
                    continue;

                if(hasEdge(csr,v,w))
                {
                    triangles.push_back({u,v,w});
                }
            }
        }
    }

    return triangles;
}