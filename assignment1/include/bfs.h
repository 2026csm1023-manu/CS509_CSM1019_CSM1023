#ifndef BFS_H
#define BFS_H

#include <vector>
#include "csr.h"

using namespace std;

struct BFSResult
{
    vector<int> traversal;
    vector<int> distance;
};

BFSResult bfs(const CSR& csr, int source);

#endif