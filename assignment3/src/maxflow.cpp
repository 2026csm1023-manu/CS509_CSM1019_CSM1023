#include "../include/maxflow.h"

#include <algorithm>
#include <limits>
#include <queue>

namespace
{
struct ResidualEdge
{
    int to;
    int reverse_index;
    int residual_capacity;
};

class Dinic
{
public:
    explicit Dinic(int vertices)
        : residual_graph(vertices), level(vertices), next_edge(vertices) {}

    void add_edge(int from, int to, int capacity)
    {
        ResidualEdge forward{to, static_cast<int>(residual_graph[to].size()), capacity};
        ResidualEdge reverse{from, static_cast<int>(residual_graph[from].size()), 0};
        residual_graph[from].push_back(forward);
        residual_graph[to].push_back(reverse);
    }

    int maximum_flow(int source, int sink)
    {
        int total_flow = 0;

        while (build_level_graph(source, sink))
        {
            std::fill(next_edge.begin(), next_edge.end(), 0);

            while (true)
            {
                const int pushed = send_flow(
                    source, sink, std::numeric_limits<int>::max());

                if (pushed == 0)
                    break;

                total_flow += pushed;
            }
        }

        return total_flow;
    }

    vector<bool> reachable_from(int source) const
    {
        vector<bool> reachable(residual_graph.size(), false);
        queue<int> pending;
        reachable[source] = true;
        pending.push(source);

        while (!pending.empty())
        {
            const int vertex = pending.front();
            pending.pop();

            for (const ResidualEdge& edge : residual_graph[vertex])
            {
                if (edge.residual_capacity > 0 && !reachable[edge.to])
                {
                    reachable[edge.to] = true;
                    pending.push(edge.to);
                }
            }
        }

        return reachable;
    }

private:
    bool build_level_graph(int source, int sink)
    {
        std::fill(level.begin(), level.end(), -1);
        queue<int> pending;
        level[source] = 0;
        pending.push(source);

        while (!pending.empty())
        {
            const int vertex = pending.front();
            pending.pop();

            for (const ResidualEdge& edge : residual_graph[vertex])
            {
                if (edge.residual_capacity > 0 && level[edge.to] == -1)
                {
                    level[edge.to] = level[vertex] + 1;
                    pending.push(edge.to);
                }
            }
        }

        return level[sink] != -1;
    }

    int send_flow(int vertex, int sink, int available_flow)
    {
        if (vertex == sink)
            return available_flow;

        for (int& edge_index = next_edge[vertex];
             edge_index < static_cast<int>(residual_graph[vertex].size());
             ++edge_index)
        {
            ResidualEdge& edge = residual_graph[vertex][edge_index];

            if (edge.residual_capacity <= 0 || level[edge.to] != level[vertex] + 1)
                continue;

            const int pushed = send_flow(
                edge.to, sink, std::min(available_flow, edge.residual_capacity));

            if (pushed == 0)
                continue;

            edge.residual_capacity -= pushed;
            residual_graph[edge.to][edge.reverse_index].residual_capacity += pushed;
            return pushed;
        }

        return 0;
    }

    vector<vector<ResidualEdge>> residual_graph;
    vector<int> level;
    vector<int> next_edge;
};
}

MaxflowResult maxflow(const CSR& csr, int source, int sink)
{
    Dinic dinic(csr.vertices);

    // Build the residual network from the already-prepared CSR graph.  Each
    // CSR entry is an original directed capacity edge; reverse edges exist
    // only inside Dinic's residual graph.
    for (int u = 0; u < csr.vertices; ++u)
    {
        for (int index = csr.row_ptr[u]; index < csr.row_ptr[u + 1]; ++index)
            dinic.add_edge(u, csr.col_idx[index], csr.values[index]);
    }

    MaxflowResult result{};
    result.maximum_flow = dinic.maximum_flow(source, sink);

    const vector<bool> source_reachable = dinic.reachable_from(source);
    for (int vertex = 0; vertex < csr.vertices; ++vertex)
    {
        if (source_reachable[vertex])
            result.source_side.push_back(vertex);
        else
            result.sink_side.push_back(vertex);
    }

    // Cut edges and their capacity must be reported from the original graph,
    // not from residual edges.
    for (int u = 0; u < csr.vertices; ++u)
    {
        if (!source_reachable[u])
            continue;

        for (int index = csr.row_ptr[u]; index < csr.row_ptr[u + 1]; ++index)
        {
            const int v = csr.col_idx[index];
            if (!source_reachable[v])
            {
                result.cut_edges.push_back({u, v, csr.values[index]});
                result.minimum_cut_capacity += csr.values[index];
            }
        }
    }

    return result;
}
