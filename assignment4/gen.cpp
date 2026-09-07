#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <filesystem>

using namespace std;

mt19937 rng(42);

double random_double(double a, double b)
{
    uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

void generate_kmeans(const string& filename, int N, int D, int K)
{
    ofstream file("tests/" + filename);

    vector<vector<double>> centers(K, vector<double>(D));

    for(int i=0;i<K;i++)
    {
        for(int j=0;j<D;j++)
            centers[i][j]=random_double(-100.0,100.0);
    }

    file<<N<<" "<<D<<" "<<K<<"\n";

    for(int i=0;i<N;i++)
    {
        int cluster=i%K;

        for(int j=0;j<D;j++)
        {
            double value=centers[cluster][j]+random_double(-5.0,5.0);

            file<<fixed<<setprecision(6)<<value;

            if(j<D-1)
                file<<" ";
        }

        file<<"\n";
    }

    file<<"MAX_ITERATIONS 300\n";
    file<<"TOLERANCE 0.0001\n";
}

void generate_fastmap(const string& filename, int N, int K)
{
    ofstream file("tests/" + filename);

    int D=3;

    vector<vector<double>> points(N,vector<double>(D));

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<D;j++)
            points[i][j]=random_double(0.0,1000.0);
    }

    file<<N<<" "<<K<<"\n";

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            double sum=0.0;

            for(int d=0;d<D;d++)
            {
                double diff=points[i][d]-points[j][d];
                sum+=diff*diff;
            }

            double distance=sqrt(sum);

            file<<fixed<<setprecision(6)<<distance;

            if(j<N-1)
                file<<" ";
        }

        file<<"\n";
    }
}

int main()
{
    filesystem::create_directories("tests");

    generate_kmeans("km_01.txt",100,2,3);
    generate_kmeans("km_02.txt",1000,2,5);
    generate_kmeans("km_03.txt",10000,5,8);
    generate_kmeans("km_04.txt",100000,5,10);

    generate_fastmap("fm_01.txt",10,2);
    generate_fastmap("fm_02.txt",100,2);
    generate_fastmap("fm_03.txt",1000,3);
    generate_fastmap("fm_04.txt",10000,3);

    cout<<"All test files generated successfully.\n";

    return 0;
}