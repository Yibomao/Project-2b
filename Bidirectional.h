#ifndef BIDIRECTIONAL_H
#define BIDIRECTIONAL_H

#include "Graph.h"
#include <vector>
#include <unordered_map>

class Bidirectional {
public:
    static double bidirectional_dijkstra(const Graph& graph, int source, int destination);
};

#endif
