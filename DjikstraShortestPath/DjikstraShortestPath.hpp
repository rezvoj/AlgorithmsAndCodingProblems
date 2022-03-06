#pragma once
#include <cstddef>
#include <vector>

using OutgoingEdge = std::vector<std::pair<double, size_t>>;
using OutgoingEdgesList = std::vector<OutgoingEdge>;

std::vector<double> DjikstraSSSP(const OutgoingEdgesList& oel, const size_t& idx);
