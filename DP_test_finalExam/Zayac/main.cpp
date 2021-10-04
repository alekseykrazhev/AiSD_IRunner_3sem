#include <iostream>
#include <fstream>

long long fib[10000010];

int main () {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");
    long n;
    in >> n;
    in.close();
    fib[0] = fib[1] = 1;

    for (int i = 2; i < n + 1; ++i) {
        fib[i] = (fib[i - 2] + fib[i - 1]) % 1000000007;
    }
    
    out << fib[n];
    out.close();
    return 0;
}