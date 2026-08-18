#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include<vector>

using namespace std;

struct GDResult
{
    double final_x;
    double final_fx;
    int iterations;
    bool converged;
};

struct GDInput;

GDResult gradient_descent(const GDInput&input);

#endif
