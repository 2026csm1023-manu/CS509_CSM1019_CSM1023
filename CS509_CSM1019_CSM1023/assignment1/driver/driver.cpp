#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
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

string filename_from_path(const string& filepath)
{
    size_t slash = filepath.find_last_of("\\\\/");
    return slash == string::npos ? filepath : filepath.substr(slash + 1);
}

string stem_from_path(const string& filepath)
{
    string filename = filename_from_path(filepath);
    size_t dot = filename.find_last_of('.');
    return dot == string::npos ? filename : filename.substr(0, dot);
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
    WIN32_FIND_DATAA file_data;
    HANDLE search = FindFirstFileA("tests\\\\*", &file_data);
    if(search == INVALID_HANDLE_VALUE)
    {
        cout << "Error: Could not open tests directory\n";
        return;
    }

    do
    {
        string filename = file_data.cFileName;

        // Only run files belonging to selected algorithm
        if(!(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
           filename.find(algorithm + "_") == 0)
        {
            run_test("tests/" + filename, algorithm);
        }
    } while(FindNextFileA(search, &file_data));

    FindClose(search);
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


    //Convert test text file into Graph 
    GraphInput input;
    if(!read_graph(file, algorithm, input))
    {
        return;
    }


    cout << "\nRunning: " << filename_from_path(filepath) << endl;


    //Converting adjacency list to CSR
    //This is preprocessing, so it is NOT timed
    CSR csr = make_csr(input.graph);

    double execution_time;

    //Creating output filename which will store the test output
    string filename = stem_from_path(filepath);

    //File name which will store the output
    string output_file = "test_output/" + filename + "_output.txt";


    /*
    1. Timer is started
    2. Algorithm running
    3. Timer stopped, execution time calculated
    4. Output is saved in test_output folder
    */


    //Runs BFS algorithm
    if(algorithm == "bfs")
    {
    start_timer();
    BFSResult result = bfs(csr, input.source);
    execution_time = stop_timer();
    print_bfs(input.source, result, execution_time,output_file);
    }

    //Runs DFS algorithm
    else if(algorithm == "dfs")
    {
    start_timer();
    vector<int> result = dfs(csr, input.source);
    execution_time = stop_timer();
    print_dfs(input.source, result, execution_time,output_file);
    }

    //Runs SSSP algorithm
    else if(algorithm == "sssp")
    {
    start_timer();
    vector<int> distance = sssp(csr, input.source);
    execution_time = stop_timer();
    print_sssp(input.source, distance, execution_time,output_file);
    }

    file.close();

}

