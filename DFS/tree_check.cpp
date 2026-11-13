#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
bool vis[N];
vector<int> G[N];

int DFS(int u) {
    int res = 1;
    vis[u] = true;
    for (int &v : G[u]) {
        if (vis[v]) continue;
        res += DFS(v);
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    if (m != n - 1) {
        cout << "NO" << '\n';
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int cc_size = DFS(1);
    cout << (cc_size == n ? "YES" : "NO") << '\n';
    return 0;
}