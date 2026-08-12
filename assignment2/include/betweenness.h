#ifndef BETWEENNESS_H
#define BETWEENNESS_H

#include <vector>
#include "csr.h"

using namespace std;

class BetweennessCentrality
{
public:
    // Returns the BC score of every vertex
    static vector<double> compute(const CSR &csr);
};

#endif