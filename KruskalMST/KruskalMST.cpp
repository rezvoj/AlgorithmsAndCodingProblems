#include <algorithm>
#include <stack>
#include "KruskalMST.hpp"



class DSU {
private:
	std::vector<size_t> m_parents;
	std::vector<size_t> m_sizes;
	size_t m_size;

public:
	DSU(const size_t& size) : m_size(size) {
		m_parents = std::vector<size_t>(size);
		for (size_t i = 0; i < size; ++i) {
			m_parents[i] = i;
		}
		m_sizes = std::vector<size_t>(size, 1);
	}

	size_t findSet(const size_t& idx) {
		std::stack<size_t> idxes;
		idxes.push(idx);
		for (; m_parents[idxes.top()] != idxes.top(); idxes.push(m_parents[idxes.top()]));
		size_t parent = idxes.top();
		idxes.pop();
		for (; !idxes.empty(); m_parents[idxes.top()] = parent, idxes.pop());
		return parent;
	}

	bool unionSets(const size_t& idx1, const size_t& idx2) {
		size_t p1 = findSet(idx1), p2 = findSet(idx2);
		if (p1 == p2) {
			return false;
		}
		size_t max = (m_sizes[p1] > m_sizes[p2]) ? p1 : p2;
		size_t min = (max == p1) ? p2 : p1;
		m_sizes[max] += m_sizes[min];
		m_parents[min] = max;
		m_size--;
		return true;
	}

	size_t size() const {
		return m_size;
	}

};


UnorderedEdgeList kruskalMST(UnorderedEdgeList edges, const size_t& nodeRange) {
	std::sort(edges.begin(), edges.end(), [](auto& a, auto& b) {return a.b < b.b;});
	UnorderedEdgeList mst;
	mst.reserve(nodeRange);
	DSU dsu(nodeRange);
	for (const auto& edge : edges) {
		size_t p1 = dsu.findSet(edge.a); 
		size_t p2 = dsu.findSet(edge.c);
		if (p1 == p2) {
			continue;
		}
		mst.push_back(edge);
		dsu.unionSets(p1, p2);
		if (dsu.size() <= 1) {
			break;
		}
	}
	return mst;
}
