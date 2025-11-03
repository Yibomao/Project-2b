#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"

int main() {
    Graph graph;

    // Example graph
    graph.addEdge(1, 2, 2.5);
    graph.addEdge(1, 3, 1.2);
    graph.addEdge(2, 4, 3.0);
    graph.addEdge(3, 4, 1.5);
    graph.addEdge(4, 5, 2.0);

    int start = 1, goal = 5;

    auto dijkstraDist = Dijkstra::shortestPath(graph, start);
    auto aStarDist = AStar::shortestPath(graph, start, goal);

    std::cout << "Dijkstra shortest distance to node " << goal << ": " << dijkstraDist[goal] << "\n";
    std::cout << "A* shortest distance to node " << goal << ": " << aStarDist[goal] << "\n";

    return 0;
}
