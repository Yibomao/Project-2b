#include "Bidirectional.h"
#include "Dijkstra.h"
#include "Graph.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>


#ifdef __linux__
#include <sys/resource.h>
#endif

using namespace std;

double getMemoryUsageMB() {
#ifdef __linux__
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return usage.ru_maxrss / 1024.0;
#else
  return 0.0;
#endif
}

int main() {
  Graph graph;
  graph.addEdge(1, 2, 2.5);
  graph.addEdge(1, 3, 1.2);
  graph.addEdge(2, 4, 3.0);
  graph.addEdge(3, 4, 1.5);
  graph.addEdge(4, 5, 2.0);

  int start = 1, goal = 5;

  cout << "===============================\n";
  cout << " Comparing Dijkstra Algorithms\n";
  cout << "===============================\n";

  // --- Dijkstra ---
  double mem_before = getMemoryUsageMB();
  auto t1 = chrono::high_resolution_clock::now();
  auto distMap = Dijkstra::shortestPath(graph, start);
  auto t2 = chrono::high_resolution_clock::now();
  double mem_after = getMemoryUsageMB();
  auto duration = chrono::duration<double, milli>(t2 - t1).count();

  cout << "\n[Dijkstra]\n";
  if (distMap.find(goal) == distMap.end() ||
      distMap[goal] == numeric_limits<double>::infinity()) {
    cout << "No path found.\n";
  } else {
    cout << "Shortest distance: " << distMap[goal] << "\n";
    cout << "Runtime: " << duration << " ms\n";
    cout << "Approx. memory used: " << (mem_after - mem_before) << " MB\n";
  }

  // --- Bidirectional Dijkstra ---
  mem_before = getMemoryUsageMB();
  t1 = chrono::high_resolution_clock::now();
  auto [distB, pathB] =
      Bidirectional::bidirectional_dijkstra(graph, start, goal);
  t2 = chrono::high_resolution_clock::now();
  mem_after = getMemoryUsageMB();
  duration = chrono::duration<double, milli>(t2 - t1).count();

  cout << "\n[Bidirectional Dijkstra]\n";
  if (distB == numeric_limits<double>::infinity()) {
    cout << "No path found.\n";
  } else {
    cout << "Path: ";
    for (size_t i = 0; i < pathB.size(); ++i)
      cout << pathB[i] << (i + 1 < pathB.size() ? " -> " : "\n");
    cout << "Total cost: " << distB << "\n";
    cout << "Runtime: " << duration << " ms\n";
    cout << "Approx. memory used: " << (mem_after - mem_before) << " MB\n";
  }

  cout << "===============================\n";
  return 0;
}
