#include "reader.h"
#include <cmath>
#include <string>

bool read_kmeans(ifstream& file,KMeansInput& input)
{
    if(!(file>>input.N>>input.D>>input.K))
        return false;

    if(input.N<=0||input.D<=0||input.K<=0||input.K>input.N)
        return false;

    input.points.resize(input.N,vector<double>(input.D));

    for(int i=0;i<input.N;i++)
    {
        for(int j=0;j<input.D;j++)
        {
            if(!(file>>input.points[i][j])||!isfinite(input.points[i][j]))
                return false;
        }
    }

    string keyword;

    if(!(file>>keyword)||keyword!="MAX_ITERATIONS")
        return false;

    if(!(file>>input.max_iterations)||input.max_iterations<=0)
        return false;

    if(!(file>>keyword)||keyword!="TOLERANCE")
        return false;

    if(!(file>>input.tolerance)||input.tolerance<=0||!isfinite(input.tolerance))
        return false;

    return true;
}

bool read_fastmap(ifstream& file,FastMapInput& input)
{
    if(!(file>>input.N>>input.K))
        return false;

    if(input.N<=0||input.K<=0||input.K>=input.N)
        return false;

    input.distances.resize(input.N,vector<double>(input.N));

    for(int i=0;i<input.N;i++)
    {
        for(int j=0;j<input.N;j++)
        {
            if(!(file>>input.distances[i][j])||!isfinite(input.distances[i][j])||input.distances[i][j]<0)
                return false;
        }
    }

    for(int i=0;i<input.N;i++)
    {
        if(fabs(input.distances[i][i])>1e-9)
            return false;

        for(int j=0;j<input.N;j++)
        {
            if(fabs(input.distances[i][j]-input.distances[j][i])>1e-9)
                return false;
        }
    }

    return true;
}
