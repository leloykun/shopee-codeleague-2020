#include <iostream>
#include <vector>

typedef long long ll;

struct graph {
  int n;
  std::vector<int> *adj;
  ll *S, *R, *Q;
  bool *F;
  graph(int n) : n(n) {
    adj = new std::vector<int>[n];
    S = new ll[n];
    R = new ll[n];
    Q = new ll[n];
    F = new bool[n];
    for (int u = 0; u < n; ++u)
      F[u] = false;
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void add_node(int u, int p, int q, bool is_fixed, int s=-1) {
    //std::cout << u << " " << p << " " << q << " " << is_fixed << " " << s << "\n";
    if (p != -1)
      add_edge(u, p);
    Q[u] = q;
    F[u] = is_fixed;
    S[u] = s;
  }
  ll dfs_fixed(int u, int p=-1, ll q_prod=1) {
    //std::cout << "dfs " << u << " \n";
    //std::cout << "dfs "  << u << " " << sum_weight << " \n";
    if (F[u]) {
      ll sum_weight = 0;
      for (int v : adj[u]) {
        if (v != p) {
          sum_weight += dfs_fixed(v, u, Q[v]);
        }
      }
      R[u] = S[u] - sum_weight;
      //std::cout << u << " " << sum_weight << "\n";
      return q_prod * S[u];
    } else {
      ll sum_weight = 0;
      for (int v : adj[u]) {
        if (v != p) {
          sum_weight += dfs_fixed(v, u, q_prod * Q[v]);
        }
      }
      return sum_weight;
    }
  }
  void dfs_derivative(int u, int p=-1, ll ps=-1) {
    if (!F[u]) {
      R[u] = ps / Q[u];
    }
    for (int v : adj[u]) {
      if (v != p) {
        dfs_derivative(v, u, R[u]);
      }
    }
  }
};

ll N, M;

int main() {
  std::cin >> N >> M;

  graph g(N+1);

  g.add_node(1, -1, 1, true, M);
  for (int u = 2; u <= N; ++u) {
    ll t, p, q;  std::cin >> t >> p >> q;
    if (t == 1) {
      g.add_node(u, p, q, false);
    } else {
      ll s;       std::cin >> s;
      g.add_node(u, p, q, true, s);
    }
  }
  g.dfs_fixed(1);
  g.dfs_derivative(1);

  for (int u = 1; u <= N; ++u)
    std::cout << g.R[u] << "\n";

  return 0;
}
