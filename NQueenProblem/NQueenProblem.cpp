#include <set>
#include <stack>
#include "NQueenProblem.hpp" 



struct cords {
	size_t x, y;
};


Solutions nQueen(const size_t& dim) {
	std::vector<size_t> board(dim*dim, 0);
	std::vector<size_t> current; 
	current.reserve(dim);
	std::stack<std::pair<cords, bool>> stack;
	Solutions solutions;
	for (size_t i = 0; i < dim; ++i) {
		stack.push({{0, i}, true});
	}
	while (!stack.empty()) {
		if (!stack.top().second) {
			for (size_t i = 1; i + stack.top().first.x < dim; ++i) {
				board[stack.top().first.y*dim + i + stack.top().first.x]--;
				if (stack.top().first.y + i < dim) { 
					board[(stack.top().first.y + i)*dim + i + stack.top().first.x]--;
				}
				if (stack.top().first.y >= i) { 
					board[(stack.top().first.y - i)*dim + i + stack.top().first.x]--;
				}
			}
			current.pop_back(); 
			stack.pop();
		}
		else {
			for (size_t i = 1; i + stack.top().first.x < dim; ++i) {
				board[stack.top().first.y*dim + i + stack.top().first.x]++;
				if (stack.top().first.y + i < dim) {
					board[(stack.top().first.y + i)*dim + i + stack.top().first.x]++;
				}
				if (stack.top().first.y >= i) {
					board[(stack.top().first.y - i)*dim + i + stack.top().first.x]++;
				}
			}
			current.push_back(stack.top().first.y); 
			stack.top().second = false;
			if (dim - 1 == stack.top().first.x) {
				solutions.push_back(current);
			}
			else {
				for (size_t cx = stack.top().first.x, i = 0; i < dim; ++i) { 
					if (!board[i*dim + cx + 1]) { 
						stack.push({{cx + 1, i}, true});
					}
				}
			}
		}
	}
	return solutions;
}


Solutions getDistinct(const Solutions& sols) {
	std::set<std::vector<size_t>> distinct;
	for (const auto& sol : sols) {
		bool dist = true;
		Solutions rots(4, sol);
		for (size_t i = 0; i < sol.size(); ++i) {
			rots[1][(sol.size() - 1) - sol[i]] = i;
		}
		for (size_t i = 0; i < sol.size(); ++i) {
			rots[2][sol[i]] = (sol.size() - 1) - i;
		}
		for (size_t i = 0; i < sol.size(); ++i) {
			rots[3][i] = (sol.size() - 1) - sol[(sol.size() - 1) - i];
		}
		for (const auto& rot : rots) {
			std::vector<size_t> mir(sol.size());
			for (size_t i = 0; i < sol.size(); ++i) {
				mir[i] = rot[(sol.size() - 1) - i];
			}
			if (distinct.find(rot) != distinct.end() || distinct.find(mir) != distinct.end()) {
				dist = false; 
				break;
			}
		} 
		if (dist) {
			distinct.insert(sol);
		}
	}
	Solutions ret;
	for (const auto& sol : distinct) {
		ret.push_back(sol);
	}
	return ret;
}
