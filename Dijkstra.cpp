#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <iostream>

std::unordered_map<int, double> Dijkstra::shortestPath(const Graph& graph, int start) {
    auto adj = graph.getAdjList();
    std::unordered_map<int, double> dist;

    // Initialize all distances to infinity
    for (auto& node : adj)
        dist[node.first] = std::numeric_limits<double>::infinity();

    // If start node not in graph, return empty map
    if (adj.find(start) == adj.end()) {
        std::cerr << "Start node not found in graph.\n";
        return dist;
    }

    dist[start] = 0.0;
    using P = std::pair<double, int>; // (distance, node)
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; // Skip outdated entry

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
