#ifndef PRINTER_H
#define PRINTER_H

#include<string>
#include "reader.h"
#include "../include/gradient_descent.h"
#include "../include/maxflow.h"

using namespace std;

void print_gd(const GDResult&result,const GDInput&input,double time,string output_file);

void print_maxflow(const MaxflowResult&result,int source,int sink,double time,string output_file);

#endif
