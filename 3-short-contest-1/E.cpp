#include <iostream>
#include <vector>
#include <queue>
#include <utility>

typedef long long ll;
typedef std::pair<ll, ll> pll;

ll INF = (1LL << 60);

struct edge {
  int u, v;
  ll cost, cap, flow;
  edge(int u, int v, ll cap, ll cost) :
    u(u), v(v), cap(cap), cost(cost), flow(0) {}
};
struct flow_network {
  int n, s, t, *par, *in_queue, *num_vis;
  ll *dist, *pot;
  std::vector<edge> edges;
  std::vector<int> *adj;
  flow_network(int n, int s, int t) : n(n), s(s), t(t) {
    adj = new std::vector<int>[n];
    par = new int[n];
    in_queue = new int[n];
    num_vis = new int[n];
    dist = new ll[n];
    pot  = new ll[n];
    for (int u = 0; u < n; ++u) pot[u] = 0;
  }
  void add_edge(int u, int v, ll cap, ll cost) {
    // std::cout << u << " " << v << " " << cap << " " << cost << "\n";
    adj[u].push_back(edges.size());
    edges.push_back(edge(u, v, cap, cost));
    adj[v].push_back(edges.size());
    edges.push_back(edge(v, u, 0LL, -cost));
  }
  ll res(edge &e) { return e.cap - e.flow; }
  void bellman_ford() {
    for (int u = 0; u < n; ++u) pot[u] = INF;
    pot[s] = 0;
    for (int it = 0; it < n-1; ++it)
      for (auto e : edges)
        if (res(e) > 0)
          pot[e.v] = std::min(pot[e.v], pot[e.u] + e.cost);
  }
  bool spfa () {
    std::queue<int> q;  q.push(s);
    while (not q.empty()) {
      int u = q.front();  q.pop();  in_queue[u] = 0;
      //std::cout << "vis " << u << "\n";
      if (++num_vis[u] >= n) {
        dist[u] = -INF;
        return false;
      }
      for (int i : adj[u]) {
        edge e = edges[i];
        if (res(e) <= 0)  continue;
        ll nd = dist[u] + e.cost + pot[u] - pot[e.v];
        if (dist[e.v] > nd) {
          dist[e.v] = nd;
          par[e.v] = i;
          if (not in_queue[e.v]) {
            q.push(e.v);
            in_queue[e.v] = 1;
    } } } }
    return dist[t] != INF;
  }
  bool aug_path() {
    for (int u = 0; u < n; ++u) {
      par[u]      = -1;
      in_queue[u] = 0;
      num_vis[u]  = 0;
      dist[u]     = INF;
    }
    dist[s] = 0;
    in_queue[s] = 1;
    return spfa();
  }
  pll calc_max_flow(bool do_bellman_ford=false) {
    ll total_cost = 0, total_flow = 0;
    //std::cout << "start max_flow\n" << "\n";
    if (do_bellman_ford)
      bellman_ford();
    while (aug_path()) {
      ll f = INF;
      for (int i = par[t]; i != -1; i = par[edges[i].u])
        f = std::min(f, res(edges[i]));
      for (int i = par[t]; i != -1; i = par[edges[i].u]) {
        edges[i].flow   += f;
        edges[i^1].flow -= f;
        //std::cout << edges[i].u << " " << edges[i].v << " " << f << "\n";
      }
      //std::cout << f << "\n";
      total_cost += f * (dist[t] + pot[t] - pot[s]);
      //std::cout << f * (dist[t] + pot[t] - pot[s]) << "\n";
      total_flow += f;
      for (int u = 0; u < n; ++u)
        if (par[u] != -1)
          pot[u] += dist[u];
    }
    return {total_cost, total_flow};
} };

int N, M=3, K;
int dr[] = {0, 0, -1, 1};
int dc[] = {1, -1, 0, 0};

int coord(int i, int j) {
  return i*M + j;
}

bool inside(int i, int j) {
  return 0 <= i and i < N and 0 <= j and j < M;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::cin >> N >> K;

  int n = 3*N+3;
  int ss = 3*N;
  int s  = 3*N+1;
  int t  = 3*N+2;
  flow_network g(n, ss, t);
  g.add_edge(ss, s, K, 0);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 3; ++j) {
      ll v; std::cin >> v;
      int c = coord(i, j);
      if (c & 1) {
        g.add_edge(s, c, 1, -v);
        for (int k = 0; k < 4; ++k) {
          //int ni = (i + dr[k] + N) % N;
          //int nj = (j + dc[k] + M) % M;
          int ni = i + dr[k];
          int nj = j + dc[k];
          if (!inside(ni, nj))
            continue;
          int nc = coord(ni, nj);
          g.add_edge(c, nc, 1, 0);
        }
      } else
        g.add_edge(c, t, 1, -v);
    }
  }

  std::cout << -g.calc_max_flow(true).first << "\n";

  return 0;
}
