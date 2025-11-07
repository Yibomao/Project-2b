#include "Bidirectional.h"
#include "Graph.h"
#include <bits/stdc++.h>
#include <limits>
#include <queue>
#include <set>

using namespace std;

pair<double, vector<int>>
Bidirectional::bidirectional_dijkstra(const Graph &graph, int source,
                                      int destination) {
  unordered_map<int, double> dists;
  unordered_map<int, double> distd;
  unordered_map<int, int> prevS;
  unordered_map<int, int> prevD;
  unordered_set<int> visS;
  unordered_set<int> visD;
  auto adj = graph.getAdjList();

  for (auto &node : adj) {
    dists[node.first] = numeric_limits<double>::infinity();
    distd[node.first] = numeric_limits<double>::infinity();
  }

  dists[source] = 0;
  distd[destination] = 0;

  using P = pair<double, int>;
  priority_queue<P, vector<P>, greater<P>> pqs;
  priority_queue<P, vector<P>, greater<P>> pqd;
  pqs.push({0.0, source});
  pqd.push({0.0, destination});

  double best = numeric_limits<double>::infinity();
  int meetingNode = -1;

  while (!pqs.empty() && !pqd.empty()) {
    auto [d1, u1] = pqs.top();
    auto [d2, u2] = pqd.top();

    if (d1 <= d2) {
      pqs.pop();
      if (visS.count(u1))
        continue;
      visS.insert(u1);

      for (auto [v, w] : adj[u1]) {
        if (dists[v] > dists[u1] + w) {
          dists[v] = dists[u1] + w;
          prevS[v] = u1;
          pqs.push({dists[v], v});
        }
        if (visD.count(v)) {
          double pathCost = dists[u1] + w + distd[v];
          if (pathCost < best) {
            best = pathCost;
            meetingNode = v;
          }
        }
      }
    } else {
      pqd.pop();
      if (visD.count(u2))
        continue;
      visD.insert(u2);

      for (auto [v, w] : adj[u2]) {
        if (distd[v] > distd[u2] + w) {
          distd[v] = distd[u2] + w;
          prevD[v] = u2;
          pqd.push({distd[v], v});
        }
        if (visS.count(v)) {
          double pathCost = distd[u2] + w + dists[v];
          if (pathCost < best) {
            best = pathCost;
            meetingNode = v;
          }
        }
      }
    }

    if (best <= d1 + d2)
      break;
  }

  if (best == numeric_limits<double>::infinity())
    return {numeric_limits<double>::infinity(), {}};

  // Reconstruct path
  vector<int> path;
  int node = meetingNode;

  // From meeting node back to source
  vector<int> path1;
  while (node != source && prevS.count(node)) {
    path1.push_back(node);
    node = prevS[node];
  }
  path1.push_back(source);
  reverse(path1.begin(), path1.end());

  // From meeting node to destination
  vector<int> path2;
  node = meetingNode;
  while (node != destination && prevD.count(node)) {
    node = prevD[node];
    path2.push_back(node);
  }

  path = path1;
  path.insert(path.end(), path2.begin(), path2.end());

  return {best, path};
}
