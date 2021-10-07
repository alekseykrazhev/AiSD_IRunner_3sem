#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    if (!in.is_open()){
        std::cerr << "Error opening file" ;
        return -1;
    }

    int s, a, b;
    std::vector <int> vec;
    in >> s;
    for (int i = 0; i < s; ++i) {
        in >> a >> b;
        vec.push_back(a);
        vec.push_back(b);
    }
    std::vector<std::vector<int>> matrix;


    return 0;
}
