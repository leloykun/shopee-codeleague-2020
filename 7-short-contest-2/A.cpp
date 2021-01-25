#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &mnt) {
    int ans = -1;
    int height = 1;

    bool count = false;
    int cur = 0;
    for (int i = 0; i < mnt.size(); i++) {
        if (mnt[i] == 1) {
            count = true;
            if (ans == -1) ans = i;
        }
        else if (count) {
            if (mnt[i] - mnt[i-1] == 1)
                cur = mnt[i];
            else
                count = false;

            if (cur > height) {
                ans = i;
                cur = height;
            }
        }
    }

    count = false;
    for (int i = mnt.size()-1; i >= 0; i--) {
        if (mnt[i] == 1)
            count = true;
        else if (count) {
            if (mnt[i] - mnt[i+1] == 1)
                cur = mnt[i];
            else
                count = false;

            if (cur > height) {
                ans = i;
                cur = height;
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    for (int t = 1; t <= n; t++) {
        int l; cin >> l;
        vector<int> mnt(l);
        for (int i = 0; i < l; i++)
            cin >> mnt[i];

        int ans = solve(mnt);
        cout << "Case #" << t << ": "
            << (ans == -1 ? -1 : mnt[ans]) << ' ' << ans << '\n';
    }
    return 0;
}
