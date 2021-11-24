#include <iostream>
#include <fstream>


int main(){
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    int n, m;
    int x, y;
    in >> n >> m;
    int** graph = new int*[n];
    for(int i = 0; i < n; i++)
        graph[i] = new int[n];

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        in >> x >> y;
        graph[x-1][y-1] = 1;
        graph[y-1][x-1] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << graph[i][j] << ' ';
        }
        if (i != n-1) out << '\n';
    }

    delete[] graph;
    return 0;
}