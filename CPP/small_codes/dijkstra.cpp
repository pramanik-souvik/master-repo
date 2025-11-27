#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int INF = 1e9;

void dijkstra(int s, vector<vector<pair<int,int>>>& g) {
    int n = g.size();
    vector<int> dist(n, INF);
    dist[s] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();
        int d = top.first, u = top.second;

        if (d > dist[u]){
            continue;
        }

        for (auto edge : g[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }


    for (int i = 0; i < n; i++) { 
        cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<pair<int,int>>> g = {
        { {1,4}, {2,1} },
        { {3,1} },
        { {1,2}, {3,5} },
        {}
    };

    dijkstra(0, g);
    return 0;
}