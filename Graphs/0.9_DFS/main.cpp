#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>

std::vector < std::vector<int> > graph;
std::vector <bool> used;
std::vector <int> marks;
int n;
int count = 1;

void dfs (int v, bool flag = false) {
    used[v] = true;
    if (flag) {
        marks[v] = count;
        ++count;
    }
    std::sort(graph[v].begin(), graph[v].end());
    for (int & i : graph[v])
        if (!used[i]) {
            marks[i] = count;
            ++count;
            dfs(i);
        }
}

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int temp;
    std::string numb;
    std::getline(in, numb);
    std::istringstream iss1 (numb);
    iss1 >> n;
    graph.resize(n);
    marks.resize(n);
    used.resize(n, false);
    std::vector<std::vector<int>> matrix(n);

    for (int i = 0; i < n; ++i) {
        std::getline(in, numb);
        std::istringstream iss (numb);
        while (iss >> temp) matrix[i].emplace_back(temp);
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 1) {
                graph[i].emplace_back(j);
            }
        }
    }

    dfs(0, true);
    for (int i = 0; i < used.size(); ++i) {
        if (!used[i]) {
            dfs(i, true);
        }
    }
    //marks[n-1] = count;
    for (const auto& i : marks) {
        out << i << ' ';
    }

    return 0;
}
