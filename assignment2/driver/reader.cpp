#include <iostream>
#include "reader.h"

using namespace std;

bool read_buddy_graph(ifstream& file, GraphInput& input)
{
    int V;
    int E;


    //Read number of vertices and edges from test file
    file >> V >> E;


    //Check if first line is valid
    if(file.fail() || V <= 0 || E < 0)
    {
        cout << "Error: Invalid test file\n";
        return false;
    }


    //Create space for all vertices
    input.graph.resize(V);
    
    int total_edges = 0;

    //Read adjacency list for every vertex
    for(int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        //Read vertex number and number of neighbours
        file >> vertex >> degree;

        if(file.fail() || vertex < 0 || vertex >= V || degree < 0)
        {
            cout << "Error: Invalid graph data\n";
            return false;
        }

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

            //Add this neighbour to the vertex's adjacency list
            input.graph[vertex].push_back(edge);

            total_edges++;
        }
    }


    //Each edge is stored twice because graph is undirected
    if(total_edges != 2 * E)
    {
        cout << "Error: Invalid number of edges\n";
        return false;
    }


    return true;
}