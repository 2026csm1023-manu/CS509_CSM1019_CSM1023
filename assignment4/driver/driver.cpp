#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "reader.h"
#include "printer.h"
#include "timer.h"
#include "../include/kmeans.h"
#include "../include/fastmap.h"

using namespace std;

void run_one_test(int choice);
void run_all_tests(int choice);
void run_test(string filepath,int choice);
string get_name(string filename);

int main()
{
    int choice;
    int run_choice;

    cout<<"1. K-Means Clustering\n";
    cout<<"2. FastMap\n";
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
        filenames={"km_01.txt","km_02.txt","km_03.txt","km_04.txt"};
    }
    else
    {
        filenames={"fm_01.txt","fm_02.txt","fm_03.txt","fm_04.txt"};
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
        KMeansInput input;

        if(!read_kmeans(file,input))
        {
            cout<<"Error: Invalid K-Means input\n";
            return;
        }

        start_timer();

        KMeansResult result=kmeans(input);

        double time=stop_timer();

        print_kmeans(result,input,time,output_file);
    }

    else
    {
        FastMapInput input;

        if(!read_fastmap(file,input))
        {
            cout<<"Error: Invalid FastMap input\n";
            return;
        }

        start_timer();

        FastMapResult result=fastmap(input);

        double time=stop_timer();

        print_fastmap(result,input,time,output_file);
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