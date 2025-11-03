#include "Dijkstra.h"
#include <queue>
#include <limits>

std::unordered_map<int, double> Dijkstra::shortestPath(const Graph& graph, int start) {
    auto adj = graph.getAdjList();
    std::unordered_map<int, double> dist;
    for (auto& node : adj) dist[node.first] = std::numeric_limits<double>::infinity();
    dist[start] = 0.0;

    using P = std::pair<double, int>; // (distance, node)
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
