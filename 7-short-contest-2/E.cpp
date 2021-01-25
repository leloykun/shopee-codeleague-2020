#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

typedef long long ll;
typedef std::vector<ll> vi;
typedef std::pair<ll, ll> ii;

struct segtree {
  int i, j, val;
  segtree *l, *r;
  segtree(int _i, int _j) : i(_i), j(_j) {
    if (i == j) {
      val = 0;
      l = r = NULL;
    } else {
      int k = (i+j) >> 1;
      l = new segtree(i, k);
      r = new segtree(k+1, j);
      val = l->val + r->val;
  } }
  segtree(int i, int j, segtree *l, segtree *r, int val) :
    i(i), j(j), l(l), r(r), val(val) {}
  segtree* update(int _i, int _val) {
    if (_i <= i and j <= _i)
      return new segtree(i, j, l, r, val + _val);
    else if (_i < i or j < _i)
      return this;
    else {
      segtree *nl = l->update(_i, _val);
      segtree *nr = r->update(_i, _val);
      return new segtree(i, j, nl, nr, nl->val + nr->val);
  } }
  int query(int _i, int _j) {
    if (_i <= i and j <= _j)
      return val;
    else if (_j < i or j < _i)
      return 0;
    else
      return l->query(_i, _j) + r->query(_i, _j);
} };
struct LeqCounter {
  segtree **roots;
  LeqCounter(std::vector<int> &ar, int n) {
    std::vector<ii> nums;
    for (int i = 0; i < n; ++i)
      nums.push_back({ar[i], i});
    std::sort(nums.begin(), nums.end());
    roots = new segtree*[n];
    roots[0] = new segtree(0, n);
    int prev = 0;
    for (ii &e : nums) {
      for (int i = prev+1; i < e.first; ++i)
        roots[i] = roots[prev];
      roots[e.first] = roots[prev]->update(e.second, 1);
      prev = e.first;
    }
    for (int i = prev+1; i < n; ++i)
      roots[i] = roots[prev];
  }
  int count(int i, int j, int x) {
    return roots[x]->query(i, j);
} };

ll dist(ll x1, ll y1, ll x2, ll y2) {
  ll dx = (x1 - x2);
  ll dy = (y1 - y2);
  return dx*dx + dy*dy;
}

int N, Q;

int bfind(std::vector<ii> &dist, ll d) {
  int i = -1;
  for (int jump = N; jump >= 1; jump >>= 1) {
    while (i + jump < N && dist[i + jump].first <= d)
      i += jump;
  }
  return i;
}

ll X[100005], Y[100005];
ll Xg, Yg, Xa, Ya;
std::vector<ii> dists_1, dists_2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::cin >> N;
  for (int i = 0; i < N; ++i)
    std::cin >> X[i] >> Y[i];
  std::cin >> Xg >> Yg >> Xa >> Ya;

  for (int i = 0; i < N; ++i) {
    dists_1.push_back({dist(Xg, Yg, X[i], Y[i]), i});
    dists_2.push_back({dist(Xa, Ya, X[i], Y[i]), i});
  }
  std::sort(dists_1.begin(), dists_1.end());
  std::sort(dists_2.begin(), dists_2.end());

  std::vector<int> poss(N), A(N);
  for (int i = 0; i < N; ++i)
    poss[dists_1[i].second] = i;
  for (int i = 0; i < N; ++i)
    A[i] = poss[dists_2[i].second];
  LeqCounter leq(A, N);

  std::cin >> Q;
  while (Q--) {
    ll Rg, Ra;  std::cin >> Rg >> Ra;
    int i = bfind(dists_1, Rg*Rg);
    int j = bfind(dists_2, Ra*Ra);
    int sakop = j+1;
    if (i != -1) {
      int k = leq.count(0, j, i);
      sakop += (i+1) - 2*k;
    }
    int ans = N - sakop;
    std::cout << ans << "\n";
  }

  return 0;
}
