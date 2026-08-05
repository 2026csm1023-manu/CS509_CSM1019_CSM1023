#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "timer.h"

#include "../include/graph.h"
#include "../include/csr.h"
#include "../include/bfs.h"
#include "../include/dfs.h"
#include "../include/sssp.h"
#include "../include/printer.h"

using namespace std;

// Function declarations
void run_one_test(string algorithm);
void run_all_tests(string algorithm);
void run_test(string filepath, string algorithm);


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
        algorithm= "bfs";
    }
    else if(algorithm_choice==2)
    {
        algorithm= "dfs";
    }
    else if(algorithm_choice==3)
    {
        algorithm= "sssp";
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


    //Convert test text file into Graph 
    GraphInput input;
    if(!read_graph(file, algorithm, input))
    {
        return;
    }


    cout << "\nRunning: "<< filesystem::path(filepath).filename()<< endl;


    // Convert adjacency list to CSR
    // This is preprocessing, so it is NOT timed
    CSR csr = make_csr(input.graph);

    double execution_time;

    if(algorithm == "bfs")
    {
    start_timer();
    BFSResult result = bfs(csr, input.source);
    execution_time = stop_timer();
    print_bfs(input.source, result, execution_time);
    }

    else if(algorithm == "dfs")
    {
    start_timer();
    vector<int> result = dfs(csr, input.source);
    execution_time = stop_timer();
    print_dfs(input.source, result, execution_time);
    }

    else if(algorithm == "sssp")
    {
    start_timer();
    vector<int> distance = sssp(csr, input.source);
    execution_time = stop_timer();
    print_sssp(input.source, distance, execution_time);
    }

    file.close();

}

