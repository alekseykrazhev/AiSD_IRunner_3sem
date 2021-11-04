#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>

void add_to_black_box(const int& now, std::priority_queue<int, std::vector<int>>& max_heap,
                      std::priority_queue<int, std::vector<int>, std::greater<>>& min_heap){
    if (max_heap.top() > now) {
        min_heap.push(max_heap.top());
        max_heap.pop();
        max_heap.push(now);
    } else {
        min_heap.push(now);
    }
}

int main() {
    std::priority_queue<int, std::vector<int>> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
    std::vector<int> add, get;

    std::ifstream in ("input.txt");
    std::ofstream out("output.txt");

    std::string temp;
    std::getline(in, temp);
    std::getline(in, temp);
    std::istringstream iss(temp);
    int numb;
    while (iss >> numb){
        add.emplace_back(numb);
    }
    std::getline(in, temp);
    in.close();
    std::istringstream is(temp);
    while (is >> numb){
        get.emplace_back(numb);
    }

    int get_count = 0;
    for (int i = 0; i < get.size(); ++i){
        if (min_heap.empty()) {
            max_heap.push(add[get_count]);
            ++get_count;
        } else {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }

        while (get_count != get[i]){
            add_to_black_box(add[get_count], max_heap, min_heap);
            ++get_count;
        }

        out << max_heap.top();
        if (i != get.size() - 1){
            out << ' ';
        }
    }
    return 0;
}