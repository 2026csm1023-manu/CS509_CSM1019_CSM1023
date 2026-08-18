#include "reader.h"

using namespace std;

bool read_gd(ifstream&file,GDInput&input)
{
    string word;

    file>>word>>input.degree;

    if(file.fail()||input.degree<1)
        return false;

    file>>word;

    if(word!="COEFFICIENTS")
        return false;

    input.coefficients.resize(input.degree+1);

    for(int i=0;i<=input.degree;i++)
        file>>input.coefficients[i];

    file>>word>>input.initial_x;

    if(word!="INITIAL_X")
        return false;

    file>>word>>input.learning_rate;

    if(word!="LEARNING_RATE"||input.learning_rate<=0)
        return false;

    file>>word>>input.tolerance;

    if(word!="TOLERANCE"||input.tolerance<=0)
        return false;

    file>>word>>input.max_iterations;

    if(word!="MAX_ITERATIONS"||input.max_iterations<=0)
        return false;

    return true;
}

bool read_maxflow(ifstream&file,vector<vector<Edge>>&graph,int&source,int&sink)
{
    int V,E;

    file>>V>>E;

    if(file.fail()||V<=0||E<0)
        return false;

    graph.resize(V);

    for(int i=0;i<V;i++)
    {
        int vertex,degree;

        file>>vertex>>degree;

        if(file.fail()||vertex<0||vertex>=V||degree<0)
            return false;

        for(int j=0;j<degree;j++)
        {
            int neighbour,capacity;

            file>>neighbour>>capacity;

            if(file.fail()||neighbour<0||neighbour>=V||capacity<0)
                return false;

            Edge edge;

            edge.neighbour=neighbour;
            edge.weight=capacity;

            graph[vertex].push_back(edge);
        }
    }

    string word;

    file>>word>>source;

    if(word!="SOURCE")
        return false;

    file>>word>>sink;

    if(word!="SINK")
        return false;

    if(source<0||source>=V||sink<0||sink>=V||source==sink)
        return false;

    return true;
}
