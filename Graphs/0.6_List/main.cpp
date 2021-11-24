#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int n, m;
    int x, y;
    in >> n >> m;
    std::vector <std::vector <int>> graph (n);

    for (int i = 0; i < m; ++i) {
        in >> x >> y;
        graph[x-1].emplace_back(y);
        graph[y-1].emplace_back(x);
    }
    in.close();

    for (const auto& i : graph) {
        out << i.size() << ' ';
        for (const auto& j : i) {
            out << j << ' ';
        }
        out << '\n';
    }
    out.close();
    return 0;
}
