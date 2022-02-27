#pragma once
#include <cstddef>
#include <vector>
#include <list>

struct Edge {size_t from, to;};
using Edges = std::list<Edge>;
using EdgeDependencies = std::vector<std::list<size_t>>;

EdgeDependencies graphDependency(const Edges& edges, size_t graphSize);
