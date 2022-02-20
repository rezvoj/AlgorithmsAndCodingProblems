#include "CoinsInGridProblem.hpp"



Grid coinsDpGrid(const Grid& grid) {
	if (grid.size() == 0 || grid[0].size() == 0) {
		return Grid();
	}
	const size_t H = grid.size(); 
	const size_t W = grid[0].size();
	Grid dp(H, std::vector<int>(W, 0));
	dp[H - 1][W - 1] = grid[H - 1][W - 1];
	for (long i = W - 2; i >= 0; --i) {
		dp[H - 1][i] = dp[H - 1][i + 1] + grid[H - 1][i];
	}
	for (long i = H - 2; i >= 0; --i) {
		for (long j = W - 1; j >= 0; --j) {
			if (j < ((long)(W - 1)) && (dp[i][j + 1] > dp[i + 1][j])) {
				dp[i][j] = dp[i][j + 1] + grid[i][j];
			}
			else {
				dp[i][j] = dp[i + 1][j] + grid[i][j];
			}
		}
	}
	return dp;
}


Path getPath(const Grid& dpGrid) {
	Path ret;
	if (dpGrid.size() == 0 || dpGrid[0].size() == 0) {
		return ret;
	}
	const size_t H = dpGrid.size(); 
	const size_t W = dpGrid[0].size();
	for (size_t x = 0, y = 0, i = 0; i < (H + W - 1); i++) {
		ret.push_back(Cords{y, x});
		if ((x + 1) >= W) {
			y++;
		}
		else if ((y + 1) >= H || dpGrid[y][x + 1] > dpGrid[y + 1][x]) {
			x++;
		}
		else {
			y++;
		}
	} 
	return ret;
}
