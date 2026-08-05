#include "../include/printer.h"

#include <fstream>
#include <climits>

using namespace std;

void print_bfs(int source, const BFSResult& result,double execution_time, string output_file)
{
    ofstream out(output_file);

    out << "Algorithm: BFS\n";
    out << "Source: " << source << "\n";
    out << "Traversal: ";

    //print all traversal value
    for(int v: result.traversal)
    {
        out<< v << " ";
    }

    out<<"\nDistances:\n";

    for(int i=0; i<result.distance.size(); i++)
    {
        out << i << " ";

        if(result.distance[i] == -1)
            out << "INF\n";
        else
            out << result.distance[i] << "\n";
    }

    out<<"Execution time: " << execution_time << " ms\n";

    out.close();
}


void print_dfs(int source, const vector<int>& result,double execution_time, string output_file)
{
    ofstream out(output_file);

    out << "Algorithm: DFS\n";
    out << "Source: " << source << "\n";
    out << "Traversal: ";

    for(int v : result)
    {
        out<<v << " ";
    }

    out << "\n";
    out << "Execution time: " << execution_time << " ms\n";

    out.close();
}


void print_sssp(int source, const vector<int>& distance,double execution_time, string output_file)
{
    ofstream out(output_file);

    out << "Algorithm: SSSP\n";
    out << "Source: " << source << "\n";
    out << "Vertex Distance\n";

    for(int i=0; i<distance.size(); i++)
    {
        out<< i << " ";

        if(distance[i]== INT_MAX)
            out<< "INF\n";
        else
            out<< distance[i] << "\n";
    }

    out << "Execution time: " << execution_time << " ms\n";

    out.close();
}