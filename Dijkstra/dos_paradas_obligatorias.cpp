#include<bits/stdc++.h>
using namespace::std;

const long long inf = numeric_limits<long long>::max();

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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    --a; --b;
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
    vector<long long> Da = Dijkstra<long long>(a, n, G);
    long long res = inf;
    if (D1[a] != inf and Da[b] != inf and Dn[b] != inf and D1[a] + Da[b] + Dn[b] < res) {
        res = D1[a] + Dn[b] + Da[b];
    }
    if (D1[b] != inf and Da[b] != inf and Dn[a] != inf and D1[b] + Da[b] + Dn[a] < res) {
        res = D1[b] + Dn[a] + Da[b];
    }
    if (res == inf) res = -1;
    cout << res << '\n';
    return 0;
}