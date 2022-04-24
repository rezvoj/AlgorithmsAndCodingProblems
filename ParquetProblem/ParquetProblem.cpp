#include <cstddef>
#include <algorithm>
#define D(A, B) ((A)*a + (B))


size_t possibleParquetPatterns(size_t a, size_t b) {
	if (!a || !b || (a*b)%2) {
		return 0;
	}
	if (a < b) {
		std::swap(a, b);
	}
	size_t h = 1 << b; 
	size_t* dp = new size_t[a * h]; std::fill(dp, dp + (a * h), 0); 
	auto genMaskReach_ = [a, b, dp](
			auto& gmr_,
			const size_t prevMask,
			size_t nextMask,
			const size_t idx,
			const size_t row) -> void {
		for (size_t i = idx; i < b; ++i) {
			if (prevMask & (1 << i)) {
				continue;
			}
			if (((i + 1) < b) && !(prevMask & (1 << (i + 1)))) {
				gmr_(gmr_, prevMask, nextMask, i + 2, row);
			}
			nextMask |= (1 << i);
		}
		dp[D(nextMask, row)] += (row ? dp[D(prevMask, row - 1)] : 1);
	}; 
	genMaskReach_(genMaskReach_, 0, 0, 0, 0);
	for (size_t i = 1; i < a; ++i) {
		for (size_t j = 0; j < h; ++j) {
			if (dp[D(j, i - 1)]) genMaskReach_(genMaskReach_, j, 0, 0, i);
		}
	}
	size_t ret = dp[D(0, a - 1)]; 
	delete[] dp; 
	return ret;
}
