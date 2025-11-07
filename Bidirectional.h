#pragma once
#include "Graph.h"
#include <utility>
#include <vector>


class Bidirectional {
public:
  static std::pair<double, std::vector<int>>
  bidirectional_dijkstra(const Graph &graph, int source, int destination);
};
