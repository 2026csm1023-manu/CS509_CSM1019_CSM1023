#include "../include/fastmap.h"

#include <algorithm>
#include <cmath>

namespace
{
double residual_distance(const FastMapInput& input,const vector<vector<double>>& coordinates,int first,int second,int completed_dimensions)
{
    double squared=input.distances[first][second]*input.distances[first][second];

    for(int dimension=0;dimension<completed_dimensions;dimension++)
    {
        double difference=coordinates[first][dimension]-coordinates[second][dimension];
        squared-=difference*difference;
    }

    // Small negative values can occur because of floating-point round-off.
    return sqrt(max(0.0,squared));
}

int farthest_from(const FastMapInput& input,const vector<vector<double>>& coordinates,int object,int completed_dimensions)
{
    int farthest=object;
    double maximum_distance=-1.0;

    for(int candidate=0;candidate<input.N;candidate++)
    {
        double distance=residual_distance(input,coordinates,object,candidate,completed_dimensions);
        if(distance>maximum_distance)
        {
            maximum_distance=distance;
            farthest=candidate;
        }
    }

    return farthest;
}
}

FastMapResult fastmap(const FastMapInput& input)
{
    FastMapResult result;
    result.coordinates.assign(input.N,vector<double>(input.K,0.0));
    result.pivots.reserve(input.K);

    for(int dimension=0;dimension<input.K;dimension++)
    {
        // Two farthest-point sweeps provide a deterministic version of the
        // recommended approximate-farthest-pair pivot heuristic.
        int first=dimension%input.N;
        int second=first;
        for(int sweep=0;sweep<2;sweep++)
        {
            first=farthest_from(input,result.coordinates,second,dimension);
            second=farthest_from(input,result.coordinates,first,dimension);
        }

        result.pivots.push_back(make_pair(first,second));
        double pivot_distance=residual_distance(input,result.coordinates,first,second,dimension);

        if(pivot_distance==0.0)
            continue;

        double pivot_squared=pivot_distance*pivot_distance;
        for(int object=0;object<input.N;object++)
        {
            double first_distance=residual_distance(input,result.coordinates,first,object,dimension);
            double second_distance=residual_distance(input,result.coordinates,second,object,dimension);
            result.coordinates[object][dimension]=
                (first_distance*first_distance+pivot_squared-second_distance*second_distance)/(2.0*pivot_distance);
        }
    }

    return result;
}
