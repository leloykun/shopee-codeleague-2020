#include <bits/stdc++.h>
using namespace std;

struct dsu_save {
    int v, rnkv, u, rnku;

    dsu_save() {}

    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu {
    vector<int> p, rnk;
    int comps;
    stack<dsu_save> op;

    dsu() {}

    dsu(int n) {
        p.resize(n);
        rnk.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }

    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u) {
            op.push(dsu_save(-69, -69, -69, -69));
            return false;
        }
        comps--;
        if (rnk[v] > rnk[u])
            swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v])
            rnk[u]++;
        return true;
    }

    void pop() {
        if (op.empty())
            return;
        dsu_save x = op.top();
        op.pop();
        if (x.v == -69) return;
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int q, n; cin >> q >> n;
    dsu uf(n);

    string op;
    while (q--) {
        cin >> op;
        if (op == "PUSH") {
            int u, v; cin >> u >> v;
            uf.unite(u-1, v-1);
        }
        else
            uf.pop();

        cout << uf.comps << '\n';
    }
    return 0;
}
