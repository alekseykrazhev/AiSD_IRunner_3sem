#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long n, p;
    std::cin >> n >> p;
    std::vector<long long> arr, ans;

    long long temp;
    for (int i = 0; i < n; ++i) {
        std::cin >> temp;
        arr.emplace_back(temp);
    }

    char q;
    long long x, y;
    for (long long i = 0; i < p; ++i) {
        std::cin >> q;
        std::cin.ignore();
        std::cin >> x >> y;
        if (q == '='){
            arr[x-1] = y;
        }
        if (q == '?'){
            std::vector<long long> copy = arr;
            std::sort(copy.begin() + x-1, copy.begin() + y);
            long long an = copy[y-1] * copy[y-2];
            if (copy[x-1] < 0 && copy[x] < 0){
                long long a = copy[x] * copy[x-1];
                an = std::max(a, an);
            }
            ans.emplace_back(an);
        }
    }

    for (auto& i : ans){
        std::cout << i << '\n';
    }
    return 0;
}
