#ifndef SSSP_H
#define SSSP_H

#include <vector>
#include "csr.h"

using namespace std;

vector<int> sssp(const CSR& csr, int source);

#endif