#include "../include/dfs.h"
#include <stack>

vector<int> dfs(const CSR& csr, int source)
{
    int n = csr.row_ptr.size() - 1;

    vector<int> visited(n, 0);
    vector<int> result;
    stack<int> st;

    st.push(source);

    while(!st.empty())
    {
        int u = st.top();
        st.pop();

        if(visited[u] == 1)
            continue;

        visited[u] = 1;
        result.push_back(u);

        for(int i = csr.row_ptr[u + 1] - 1; i >= csr.row_ptr[u]; i--)
        {
            int v = csr.col_idx[i];

            if(visited[v] == 0)
            {
                st.push(v);
            }
        }
    }

    return result;
}