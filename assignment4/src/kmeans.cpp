#include "../include/kmeans.h"

#include <cmath>
#include <limits>

namespace
{
double squared_distance(const vector<double>& left,const vector<double>& right)
{
    double total=0.0;

    for(size_t dimension=0;dimension<left.size();dimension++)
    {
        double difference=left[dimension]-right[dimension];
        total+=difference*difference;
    }

    return total;
}
}

KMeansResult kmeans(const KMeansInput& input)
{
    KMeansResult result;
    result.assignments.assign(input.N,-1);
    result.centroids.assign(input.K,vector<double>(input.D));
    result.iterations=0;
    result.WCSS=0.0;
    result.converged=false;

    // Using the first K points makes the result reproducible, as required.
    for(int cluster=0;cluster<input.K;cluster++)
        result.centroids[cluster]=input.points[cluster];

    for(int iteration=0;iteration<input.max_iterations;iteration++)
    {
        bool assignments_changed=false;
        vector<vector<double>> sums(input.K,vector<double>(input.D,0.0));
        vector<int> counts(input.K,0);

        for(int point=0;point<input.N;point++)
        {
            int nearest_cluster=0;
            double nearest_distance=squared_distance(input.points[point],result.centroids[0]);

            for(int cluster=1;cluster<input.K;cluster++)
            {
                double distance=squared_distance(input.points[point],result.centroids[cluster]);
                if(distance<nearest_distance)
                {
                    nearest_distance=distance;
                    nearest_cluster=cluster;
                }
            }

            if(result.assignments[point]!=nearest_cluster)
                assignments_changed=true;

            result.assignments[point]=nearest_cluster;
            counts[nearest_cluster]++;

            for(int dimension=0;dimension<input.D;dimension++)
                sums[nearest_cluster][dimension]+=input.points[point][dimension];
        }

        double maximum_shift=0.0;
        for(int cluster=0;cluster<input.K;cluster++)
        {
            // Empty clusters retain their old centroid.
            if(counts[cluster]==0)
                continue;

            vector<double> updated_centroid(input.D);
            for(int dimension=0;dimension<input.D;dimension++)
                updated_centroid[dimension]=sums[cluster][dimension]/counts[cluster];

            maximum_shift=max(maximum_shift,sqrt(squared_distance(result.centroids[cluster],updated_centroid)));
            result.centroids[cluster]=updated_centroid;
        }

        result.iterations=iteration+1;
        if(!assignments_changed||maximum_shift<=input.tolerance)
        {
            result.converged=true;
            break;
        }
    }

    for(int point=0;point<input.N;point++)
        result.WCSS+=squared_distance(input.points[point],result.centroids[result.assignments[point]]);

    return result;
}
