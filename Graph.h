#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


class Graph {
private:
  std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;

public:
  void addEdge(int from, int to, double weight);
  const std::unordered_map<int, std::vector<std::pair<int, double>>> &
  getAdjList() const;
  void loadGraphFromFile(const std::string &filename);
};
