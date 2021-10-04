#include <iostream>
#include <fstream>
#include <set>
#include <numeric>

int main() {
    std::ifstream in (R"(input.txt)");
    std::ofstream out (R"(output.txt)");
    long long a;
    std::set<long long> set;

    if (!in.is_open()){
        std::cerr << "Error opening file";
        return 1;
    }

    while (in >> a){
        set.insert(a);
    }

    in.close();
    long long sum = 0;
    for (long long i : set){
        sum += i;
    }
    out << sum;
    out.close();
    return 0;
}