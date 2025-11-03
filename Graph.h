#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>

class Graph {
public:
    void addEdge(int from, int to, double weight);
    const std::unordered_map<int, std::vector<std::pair<int, double>>>& getAdjList() const;

private:
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;
};

#endif
