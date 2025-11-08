#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Graph::addEdge(int from, int to, double weight) {
  adjList[from].push_back({to, weight});
  adjList[to].push_back({from, weight}); // undirected road network
}

const std::unordered_map<int, std::vector<std::pair<int, double>>> &
Graph::getAdjList() const {
  return adjList;
}

// New: Load graph from file (SNAP format, e.g., roadNet-CA.txt)
void Graph::loadGraphFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::string line;
  long long count = 0;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue; // skip comments

    std::stringstream ss(line);
    int u, v;
    ss >> u >> v;
    addEdge(u, v, 1.0); // all edges have weight 1

    // Optional progress output every 1 million edges
    if (++count % 1000000 == 0) {
      std::cout << "Loaded " << count << " edges..." << std::endl;
    }
  }

  std::cout << "Finished loading graph with " << adjList.size() << " nodes and "
            << count << " edges." << std::endl;
}
