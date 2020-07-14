#include <iostream>
#include <vector>
#define REP(i,n) for (int i = 1; i <= n; i++)


typedef long long ll;
typedef std::vector<std::vector<ll> > matrix;

ll MOD = 1e9+7;
ll N, M, K;

// computes A * B
matrix mul(matrix A, matrix B) {
    matrix C(K+1, std::vector<ll>(K+1));
    REP(i, K) REP(j, K) REP(k, K)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

// computes A ^ p
matrix pow(matrix &A, ll p)
{
    if (p == 1)
        return A;
    if (p % 2)
        return mul(A, pow(A, p-1));
    matrix X = pow(A, p/2);
    return mul(X, X);
}

ll A, B, C;
ll freq[2001];
ll dp[10001][2001];

ll f(ll j) {
  return (((A * j) % K) * j % K + B) % K;
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


  matrix F = std::vector<std::vector<ll>(0LL, K), K);
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < K; ++j) {
      int k = (i - j + K) % K;
      F[i][j] = freq[k];
    }
  }

  matrix P = pow(F, M);
  std::cout << P[0][0] << "\n";
}
