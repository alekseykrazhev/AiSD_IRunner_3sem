#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");
    int n, m ,q;
    int x, y;
    in >> n >> m >> q;
    std::vector<std::vector<int>> g (n);

    for (int i = 0; i < m; ++i) {
        in >> x >> y;
        g[x-1].emplace_back(y-1);
        g[y-1].emplace_back(x-1);
    }

    for (int i = 0; i < q; ++i) {
        in >> x;
    }
    return 0;
}
