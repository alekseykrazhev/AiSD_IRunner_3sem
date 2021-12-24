#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

const int MAXN = 25; // число вершин
const int INF = 1000000000; // константа-бесконечность

int n, c[MAXN][MAXN], f[MAXN][MAXN], s, t, d[MAXN], ptr[MAXN], q[MAXN];

bool bfs() {
    int qh=0, qt=0;
    q[qt++] = s;
    memset (d, -1, n * sizeof d[0]);
    d[s] = 0;
    while (qh < qt) {
        int v = q[qh++];
        for (int to=0; to<n; ++to)
            if (d[to] == -1 && f[v][to] < c[v][to]) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
    }
    return d[t] != -1;
}

int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (int & to=ptr[v]; to<n; ++to) {
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, std::min (flow, c[v][to] - f[v][to]));
        if (pushed) {
            f[v][to] += pushed;
            f[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic() {
    int flow = 0;
    for (;;) {
        if (!bfs())  break;
        memset (ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs (s, INF))
            flow += pushed;
    }
    return flow;
}

void departmentFill (std::ifstream& in, std::vector<int>& dep) {
    std::string numb;
    int temp;
    std::getline(in, numb);
    std::istringstream iss (numb);
    while (iss >> temp) {
        dep.emplace_back(temp);
    }
}

void resize_matrix(std::vector<std::vector<double>> &matrix, const unsigned int& n){
    matrix.resize(n);
    for (auto& i : matrix) {
        for (int j = 0; j < n; ++j) {
            i.push_back(0);
        }
    }
}

void create_cost_matrix(std::vector<int>& group_1, std::vector<int>& group_2, std::vector<std::vector<double>>& a, const unsigned int&n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (group_1.size() == n) {
                if (group_2.size() <= j) {
                    a[i][j] = group_1[i];
                } else {
                    a[i][j] = abs(group_1[i] - group_2[j]) * 2;
                }
            }
            else {
                if (group_1.size() <= j) {
                    a[i][j] = group_2[i];
                } else {
                    a[i][j] = abs(group_1[j] - group_2[i]) * 2;
                }
            }
        }
    }
}

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    std::vector<int> department1;
    std::vector<int> department2;
    std::vector<std::vector<double>> a;
    std::vector<int> a1;

    departmentFill(in, department1);
    departmentFill(in, department2);
    in.close();

    unsigned int max_size = std::max(department1.size(), department2.size());
    resize_matrix(a, max_size);
    create_cost_matrix(department1, department2, a, max_size);
    /*
    for (const auto& i : a) {
        for (auto j : i){
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }*/
    double ans = dinic();
    ans /= 2;
    out << std::fixed << std::setprecision(1) << ans;
    out.close();
    return 0;
}
