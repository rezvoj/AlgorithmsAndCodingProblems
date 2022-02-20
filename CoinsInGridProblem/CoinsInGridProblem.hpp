#pragma once
#include <cstddef>
#include <vector>

struct Cords {size_t y, x;
	bool operator==(const Cords& b) const {
		return this->x == b.x && this->y == b.y;
	}
};
using Grid = std::vector<std::vector<int>>;
using Path = std::vector<Cords>;

Grid coinsDpGrid(const Grid& grid);
Path getPath(const Grid& dpGrid);
