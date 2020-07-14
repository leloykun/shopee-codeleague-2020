#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
ll solve(ll idx, ll n, vector<ll> &p, vector<bool> &bought, vector<vector<ll>> &dp) {
        if (n <= 0) return 0;
        if (idx >= p.size()) return INF;
        if (dp[idx][n] != -1) return dp[idx][n];

        ll ans1, ans2, ans3, ans4;
        ans1 = ans2 = ans3 = ans4 = INF;
        if (idx < p.size()-1 and (not bought[idx] and not bought[idx+1])) {
                bought[idx] = bought[idx+1] = true;
                //buy left, get right
                ans1 = p[idx] + solve(idx+2, n-2, p, bought, dp);
                //buy right, get left
                ans2 = p[idx+1] + solve(idx+2, n-2, p, bought, dp);
                bought[idx] = bought[idx+1] = false;
        }

        //buy left only
        if (not bought[idx]) {
                bought[idx] = true;
                ans3 = p[idx] + solve(idx+1, n-1, p, bought, dp);
                bought[idx] = false;
        }

        //dont buy
        ans4 = solve(idx+1, n, p, bought, dp);

        dp[idx][n] = min({ans1, ans2, ans3, ans4});
        return dp[idx][n];
}

int main() {
        ll T; cin >> T;
        for (ll t = 1; t <= T; ++t) {
                ll s, n; cin >> s >> n;
                vector<ll> p(s);
                vector<vector<ll>> dp(s, vector<ll>(n+1, -1));
                vector<bool> bought(s);
                for (ll i = 0; i < s; ++i)
                        cin >> p[i];
                cout << "Case " << t << ": ";
                cout << solve(0, n, p, bought, dp) << '\n';
        }
        return 0;
}
