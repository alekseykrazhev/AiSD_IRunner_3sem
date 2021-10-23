#include <iostream>
#include <vector>

int BinarySearch (const std::vector<int>& mas, const int& search) {
    int beg = 0, end = mas.size();

    while (beg < end) {
        int middle = (beg + end) / 2;
        if (mas[middle] == search) {
            return 1;
        } else if (mas[middle] > search) {
            end = middle;
        } else {
            beg = middle + 1;
        }
    }

    return 0;
}

int FindUpperOrSame (const std::vector<int>& mas, const int& search) {
    int beg = 0, end = mas.size();

    while (beg < end) {
        int middle = (beg + end) / 2;
        if (search <= mas[middle]) {
            end = middle;
        } else {
            beg = middle + 1;
        }
    }

    return beg;
}

int FindUpper (const std::vector<int>& mas, const int& search) {
    int beg = 0, end = mas.size();

    while (beg < end) {
        int middle = (beg + end) / 2;
        if (search < mas[middle]) {
            end = middle;
        } else {
            beg = middle + 1;
        }
    }

    return beg;
}

int main() {
    int n, k, b;
    std::vector <int> mas, ask, ans;
    int count = 0;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        mas.push_back(a);
    }
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int a;
        std::cin >> a;
        ask.push_back(a);
    }
    
    for (int i = 0; i < ask.size(); ++i){
        ans.push_back(BinarySearch(mas, ask[i]));
        ans.push_back(FindUpperOrSame(mas, ask[i]));
        ans.push_back(FindUpper(mas, ask[i]));
    }

    for (int i : ans){
        ++count;
        std::cout << i;
        if (count % 3 != 0) {
            std::cout << ' ';
        }
        if (count % 3 == 0) {
            std::cout << '\n';
        }
    }
    return 0;
}