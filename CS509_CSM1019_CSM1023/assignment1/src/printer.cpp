#include "../include/printer.h"

#include <iostream>
#include <climits>

using namespace std;

void print_bfs(int source, const BFSResult& result, double execution_time)
{
    cout << "Algorithm: BFS\n";
    cout << "Source: " << source << "\n";
    cout << "Traversal: ";

    for(int v : result.traversal)
    {
        cout << v << " ";
    }

    cout << "\nDistances:\n";

    for(int i = 0; i < result.distance.size(); i++)
    {
        cout << i << " ";

        if(result.distance[i] == -1)
            cout << "INF\n";
        else
            cout << result.distance[i] << "\n";
    }

    cout << "Execution time: " << execution_time << " ms\n";
}


void print_dfs(int source, const vector<int>& result, double execution_time)
{
    cout << "Algorithm: DFS\n";
    cout << "Source: " << source << "\n";
    cout << "Traversal: ";

    for(int v : result)
    {
        cout << v << " ";
    }

    cout << "\n";
    cout << "Execution time: " << execution_time << " ms\n";
}


void print_sssp(int source, const vector<int>& distance, double execution_time)
{
    cout << "Algorithm: SSSP\n";
    cout << "Source: " << source << "\n";
    cout << "Vertex Distance\n";

    for(int i = 0; i < distance.size(); i++)
    {
        cout << i << " ";

        if(distance[i] == INT_MAX)
            cout << "INF\n";
        else
            cout << distance[i] << "\n";
    }

    cout << "Execution time: " << execution_time << " ms\n";
}