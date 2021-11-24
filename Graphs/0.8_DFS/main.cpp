#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>

std::vector < std::vector<int> > graph;
std::vector<bool> used;
std::vector <int> marks;
int n;
int count = 1;
void BFS(int s) {
    std::queue<int> q;
    q.push (s);
    used.resize(n, false);
    std::vector<int> d (n), p (n);
    used[s] = true;
    marks[s] = count;
    ++count;

    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std::sort(graph[v].begin(), graph[v].end());
        for (size_t i=0; i<graph[v].size(); ++i) {
            int to = graph[v][i];
            if (!used[to]) {
                marks[to] = count;
                ++count;
                used[to] = true;
                q.push (to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
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

    BFS(0);
    for (int i = 0; i < used.size(); ++i) {
        if (!used[i]) {
            BFS(i);
        }
    }
    //marks[n-1] = count;
    for (const auto& i : marks) {
        out << i << ' ';
    }

    return 0;
}
