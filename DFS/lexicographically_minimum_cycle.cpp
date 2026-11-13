#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int m;
int vis[N];
vector<int> G[N];
stack<int> current_path;
vector<pair<int, int>> edges;

bool has_cycle(int u, int rt, int p = -1) {
    vis[u] = 1;
    current_path.emplace(u);
    for (int &v : G[u]) {
        if (v == p) continue;
        if (vis[v] == 2) continue;
        if (vis[v] == 1) {
            if (v == rt) {
                // Encontre un ciclo
                vector<int> res;
                while (not current_path.empty() and current_path.top() != rt) {
                    res.emplace_back(current_path.top());
                    current_path.pop();
                }
                res.emplace_back(current_path.top());
                reverse(res.begin(), res.end());
                cout << "YES" << '\n';
                cout << res.size() << '\n';
                for (int &x: res) {
                    cout << x << " \n"[x == res.back()];
                }
                return true;
            }
            continue;
        }
        if (has_cycle(v, rt, u)) {
            return true;
        }
    }
    current_path.pop();
    vis[u] = 2;
    return false;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    for (int i = 1; i <= n; ++i) sort(G[i].begin(), G[i].end());
    for (int i = 1; i <= n; ++i) {
        if (has_cycle(i, i)) {
            return 0;
        }
        fill_n(vis + 1, n, 0);
    }
    cout << "NO" << '\n';
    return 0;
}