#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

const string TEST_PATH = "assignment1/tests/";

mt19937 rng(42);

struct Edge
{
    int to;
    int weight;
};

void writeUnweighted(const vector<vector<Edge>> &adj,
                     int V,
                     int E,
                     const string &filename)
{
    ofstream out(TEST_PATH + filename);

    if (!out.is_open())
    {
        cerr << "Cannot open " << filename << endl;
        return;
    }

    out << V << " " << E << "\n";

    for (int i = 0; i < V; i++)
    {
        out << i << " " << adj[i].size();

        for (auto edge : adj[i])
            out << " " << edge.to;

        out << "\n";
    }

    out << "SOURCE 0\n";
}

void writeWeighted(const vector<vector<Edge>> &adj,
                   int V,
                   int E,
                   const string &filename)
{
    ofstream out(TEST_PATH + filename);

    if (!out.is_open())
    {
        cerr << "Cannot open " << filename << endl;
        return;
    }

    out << V << " " << E << "\n";

    for (int i = 0; i < V; i++)
    {
        out << i << " " << adj[i].size();

        for (auto edge : adj[i])
            out << " " << edge.to << " " << edge.weight;

        out << "\n";
    }

    out << "SOURCE 0\n";
}

void generateGraph(int V, int E)
{
    vector<vector<Edge>> adj(V);

    set<pair<int,int>> used;

    // -------- Step 1 : Create Connected Graph --------

    for (int i = 1; i < V; i++)
    {
        int parent = rng() % i;

        int weight = rng() % 20 + 1;

        adj[parent].push_back({i, weight});
        adj[i].push_back({parent, weight});

        used.insert({min(parent, i), max(parent, i)});
    }

    int currentEdges = V - 1;

    // -------- Step 2 : Add Random Edges --------

    while (currentEdges < E)
    {
        int u = rng() % V;
        int v = rng() % V;

        if (u == v)
            continue;

        pair<int,int> p = {min(u, v), max(u, v)};

        if (used.count(p))
            continue;

        used.insert(p);

        int weight = rng() % 20 + 1;

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});

        currentEdges++;
    }

    string suffix = to_string(V);

    writeUnweighted(adj, V, E, "bfs_" + suffix + ".txt");
    writeUnweighted(adj, V, E, "dfs_" + suffix + ".txt");
    writeWeighted(adj, V, E, "sssp_" + suffix + ".txt");

    cout << "Generated graph with "
         << V
         << " vertices\n";
}

int main()
{
    vector<pair<int,int>> testCases =
    {
        {10,20},
        {100,300},
        {10000,30000},
        {50000,150000},
        {100000,300000}
    };

    for (auto test : testCases)
    {
        generateGraph(test.first, test.second);
    }

    cout << "\nAll graph files generated successfully.\n";

    return 0;
}