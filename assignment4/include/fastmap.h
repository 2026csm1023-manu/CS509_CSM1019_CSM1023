#ifndef FASTMAP_H
#define FASTMAP_H

#include <vector>
#include <utility>

using namespace std;

struct FastMapInput
{
    int N;
    int K;
    vector<vector<double>> distances;
};

struct FastMapResult
{
    vector<vector<double>> coordinates;
    vector<pair<int,int>> pivots;
};

FastMapResult fastmap(const FastMapInput& input);

#endif
