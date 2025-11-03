#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <unordered_map>

class Dijkstra {
public:
    static std::unordered_map<int, double> shortestPath(const Graph& graph, int start);
};

#endif
