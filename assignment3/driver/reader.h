#ifndef READER_H
#define READER_H

#include<fstream>
#include<vector>
#include "../include/csr.h"

using namespace std;

struct GDInput
{
    int degree;
    vector<double>coefficients;
    double initial_x;
    double learning_rate;
    double tolerance;
    int max_iterations;
};

bool read_gd(ifstream&file,GDInput&input);

bool read_maxflow(ifstream&file,vector<vector<Edge>>&graph,int&source,int&sink);

#endif
