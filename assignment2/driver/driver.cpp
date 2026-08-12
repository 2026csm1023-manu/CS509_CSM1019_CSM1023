#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "timer.h"

#include "../include/graph.h"
#include "../include/csr.h"
#include "../include/triangle_count.h"
#include "../include/betweenness.h"
#include "../include/connected_components.h"
#include "printer.h"
#include "reader.h"

using namespace std;

void run_one_test(string algorithm);
void run_all_tests(string algorithm);
void run_test(string filepath, string algorithm);

string filename_from_path(const string& filepath)
{
    size_t slash = filepath.find_last_of("\\/");
    return slash == string::npos ? filepath : filepath.substr(slash + 1);
}

string stem_from_path(const string& filepath)
{
    string filename = filename_from_path(filepath);
    size_t dot = filename.find_last_of('.');
    return dot == string::npos ? filename : filename.substr(0, dot);
}

bool compare_edges(const Edge& a, const Edge& b)
{
    return a.neighbour < b.neighbour;
}

int main()
{
    int algorithm_choice;
    int run_choice;
    string algorithm;

    cout << "Select Algorithm\n";
    cout << "1. Triangle Counting\n";
    cout << "2. Betweenness Centrality\n";
    cout << "3. Connected Components\n";
    cout << "Enter choice: ";
    cin >> algorithm_choice;

    if(algorithm_choice == 1)
    {
        algorithm = "tc";
    }
    else if(algorithm_choice == 2)
    {
        algorithm = "bc";
    }
    else if(algorithm_choice == 3)
    {
        algorithm = "cc";
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

    if(run_choice == 1)
    {
        run_one_test(algorithm);
    }
    else if(run_choice == 2)
    {
        run_all_tests(algorithm);
    }
    else
    {
        cout << "Invalid choice\n";
    }

    return 0;
}


//Runs one test file of algorithm choosen and filename provided
void run_one_test(string algorithm)
{
    string filename;

    cout << "Enter test filename: ";
    cin >> filename;

    run_test("tests/" + filename, algorithm);
}



//Runs all test files belonging to selected algorithm
void run_all_tests(string algorithm)
{
    try
    {
        for(const auto& entry : filesystem::directory_iterator("tests"))
        {
            if(entry.is_regular_file())
            {
                string filename = entry.path().filename().string();

               //Only run files belonging to selected algorithm
                if(filename.find(algorithm + "_") == 0)
                {
                    run_test("tests/" + filename, algorithm);
                }
            }
        }
    }
    catch(...)
    {
        cout << "Error: Could not open tests directory\n";
    }
}

//Function to run 1 selected test and algorithm
void run_test(string filepath, string algorithm)
{
    ifstream file;
    file.open(filepath);

    if(!file)
    {
        cout << "Error: Could not open test file\n";
        return;
    }

    GraphInput input;

    //Convert test text file into Graph 
    if(!read_buddy_graph(file, input))
    {
        file.close();
        return;
    }

    cout << "\nRunning: "<< filename_from_path(filepath)<< endl;

    for(int i = 0; i < input.graph.size(); i++)
    {
        sort(input.graph[i].begin(),input.graph[i].end(),compare_edges);
    }

    //convert graph to CSR
    CSR csr = make_csr(input.graph);
    double execution_time;
    string filename = stem_from_path(filepath);
    string output_file = "test_output/" + filename + "_output.txt";


    
    /*
    1. Timer is started
    2. Algorithm running
    3. Timer stopped, execution time calculated
    4. Output is saved in test_output folder
    */

    //Run Triangle Count algo
    if(algorithm == "tc")
    {
        start_timer();
        vector<tuple<int,int,int>> triangles = triangleCount::countTriangles(csr);
        execution_time = stop_timer();

        bool print_triangles = (csr.vertices < 100);

        print_triangle_count(triangles.size(),triangles,execution_time,output_file,print_triangles);
    }

    //R&un Betweenness Centrality algo
    else if(algorithm == "bc")
    {
        start_timer();
        vector<double> centrality = BetweennessCentrality::compute(csr);
        execution_time = stop_timer();

        print_betweenness_centrality(centrality,execution_time,output_file);
    }

    //Run Connected Components algo
    else if(algorithm=="cc")
    {
        vector<int> component;

        start_timer();
        int number_of_components=ConnectedComponents::findComponents(csr,component);
        execution_time = stop_timer();

        print_connected_components(number_of_components,component,execution_time,output_file);
    }

    file.close();
}
