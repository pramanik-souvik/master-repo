#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Breadth-First Search (BFS)
void bfs(int start, const vector<vector<int>>& g, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Depth-First Search (DFS) - Recursive
void dfs_recursive(int u, const vector<vector<int>>& g, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : g[u]) {
        if (!visited[v]) {
            dfs_recursive(v, g, visited);
        }
    }
}

// DFS wrapper (handles disconnected graphs)
void dfs(const vector<vector<int>>& g) {
    vector<bool> visited(g.size(), false);
    for (int i = 0; i < (int)g.size(); i++) {
        if (!visited[i]) {
            dfs_recursive(i, g, visited);
        }
    }
    cout << endl;
}

// BFS wrapper (handles disconnected graphs)
void bfs_full(const vector<vector<int>>& g) {
    vector<bool> visited(g.size(), false);
    for (int i = 0; i < (int)g.size(); i++) {
        if (!visited[i]) {
            bfs(i, g, visited);
        }
    }
    cout << endl;
}

int main() {
    vector<vector<int>> g = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2} 
    };

    cout << "BFS traversal: ";
    bfs_full(g);

    cout << "DFS traversal: ";
    dfs(g);

    return 0;
}