#ifndef DFS_H
#define DFS_H

#include <vector>
#include "csr.h"

using namespace std;

vector<int> dfs(const CSR& csr, int source);

#endif