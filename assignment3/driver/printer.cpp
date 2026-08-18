#include "printer.h"
#include<fstream>
#include<iomanip>

using namespace std;

void print_gd(const GDResult&result,const GDInput&input,double time,string output_file)
{
    ofstream out(output_file);

    out<<"Algorithm: Gradient Descent\n";
    out<<"Degree: "<<input.degree<<"\n";

    out<<fixed<<setprecision(6);

    out<<"Final x: approximately "<<result.final_x<<"\n";
    out<<"Final f(x): approximately "<<result.final_fx<<"\n";
    out<<"Iterations: "<<result.iterations<<"\n";

    if(result.converged)
        out<<"Converged: true\n";
    else
        out<<"Converged: false\n";

    out<<"Execution time: "<<time<<" ms\n";

    out.close();
}

void print_maxflow(const MaxflowResult&result,int source,int sink,double time,string output_file)
{
    ofstream out(output_file);

    out<<"Algorithm: Maxflow-Mincut\n";
    out<<"Source: "<<source<<"\n";
    out<<"Sink: "<<sink<<"\n";
    out<<"Maximum flow: "<<result.maximum_flow<<"\n";
    out<<"Minimum cut capacity: "<<result.minimum_cut_capacity<<"\n";

    out<<"Source side:";

    for(int i=0;i<result.source_side.size();i++)
        out<<" "<<result.source_side[i];

    out<<"\n";

    out<<"Sink side:";

    for(int i=0;i<result.sink_side.size();i++)
        out<<" "<<result.sink_side[i];

    out<<"\n";

    out<<"Cut edges:\n";

    for(int i=0;i<result.cut_edges.size();i++)
    {
        out<<result.cut_edges[i].u<<" ";
        out<<result.cut_edges[i].v<<" ";
        out<<result.cut_edges[i].capacity<<"\n";
    }

    out<<"Execution time: "<<time<<" ms\n";

    out.close();
}
