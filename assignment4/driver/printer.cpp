#include "printer.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void print_kmeans(const KMeansResult& result,const KMeansInput& input,double execution_time,const string& output_file)
{
    ofstream file(output_file);

    if(!file)
    {
        cout<<"Error: Could not create output file\n";
        return;
    }

    file<<"Algorithm: K-Means Clustering\n";
    file<<"K: "<<input.K<<"\n\n";
    file<<"Point assignments:\n";

    for(int i=0;i<input.N;i++)
        file<<i<<" "<<result.assignments[i]<<"\n";

    file<<"\nFinal centroids:\n";
    file<<fixed<<setprecision(6);

    for(int i=0;i<input.K;i++)
    {
        file<<i<<": ";
        for(int j=0;j<input.D;j++)
        {
            file<<result.centroids[i][j];
            if(j<input.D-1)
                file<<" ";
        }
        file<<"\n";
    }

    file<<"\nWCSS: "<<result.WCSS<<"\n";
    file<<"Iterations: "<<result.iterations<<"\n";
    file<<"Converged: "<<(result.converged?"true":"false")<<"\n";
    file<<"Execution time: "<<execution_time<<" ms\n";

    cout<<"Running K-Means\n";
    cout<<"Execution time: "<<execution_time<<" ms\n";
}

void print_fastmap(const FastMapResult& result,const FastMapInput& input,double execution_time,const string& output_file)
{
    ofstream file(output_file);

    if(!file)
    {
        cout<<"Error: Could not create output file\n";
        return;
    }

    file<<"Algorithm: FastMap\n";
    file<<"Target dimensions: "<<input.K<<"\n\n";
    file<<"Pivots per dimension:\n";

    for(int i=0;i<input.K;i++)
        file<<"Dim "<<i+1<<": "<<result.pivots[i].first<<" "<<result.pivots[i].second<<"\n";

    file<<"\nObject coordinates:\n";
    file<<fixed<<setprecision(6);

    for(int i=0;i<input.N;i++)
    {
        file<<i<<": ";
        for(int j=0;j<input.K;j++)
        {
            file<<result.coordinates[i][j];
            if(j<input.K-1)
                file<<" ";
        }
        file<<"\n";
    }

    file<<"\nExecution time: "<<execution_time<<" ms\n";

    cout<<"Running FastMap\n";
    cout<<"Execution time: "<<execution_time<<" ms\n";
}
