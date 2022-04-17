#pragma once
#include <vector>
#include <cstddef>

struct Brick {double a, b, c;};
using Brickdex = std::pair<double, size_t>;
using Bricks = std::vector<Brick>;

Bricks towerOfBricks(const Bricks& initBricks);
double getTowerHeigth(const Bricks& tower);
