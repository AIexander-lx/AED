#include<bits/stdc++.h>
using namespace::std;

typedef pair<int, int> info;
const int N = 10001;

int n, P, Q, M;
int D[N];
int edges[N];

pair<int, int> Dijkstra(int src) {
    fill_n(D + 1, n, numeric_limits<int>::max());
    fill_n(edges + 1, n, numeric_limits<int>::max());
    D[src] = 0;
    edges[src] = 0;
    vector<int> unvisited(n);
    iota(unvisited.begin(), unvisited.end(), 1);
    for (int s = 1; s <= n; ++s) {
        int u = -1;
        int pos = -1;
        int at = 0;
        for (int i : unvisited) {
            if (u == -1 or (D[u] > D[i] or D[u] == D[i] and edges[u] > edges[i])) {
                u = i;
                pos = at;
            }
            ++at;
        }
        if (pos + 1 != unvisited.size()) {
            swap(unvisited[pos], unvisited.back());
        }
        unvisited.pop_back();
        for (int v : unvisited) {
            int w = (1ll * (u + v) * P + ((1ll * u * v) % M * Q)) % M + 1;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                edges[v] = edges[u] + 1;
            }
            else if (D[v] == D[u] + w) {
                edges[v] = min(edges[v], edges[u] + 1);
            }
        }
    }
    return {D[n], edges[n]};
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> P >> Q >> M;
    info res = Dijkstra(1);
    cout << res.first << " " << res.second << '\n';
    return 0;
}