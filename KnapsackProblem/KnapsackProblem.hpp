#pragma once
#include <cstddef>
#include <vector>

using Items = std::vector<std::pair<double, size_t>>;
Items knapsackDP(const Items& items, const size_t& size);
