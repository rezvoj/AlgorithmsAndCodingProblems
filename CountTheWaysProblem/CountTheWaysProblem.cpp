#include <iostream>
#include <array>

using DP = std::array<std::array<long, 30001>, 5>;
constexpr std::array<int, 5> dec_arr = {1, 5, 10, 25, 50};


long dp_rec(DP& dp, int y, int x) {
    if ((x < 0) || (y >= 5)) {
        return 0;
    }
    if (dp[y][x] > -1) {
        return dp[y][x];
    }
    dp[y][x] = dp_rec(dp, y, x - dec_arr[y]) + dp_rec(dp, y + 1, x);
    return dp[y][x];
}


int main(int argc, char const *argv[]) {
    DP dp;
    for (auto& arr : dp) {
        std::fill(arr.begin(), arr.end(), -1LL);
        arr[0] = 1LL;
    }
    int num;
    while (std::cin >> num) {
        long ways = dp_rec(dp, 0, num);
        if (ways > 1LL) {
            std::printf("There are %lld ways to produce %d cents change.\n", ways, num);
        }
        else {
            std::printf("There is only 1 way to produce %d cents change.\n", num);
        }
    }
    return 0;
}
