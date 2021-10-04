#include <iostream>
#include <vector>

void fillArray (std::vector<std::vector<long long>>& ans, const int& n){
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
        ans[i][0] = 1;
    }
    int p = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j){
            ans[i][j] = (ans[i-1][j-1] + ans[i-1][j]) % 1000000007;
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<std::vector<long long>> ans (n + 1, std::vector<long long>(n + 1));
    fillArray(ans, n + 1);
    /*for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            std::cout << ans[i][j] << ' ';
        }
        std::cout << std::endl;
    }*/

    std::cout << ans[n][k];
    return 0;
}