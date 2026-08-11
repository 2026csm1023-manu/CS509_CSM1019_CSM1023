#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

#include <vector>
#include "csr.h"

using namespace std;

class ConnectedComponents
{
public:
    static int findComponents(const CSR &csr, vector<int> &component);

private:
    static void dfs(int u,
                    const CSR &csr,
                    vector<bool> &visited,
                    vector<int> &component,
                    int componentID);
};

#endif