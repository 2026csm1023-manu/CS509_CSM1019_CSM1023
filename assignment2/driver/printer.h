#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

void print_triangle_count(int total_triangles,const vector<tuple<int, int, int>>& triangles,double execution_time,string output_file,bool print_triangles);

void print_betweenness_centrality(const vector<double>& centrality,double execution_time,string output_file);

void print_connected_components(int number_of_components,const vector<int>& component,double execution_time,string output_file);

#endif