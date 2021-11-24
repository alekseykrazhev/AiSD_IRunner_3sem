#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int n;
    int x, y;
    std::string temp;
    std::getline(in, temp);
    std::istringstream iss1 (temp);
    iss1 >> n;
    std::vector <std::vector <int>> graph (n);
    std::vector <std::vector <int>> matrix (n);
    std::vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        std::getline(in, temp);
        std::istringstream iss (temp);
        while (iss >> x) {
            matrix[i].emplace_back(x);
        }
    }
    in.close();

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 1) {
                graph[i].emplace_back(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!graph[i].empty()) {
            for (int j = 0; j < graph[i].size(); ++j){
                ans[graph[i][j]] = i + 1;
            }
        }
    }

    for (const auto& i : ans) {
        out << i << ' ';
    }

    out.close();
    return 0;
}
