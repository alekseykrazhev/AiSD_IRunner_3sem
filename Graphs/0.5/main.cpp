#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int n;
    int x, y;
    in >> n;
    std::vector <std::vector <int>> graph (n);
    std::vector<int> ans(n, 0);

    for (int i = 0; i < n-1; ++i) {
        in >> x >> y;
        graph[x-1].emplace_back(y);
    }
    in.close();

    for (int i = 0; i < n; ++i) {
        if (!graph[i].empty()) {
            for (int j = 0; j < graph[i].size(); ++j){
                ans[graph[i][j] - 1] = i + 1;
            }
        }
    }

    for (const auto& i : ans) {
        out << i << ' ';
    }

    /*
    for (const auto& i : graph) {
        for (const auto& j : i) {
            out << j << ' ';
        }
        out << '\n';
    }*/
    out.close();
    return 0;
}
