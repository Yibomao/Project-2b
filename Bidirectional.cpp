#include<bits/stdc++.h>
#include "Bidirectional.h"
#include "Graph.h"
#include<queue>
#include<set>
#include <limits>
using namespace std;
double Bidirectional::bidirectional_dijkstra(const Graph& graph, int source, int destination) {
    unordered_map<int, double> dists;
    unordered_map<int, double> distd;
    unordered_set<int> visS;
    unordered_set<int> visD;
    auto adj = graph.getAdjList();
    for (auto& node : adj) {
        dists[node.first] = numeric_limits<double>::infinity();
        distd[node.first] = numeric_limits<double>::infinity();
    }
    dists[source] = 0;
    distd[destination] = 0;
    using P = pair<double, int>;
    priority_queue<P , vector<P>, greater<P>> pqs;
    priority_queue<P , vector<P>, greater<P>> pqd;
    pqs.push({0.0, source});
    pqd.push({0.0, destination});
    double best = numeric_limits<double>::infinity();
    while (!pqs.empty() && !pqd.empty()) {
        auto [d1, u1] = pqs.top();
        auto [d2, u2] = pqd.top();
        if (d1 <= d2) {
            pqs.pop();
            if (visS.count(u1)) continue;
            visS.insert(u1);
            for (auto [v, w] : adj[u1]) {
                if (dists[v] > dists[u1] + w) {
                    dists[v] = dists[u1] + w;
                    pqs.push({dists[v], v});
                }
                if (visD.count(v)) {
                    best = best < dists[v] + distd[v] ? best : dists[v] + distd[v];
                }
            }
        }
        else {
            pqd.pop();
            if (visD.count(u2)) continue;
            visD.insert(u2);
            for (auto [v, w] : adj[u2]) {
                if (distd[v] > distd[u2] + w) {
                    distd[v] = distd[u2] + w;
                    pqd.push({distd[v], v});
                }
                if (visS.count(v)) {
                    best = best < dists[v] + distd[v] ? best : dists[v] + distd[v];
                }
            }
        }
        if (best <= d1 + d2)
            break;

    }
    return (best == numeric_limits<double>::infinity()) ? -1 : best;
}
