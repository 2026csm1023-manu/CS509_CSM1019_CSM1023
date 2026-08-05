#include "../include/graph.h"

#include <iostream>

using namespace std;

bool read_graph(ifstream& file, string algorithm, GraphInput& input)
{
    int V, E;

    file >> V >> E;

    if(file.fail() || V <= 0 || E < 0)
    {
        cout << "Error: Invalid test file\n";
        return false;
    }

    // Create adjacency list
    input.graph.resize(V);

    // Read adjacency list for every vertex
    for(int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        if(file.fail() || vertex < 0 || vertex >= V || degree < 0)
        {
            cout << "Error: Invalid graph data\n";
            return false;
        }

        // BFS / DFS: unweighted graph
        if(algorithm == "bfs" || algorithm == "dfs")
        {
            for(int j = 0; j < degree; j++)
            {
                int neighbour;

                file >> neighbour;

                if(file.fail() || neighbour < 0 || neighbour >= V)
                {
                    cout << "Error: Invalid neighbour\n";
                    return false;
                }

                Edge edge;

                edge.neighbour = neighbour;
                edge.weight = 1;

                input.graph[vertex].push_back(edge);
            }
        }

        // SSSP: weighted graph
        else if(algorithm == "sssp")
        {
            for(int j = 0; j < degree; j++)
            {
                int neighbour;
                int weight;

                file >> neighbour >> weight;

                if(file.fail() ||
                   neighbour < 0 ||
                   neighbour >= V ||
                   weight <= 0)
                {
                    cout << "Error: Invalid edge\n";
                    return false;
                }

                Edge edge;

                edge.neighbour = neighbour;
                edge.weight = weight;

                input.graph[vertex].push_back(edge);
            }
        }
    }

    // Read SOURCE
    string source_word;

    file >> source_word >> input.source;

    if(file.fail() ||
       source_word != "SOURCE" ||
       input.source < 0 ||
       input.source >= V)
    {
        cout << "Error: Invalid source\n";
        return false;
    }

    return true;
}