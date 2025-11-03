#include "AStar.h"
#include <queue>
#include <cmath>
#include <limits>
#include <iostream>

double AStar::heuristic(int a, int b) {
    // Simple heuristic based on node ID difference (placeholder)
    return std::abs(a - b);
}

std::unordered_map<int, double> AStar::shortestPath(const Graph& graph, int start, int goal) {
    auto adj = graph.getAdjList();
    std::unordered_map<int, double> gScore, fScore;
    
    // Initialize all nodes to infinity
    for (auto& node : adj) {
        gScore[node.first] = std::numeric_limits<double>::infinity();
        fScore[node.first] = std::numeric_limits<double>::infinity();
    }

    if (adj.find(start) == adj.end() || adj.find(goal) == adj.end()) {
        std::cerr << "Start or goal node not found in graph.\n";
        return gScore;
    }

    gScore[start] = 0.0;
    fScore[start] = heuristic(start, goal);

    using P = std::pair<double, int>; // (fScore, node)
    std::priority_queue<P, std::vector<P>, std::greater<P>> openSet;
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        auto [f, current] = openSet.top();
        openSet.pop();

        if (current == goal)
            break;

        for (auto [neighbor, weight] : adj[current]) {
            double tentative_g = gScore[current] + weight;
            if (tentative_g < gScore[neighbor]) {
                gScore[neighbor] = tentative_g;
                fScore[neighbor] = tentative_g + heuristic(neighbor, goal);
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    return gScore;
}
