#include "printer.h"

#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

void print_triangle_count(int total_triangles,const vector<tuple<int, int, int>>& triangles,double execution_time,string output_file,bool print_triangles)
{
    ofstream out(output_file);

    out << "Algorithm: Triangle Counting\n";
    out << "Total triangles: " << total_triangles << "\n";

    if(print_triangles)
    {
        out << "Triangles found:\n";

        for(auto &t : triangles)
        {
            out << "("<< get<0>(t) << ", "<< get<1>(t) << ", "<< get<2>(t)<< ")\n";
        }
    }

    out << "Execution time: "<< execution_time<< " ms\n";

    out.close();
}


void print_betweenness_centrality(const vector<double>& centrality,double execution_time,string output_file)
{
    ofstream out(output_file);

    out << "Algorithm: Betweenness Centrality\n";
    out << "Vertex Centrality\n";

    out << fixed << setprecision(2);

    for(int i = 0; i < centrality.size(); i++)
    {
        out << i << " "<< centrality[i]<< "\n";
    }

    out << "Execution time: "<< execution_time<< " ms\n";

    out.close();
}


void print_connected_components(int number_of_components,const vector<int>& component,double execution_time,string output_file)
{
    ofstream out(output_file);

    out << "Algorithm: Connected Components\n";
    out << "Number of components: "<< number_of_components<< "\n";

    out << "Vertex Component\n";

    for(int i = 0; i < component.size(); i++)
    {
        out << i << " "<< component[i]<< "\n";
    }

    out << "Execution time: "<< execution_time << " ms\n";

    out.close();
}