#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>


struct Disk{
    double coordinate;
    double radius;
};


int main() {
    std::ifstream in ("in.txt");
    std::ofstream out ("out.txt");

    int n;
    double ans = 0.0;
    double temp;
    std::vector<double> rad;
    std::vector<Disk> disks;
    in >> n;

    if (n == 0) {
        out << "0.00000";
        out.close();
        return 0;
    }

    while (in >> temp) {
        rad.emplace_back(temp);
        Disk numb{};
        numb.radius = temp;
        disks.emplace_back(numb);
    }
    in.close();

    disks[0].coordinate = disks[0].radius;
    double pr_ans = 0.0;
    for (int i = 1; i < disks.size(); ++i) {
        pr_ans = ans;
        double maximum = disks[i].radius;
        for (int j = 0; j < i; ++j) {
            double max_check = 2 * sqrt(disks[i].radius * disks[j].radius) + disks[j].coordinate;
            if (max_check > maximum) {
                maximum = max_check;
            }
        }
        disks[i].coordinate = maximum;
        ans = std::max(pr_ans, disks[i].radius + disks[i].coordinate);
        //std::cout << maximum << ' ';
    }
    if (n == 1) {
        ans = disks[0].radius * 2;
    }
    //ans = std::max(disks[n-1].radius + disks[n-1].coordinate, disks[n-2].radius + disks[n-2].coordinate);
    /*
    double first, last;

    for (int i = 1; i < rad.size(); ++i) {
        ans += 2 * sqrt(rad[i] * rad[i - 1]);
        if (i == 1) {
            first = ans;
        }
        if (i == rad.size() - 1) {
            last = 2 * sqrt(rad[i] * rad[i - 1]);
        }
    }

    if (rad.size() == 1) {
        out << std::fixed << std::setprecision(5) << rad[0];
        out.close();
        return 0;
    }
    if (rad.size() > 1) {
        ans += rad[0] + rad[n - 1];
    } else {
        ans += std::max (rad[0], rad[1] - first) + std::max(rad[n-1], rad[n-2] - last);
    }
    */
    out << std::fixed << std::setprecision(5) << ans;
    out.close();
    return 0;
}
