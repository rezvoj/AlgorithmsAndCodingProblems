#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


inline double get_distance(double a, double b) {
    return sqrt((a + b)*(a + b) - (a - b)*(a - b));
}

double get_sum(const std::vector<double>& vec) {    
    if (vec.empty()) return 0;
    double max;
    std::vector<double> cords(vec.size(), 0);
    cords[0] = vec[0];
    for (size_t i = 1; i < vec.size(); i++) {
        max = 0;
        for (size_t j = 0; j < i; j++)
            max = std::max(max, get_distance(vec[i], vec[j]) + cords[j]);
        cords[i] = std::max(max, vec[i]);
    }
    max = 0;
    for (size_t i = 0; i < vec.size(); i++)
        max = std::max(max, cords[i] + vec[i]);
    return max;
}


int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;
    for (int _ = 0; _ < n; ++_) {
        int len;
        std::cin >> len;
        std::vector<double> data(len);
        for (int j = 0; j < len; ++j)
            std::cin >> data[j];
        std::sort(data.begin(), data.end());
        double min = get_sum(data);
        while(std::next_permutation(data.begin(), data.end()))
            min = std::min(min, get_sum(data));
        printf("%.3f\n", min);
    }
    return 0;
}
