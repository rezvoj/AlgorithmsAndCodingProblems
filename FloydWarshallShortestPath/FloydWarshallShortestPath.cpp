#include <limits>
#include <algorithm>
#include "FloydWarshallShortestPath.hpp"
#define Inf std::numeric_limits<double>::infinity()


AdjacencyMatrix Floyd_WarshalAPSP(AdjacencyMatrix prev) {
	AdjacencyMatrix top(prev.size());
	for (size_t i = 0; i < prev.size(); ++i) {
		for (size_t j = 0; j < prev.size(); ++j) {
			for (size_t k = 0; k < prev.size(); ++k) {
				top[j][k] = std::min(prev[j][k], prev[j][i] + prev[i][k]);
			}
		}
		std::swap(top, prev);
	}
	for (size_t i = 0; i < prev.size(); ++i) {
		if (prev[i][i] >= 0) {
			continue;
		}			
		for (size_t j = 0; j < prev.size(); ++j) {
			for (size_t k = 0; k < prev.size(); ++k) {
				if ((prev[j][i] != Inf) && (prev[i][k] != Inf)) {
					prev[j][k] = -Inf;
				}
			}
		}
	} 
	return prev;
}
