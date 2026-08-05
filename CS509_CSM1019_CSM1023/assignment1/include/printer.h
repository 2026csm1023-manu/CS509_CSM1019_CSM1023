#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <string>
#include "bfs.h"

using namespace std;

void print_bfs(int source, const BFSResult& result, double execution_time, string output_file);

void print_dfs(int source, const vector<int>& result, double execution_time, string output_file);

void print_sssp(int source, const vector<int>& distance,double execution_time, string output_file);

#endif