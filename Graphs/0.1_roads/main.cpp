#include <iostream>
#include <fstream>
#include <vector>

std::vector<bool> used;
std::vector<std::vector<int>> graph;

void dfs (int v) {
    used[v] = true;
    for (int to : graph[v]) {
        if (! used[to])
            dfs (to);
    }
}

int find_comps(const int& n) {
    for (int i=0; i<n; ++i) used[i] = false;
    int count = 0;
    for (int i=0; i<n; ++i) {
        if (!used[i]) {
            ++count;
            dfs(i);
        }
    }
    return count;
}

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int n, q;
    int x, y;
    in >> n >> q;
    used.resize(n);
    graph.resize(n);

    for (int i = 0; i < q; ++i) {
        in >> x >> y;
        graph[x-1].emplace_back(y-1);
        graph[y-1].emplace_back(x-1);
        out << find_comps(n) << '\n';
    }

    return 0;
}
