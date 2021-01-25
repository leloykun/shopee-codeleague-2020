#include <iostream>
#include <vector>
#include <utility>
#include <queue>

typedef long long ll;
typedef std::pair<int, ll> ii;

struct graph {
  int n;
  std::vector<ii> *adj;
  int *available, *vis;
  ll *dist;
  graph(int n) : n(n) {
    adj = new std::vector<ii>[n];
    available = new int[n];
    vis = new int[n];
    dist = new ll[n];
    for (int u = 0; u < n; ++u)
      available[u] = 1;
  }
  void add_edge(int u, int v, ll w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  void reset() {
    for (int u = 0; u < n; ++u)
      vis[u] = 0, dist[u] = -1;
  }
  ii bfs(int s) {
    //std::cout << "bfs\n";
    reset();
    std::queue<int> q;  q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      //std::cout << "q: " << u << "\n";
      q.pop();
      vis[u] = 1;
      for (auto &e : adj[u]) {
        int v = e.first;
        ll w = e.second;
        if (!vis[v] and available[v]) {
          q.push(v);
          dist[v] = dist[u] + w;
        }
      }
    }
    //for (int u = 0; u < n; ++u)
    //  std::cout << dist[u] << " ";
    //std::cout << "\n";
    int farthest_u = s;
    ll farthest_d = 0;
    for (int u = 0; u < n; ++u) {
      if (vis[u] and dist[u] > farthest_d) {
        farthest_u = u;
        farthest_d = dist[u];
      }
    }
    return {farthest_u, farthest_d};
  }
};

int N;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::cin >> N;
  graph g(N);
  for (int i = 0; i < N-1; ++i) {
    int u, v, w;  std::cin >> u >> v >> w;
    g.add_edge(u-1, v-1, w);
  }

  g.reset();
  ii res1 = g.bfs(0);
  g.reset();
  ii res2 = g.bfs(res1.first);
  int s = res1.first, t = res2.first;

  ll ans = 0;

  g.available[s] = 0;
  g.reset();
  ii res3;
  for (int u = 0; u < N; ++u)
    if (u != s and u != t) {
      res3 = g.bfs(u);
      break;
    }
  g.reset();
  ii res4 = g.bfs(res3.first);

  g.available[s] = 1;
  g.available[t] = 0;
  g.reset();
  ii res5;
  for (int u = 0; u < N; ++u)
    if (u != s and u != t) {
      res5 = g.bfs(u);
      break;
    }
  g.reset();
  ii res6 = g.bfs(res5.first);

  std::cout << std::max(res4.second, res6.second) << "\n";

  return 0;
}
