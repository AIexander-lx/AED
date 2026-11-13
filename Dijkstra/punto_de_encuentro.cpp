#include<bits/stdc++.h>
using namespace::std;

template<class distance_type, typename weight_type>
vector<distance_type> Dijkstra(int src, int n, vector<vector<pair<int, weight_type>>> &G) {
    vector<distance_type> D(n, numeric_limits<distance_type>::max());
    D[src] = 0;
    priority_queue<pair<distance_type, int>, vector<pair<distance_type, int>>, greater<pair<distance_type, int>>> Q;
    Q.emplace(0, src);
    while (not Q.empty()) {
        int u;
        distance_type d;
        tie(d, u) = Q.top(); Q.pop();
        if (D[u] != d) continue;
        for (auto &e : G[u]) {
            int v;
            weight_type w;
            tie(v, w) = e;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                Q.emplace(D[v], v);
            }
        }
    }
    return D;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> G(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    vector<long long> D1 = Dijkstra<long long>(0, n, G);
    vector<long long> Dn = Dijkstra<long long>(n - 1, n, G);
    long long min_T = numeric_limits<long long>::max();
    int cnt_min = 0;
    for (int i = 0; i < n; ++i) {
        long long cur_T = max(D1[i], Dn[i]);
        if (cur_T < min_T) {
            min_T = cur_T;
            cnt_min = 1;
        }
        else if (cur_T == min_T) {
            ++cnt_min;
        }
    }
    if (min_T == numeric_limits<long long>::max()) {
        cout << -1 << '\n';
    }
    else {
        cout << min_T << " " << cnt_min << '\n';
    }
    return 0;
}