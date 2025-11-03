#include "Graph.h"

void Graph::addEdge(int from, int to, double weight) {
    adjList[from].push_back({to, weight});
}

const std::unordered_map<int, std::vector<std::pair<int, double>>>& Graph::getAdjList() const {
    return adjList;
}
