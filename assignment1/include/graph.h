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

//Filepath is provided, txt file is converted into Graph as per algorithm selected.
bool read_graph(ifstream& file, string algorithm, GraphInput& input);

#endif