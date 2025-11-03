#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double INF = 1e300;

// ------------ Edge & Graph ------------
struct Edge {
    int to;
    double w;
    Edge(int _to=0, double _w=1.0): to(_to), w(_w) {}
};

struct Graph {
    int n; // number of nodes (0..n-1)
    vector<vector<Edge>> adj;
    vector<vector<Edge>> rev_adj; // reversed edges
    Graph(int _n=0): n(_n), adj(_n), rev_adj(_n) {}
    void resize(int _n) {
        n = _n;
        adj.assign(n, {});
        rev_adj.assign(n, {});
    }
    void add_edge(int u, int v, double w=1.0) {
        adj[u].emplace_back(v,w);
        rev_adj[v].emplace_back(u,w);
    }
};

