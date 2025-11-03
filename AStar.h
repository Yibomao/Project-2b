#ifndef ASTAR_H
#define ASTAR_H

#include "Graph.h"
#include <unordered_map>

class AStar {
public:
    static std::unordered_map<int, double> shortestPath(const Graph& graph, int start, int goal);
private:
    static double heuristic(int a, int b);
};

#endif
