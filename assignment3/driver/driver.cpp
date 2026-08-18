#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "reader.h"
#include "printer.h"
#include "timer.h"
#include "../include/csr.h"
#include "../include/gradient_descent.h"
#include "../include/maxflow.h"

using namespace std;

void run_one_test(int choice);
void run_all_tests(int choice);
void run_test(string filepath,int choice);
string get_name(string filename);

int main()
{
    int choice;
    int run_choice;

    cout<<"1. Gradient Descent\n";
    cout<<"2. Maxflow-Mincut\n";
    cout<<"Enter choice: ";
    cin>>choice;

    if(choice<1||choice>2)
    {
        cout<<"Invalid choice\n";
        return 0;
    }

    cout<<"\n1. Run one test\n";
    cout<<"2. Run all tests\n";
    cout<<"Enter choice: ";
    cin>>run_choice;

    if(run_choice==1)
        run_one_test(choice);
    else if(run_choice==2)
        run_all_tests(choice);
    else
        cout<<"Invalid choice\n";

    return 0;
}

void run_one_test(int choice)
{
    string filename;

    cout<<"Enter test filename: ";
    cin>>filename;

    run_test("tests/"+filename,choice);
}

void run_all_tests(int choice)
{
    vector<string> filenames;

    if(choice==1)
    {
        filenames={"gd_01.txt","gd_02.txt","gd_03.txt","gd_04.txt","gd_05.txt"};
    }
    else
    {
        filenames={"maxflow_10.txt","maxflow_100.txt","maxflow_1000.txt",
                   "maxflow_10000.txt","maxflow_50000.txt"};
    }

    for(const string& filename:filenames)
        run_test("tests/"+filename,choice);
}

void run_test(string filepath,int choice)
{
    ifstream file(filepath);

    if(!file)
    {
        cout<<"Error: Could not open test file\n";
        return;
    }

    string output_file="outputs/"+get_name(filepath)+"_output.txt";

    if(choice==1)
    {
        GDInput input;

        if(!read_gd(file,input))
        {
            cout<<"Error: Invalid Gradient Descent input\n";
            return;
        }

        start_timer();

        GDResult result=gradient_descent(input);

        double time=stop_timer();

        print_gd(result,input,time,output_file);
    }

    else
    {
        vector<vector<Edge>>graph;
        int source;
        int sink;

        if(!read_maxflow(file,graph,source,sink))
        {
            cout<<"Error: Invalid Maxflow input\n";
            return;
        }

        CSR csr=make_csr(graph);

        start_timer();

        MaxflowResult result=maxflow(csr,source,sink);

        double time=stop_timer();

        print_maxflow(result,source,sink,time,output_file);
    }

    file.close();
}

string get_name(string filename)
{
    size_t slash=filename.find_last_of("\\/");

    if(slash!=string::npos)
        filename=filename.substr(slash+1);

    size_t dot=filename.find_last_of('.');

    if(dot==string::npos)
        return filename;

    return filename.substr(0,dot);
}
