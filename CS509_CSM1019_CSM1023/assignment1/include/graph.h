#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <string>
#include "csr.h"

using namespace std;

struct GraphInput
{
    vector<vector<Edge>> graph;
    int source;
};

// Reads graph + SOURCE from an already opened file
bool read_graph(ifstream& file, string algorithm, GraphInput& input);

#endif