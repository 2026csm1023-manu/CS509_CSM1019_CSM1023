#ifndef KMEANS_H
#define KMEANS_H

#include <vector>

using namespace std;

struct KMeansInput
{
    int N;
    int D;
    int K;
    int max_iterations;
    double tolerance;
    vector<vector<double>> points;
};

struct KMeansResult
{
    vector<int> assignments;
    vector<vector<double>> centroids;
    int iterations;
    double WCSS;
    bool converged;
};

KMeansResult kmeans(const KMeansInput& input);

#endif
