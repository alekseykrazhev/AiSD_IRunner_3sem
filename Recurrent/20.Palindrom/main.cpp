#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::string ans;

void FillDiagonal (std::vector<std::vector<int>>& vec, const int& size, const std::string& str) {
    for (int i = 0; i < size; ++i) {
        vec[i][i] = 1;
    }
    for (int i = 0; i < size - 1; ++i) {
        if (str[i] == str[i+1]) {
            vec[i][i+1] = 2;
        } else if (str[i] != str[i+1]) {
            vec[i][i+1] = 1;
        }
    }
    int l = 2;
    for (int k = 0; k < size - 2; ++k) {
        for (int j = l, i = 0; i < size - l; ++j, ++i) {
            if (str[i] == str[j]) {
                vec[i][j] = vec[i + 1][j - 1] + 2;
            }
            if (str[i] != str[j]) {
                vec[i][j] = std::max(vec[i+1][j], vec[i][j-1]);
            }
        }
        ++l;
    }
}

void FindPalyndrom (const std::vector<std::vector<int>>& vec, const int& i, const int& j, const std::string& str) {
    if (i > j) {
        return;
    }
    if (str[i] == str[j]) {
        ans += str[i];
    }
    //vec[i][j - 1] == vec[i+1][j-1]  && vec[i+1][j-1] == vec[i+1][j]
    if (str[i] == str[j]) {
        return FindPalyndrom(vec, i+1, j-1, str);
    }
    int m = std::max(vec[i][j-1], vec[i+1][j-1]);
    int max = std::max(m, vec[i+1][j]);
    if (vec[i+1][j] == max)
        return FindPalyndrom(vec, i+1, j, str);
    if (vec[i][j-1] == max)
        return FindPalyndrom(vec, i, j-1, str);
    /*if (vec[i+1][j-1] == max)
        return FindPalyndrom(vec,i+1, j-1, str);*/
}

int main() {
    std::ifstream in (R"(C:\Users\Alex\Desktop\AiSD_irunner_3sem\Recurrent\20.Palindrom\input.txt)");
    std::ofstream out (R"(C:\Users\Alex\Desktop\AiSD_irunner_3sem\Recurrent\20.Palindrom\output.txt)");

    if (!in.is_open()) {
        std::cerr << "Error opening file!";
        return -1;
    }

    std::string str;
    std::getline(in, str);
    in.close();
    int size = str.length();
    std::vector<std::vector<int>> vec (size, std::vector<int> (size));
    FillDiagonal(vec, size, str);
    int ans_size = vec[0][size-1];
    out << ans_size << '\n';
    FindPalyndrom(vec, 0, size - 1, str);
    int count = ans.length();
    if (ans_size % 2 == 0) {
        for (int i = count - 1; i >= 0; --i) {
            ans += ans[i];
        }
    } else {
        for (int i = count - 2; i >= 0; --i) {
            ans += ans[i];
        }
    }
    out << ans;
    return 0;
}
