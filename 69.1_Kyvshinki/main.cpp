#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void FindMaxWay (const std::vector<int>& vec, std::vector<int>& sums) {
    for (int i = 0; i < vec.size() - 2; ++i) {
        if (sums[i] == -1) {
            continue;
        }
        sums[i + 2] = std::max(vec[i + 2] + sums[i], sums[i + 2]);
        if (i < vec.size() - 3) {
            sums[i + 3] = std::max(vec[i + 3] + sums[i], sums[i + 3]);
        }
    }
}

int main() {
    std::ifstream in (R"(input.txt)");
    std::ofstream out (R"(output.txt)");

    int n, a;
    in >> n;
    std::vector<int> vec, sums;
    while (in >> a) {
        vec.push_back(a);
        sums.push_back(a);
    }
    sums[1] = -1; 
    FindMaxWay(vec, sums);
    out << sums[n - 1];
    return 0;
}