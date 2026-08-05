#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include "timer.h"

#include "../include/graph.h"
#include "../include/csr.h"
#include "../include/bfs.h"
#include "../include/dfs.h"
#include "../include/sssp.h"

using namespace std;

// Function declarations
void run_one_test(string algorithm);
void run_all_tests(string algorithm);
void run_test(string filepath, string algorithm);
bool validate(ifstream &file);


void bfs()
{
    cout << "BFS will run here\n";
}

void dfs()
{
    cout << "DFS will run here\n";
}

void sssp()
{
    cout << "SSSP will run here\n";
}





int main()
{
    int algorithm_choice;
    int run_choice;
    string algorithm;


    cout << "Select Algorithm\n";
    cout << "1. BFS\n";
    cout << "2. DFS\n";
    cout << "3. SSSP\n";
    cout << "Enter choice: ";
    cin >> algorithm_choice;


    if(algorithm_choice==1)
    {
        algorithm= "BFS";
    }
    else if(algorithm_choice==2)
    {
        algorithm= "DFS";
    }
    else if(algorithm_choice==3)
    {
        algorithm= "SSSP";
    }
    else
    {
        cout << "Invalid choice\n";
        return 0;
    }


    cout << "\n1. Run one test\n";
    cout << "2. Run all tests\n";
    cout << "Enter choice: ";
    cin >> run_choice;


    if(run_choice== 1)
    {
        run_one_test(algorithm);
    }
    else if(run_choice== 2)
    {
        run_all_tests(algorithm);
    }
    else
    {
        cout << "Invalid choice\n";
    }


    return 0;
}



void run_one_test(string algorithm)
{
    string filename;

    cout << "Enter test filename: ";
    cin >> filename;

    run_test("tests/" + filename, algorithm);
}


// Run all test files belonging to selected algorithm
void run_all_tests(string algorithm)
{
    filesystem::directory_iterator files("tests");

    for(auto file : files)
    {
        string filename = file.path().filename().string();

        // Only run files belonging to selected algorithm
        if(filename.find(algorithm + "_") == 0)
        {
            run_test(file.path().string(), algorithm);
        }
    }
}

void run_test(string filepath, string algorithm)
{
    ifstream file;
    file.open(filepath);

    if(!file)
    {
        cout << "Error: Could not open test file\n";
        return;
    }


    int V, E;

    file >> V >> E;

    if(file.fail() || V<= 0 || E< 0)
    {
        cout << "Error: Invalid test file\n";
        return;
    }


    //Adjacency list
    vector<vector<Edge>> graph(V);


    //Read adjacency list for all vertices
    for(int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        if(file.fail() || vertex < 0 || vertex >= V || degree < 0)
        {
            cout << "Error: Invalid graph data\n";
            return;
        }


        // BFS and DFS - unweighted graph
        if(algorithm == "BFS" || algorithm == "DFS")
        {
            for(int j = 0; j < degree; j++)
            {
                int neighbour;

                file >> neighbour;

                if(file.fail() || neighbour < 0 || neighbour >= V)
                {
                    cout << "Error: Invalid neighbour\n";
                    return;
                }


                Edge edge;

                edge.neighbour = neighbour;
                edge.weight = 1;

                graph[vertex].push_back(edge);
            }
        }


        // SSSP - weighted graph
        else if(algorithm == "SSSP")
        {
            for(int j = 0; j < degree; j++)
            {
                int neighbour;
                int weight;

                file >> neighbour >> weight;

                if(file.fail() || neighbour < 0 || neighbour >= V || weight <= 0)
                {
                    cout << "Error: Invalid edge\n";
                    return;
                }


                Edge edge;

                edge.neighbour = neighbour;
                edge.weight = weight;

                graph[vertex].push_back(edge);
            }
        }
    }


    // Read SOURCE
    string source_word;
    int source;

    file >> source_word >> source;

    if(file.fail() || source_word != "SOURCE" || source < 0 || source >= V)
    {
        cout << "Error: Invalid source\n";
        return;
    }


    cout << "\nRunning: "<< filesystem::path(filepath).filename()<< endl;


    // Convert adjacency list to CSR
    // This is preprocessing, so it is NOT timed
    CSR csr = make_csr(graph);

    double execution_time;

    if(algorithm == "BFS")
    {
        start_timer();
        bfs();       // later: bfs(csr, source)
        execution_time = stop_timer();
    }

    else if(algorithm == "DFS")
    {
        start_timer();
        dfs();       // later: dfs(csr, source)
        execution_time = stop_timer();
    }

    else if(algorithm == "SSSP")
    {
        start_timer();
        sssp();      // later: sssp(csr, source)
        execution_time = stop_timer();
    }


    cout << "Execution time: "<< execution_time << " ms\n";
    file.close();

}

// Basic validation for now
bool validate(ifstream &file)
{
    int V,E;

    file >> V >> E;

    if(file.fail())
    {
        return false;
    }

    if(V<=0 || E<0)
    {
        return false;
    }

    return true;
}