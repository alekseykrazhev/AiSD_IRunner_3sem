#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

void Bellman (std::vector<std::vector<int>>& a, std::vector<int>& group_1, std::vector<int>& group_2) {
    int n = std::max(group_1.size(), group_2.size());
    std::vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(n + 1, INT_MAX);
        std::vector<char> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INT_MAX, j1;
            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= n; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    std::cout << std::fixed << std::setprecision(1) << -v[0] / 2.0 << std::endl;
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

void build_matrix(std::vector<int>& group_1, std::vector<int>& group_2, std::vector<std::vector<int>>& a) {
    int n = std::max(group_1.size(), group_2.size());
    a.assign(n + 1, std::vector<int>());
    for (int i = 0; i < n; i++) {
        a[i + 1].assign(n + 1, 0);
        for (int j = 0; j < n; j++) {
            if (group_1.size() == n) {
                if (j >= group_2.size()) a[i + 1][j + 1] = group_1[i];
                else a[i + 1][j + 1] = 2 * abs(group_1[i] - group_2[j]);
            }
            else {
                if (j >= group_1.size()) a[i + 1][j + 1] = group_2[i];
                else a[i + 1][j + 1] = 2 * abs(group_1[j] - group_2[i]);
            }
        }
    }
}

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    std::vector<int> department1;
    std::vector<int> department2;
    std::vector<std::vector<int>> a;

    departmentFill(in, department1);
    departmentFill(in, department2);
    build_matrix(department1, department2, a);
    Bellman(a, department1, department2);

    return 0;
}
