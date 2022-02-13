#include <stack>
#include <algorithm>
#include <utility>
#include "KnapsackProblem.hpp"
#define D(A, B) ((A)*(ksc + 1) + (B))


Items knapsackDP(const Items& items, const size_t& ksc) {
	double* dp = new double[(items.size() + 1)*(ksc + 1)];
	for (size_t i = 0; i < items.size() + 1; ++i) {
		dp[D(i, 0)] = 0;
	}
	std::fill(dp, dp + ksc + 1, 0);
	for (size_t i = 1; i < items.size() + 1; ++i) {
		for (size_t j = 1; j < ksc + 1; ++j) {
			if (items[i - 1].second <= j && dp[D(i - 1, j)] < (dp[D(i - 1, j - items[i - 1].second)] + items[i - 1].first)) {
				dp[D(i, j)] = dp[D(i - 1, j - items[i - 1].second)] + items[i - 1].first;
			}
			else {
				dp[D(i, j)] = dp[D(i - 1, j)];
			}
		}
	} 
	Items ret;
	for (size_t x = ksc, y = items.size(); y > 0; --y) {
		if (dp[D(y - 1, x)] == dp[D(y, x)]) {
			continue;
		}
		x -= items[y - 1].second; 
		ret.push_back(items[y - 1]);
	} 
	delete[] dp; 
	return ret;
}
