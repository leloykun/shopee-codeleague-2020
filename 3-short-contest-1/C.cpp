#include <iostream>

typedef long long ll;
ll MOD = 1e9+7;

ll N, M, K;
ll A, B, C;
ll freq[2001];
ll dp[10001][2001];

ll f(ll j) {
  return (((A * j) % K) * j % K + B) % K;
}

ll solve(ll M, ll s) {
  if (M == 1) {
    return freq[s];
  } else if (dp[M][s] != -1)
    return dp[M][s];
  ll ans = 0;
  for (int k = 0; k < K; ++k)
    ans = (ans + (solve(M-1, k) * freq[(s - k + K) % K]) % MOD) % MOD;
  return dp[M][s] = ans;
}

int main() {
  std::cin >> N >> M >> K;
  if (M >= 10001)
    return 0;

  for (int k = 0; k < K; ++k)
    freq[k] = 0;
  for (int i = 0; i < N; ++i)
    for (int k = 0; k < K; ++k)
      dp[i][k] = -1;

  for (int n = 0; n < N; ++n) {
    std::cin >> A >> B >> C;
    ll mult = C / K;
    for (int j = 0; j < K; ++j)
      freq[f(j)] += mult;
    for (int j = 1; j < K; ++j)
      if (mult * K + j <= C)
        freq[f(j)]++;
  }

  std::cout << solve(M, 0) << "\n";

  return 0;
}
