#include <limits>
#include <algorithm>
#include <unordered_map>
#include "DjikstraShortestPath.hpp"
#define Inf std::numeric_limits<double>::infinity()



template <typename Idx, typename Prio>
class IPQ {
public:
	using Duo = std::pair<Idx, Prio>;
	using Heap = std::vector<Duo>;
	using Htable = std::unordered_map<Idx, size_t>;

private:
	size_t m_size;
	const bool m_minHeap;
	Heap m_heap;
	Htable m_table;

private:
	void m_swap(const size_t& posA, const size_t& posB) {
		m_table[m_heap[posA].first] = posB;
		m_table[m_heap[posB].first] = posA;
		std::swap(m_heap[posA], m_heap[posB]);
	}

	void m_rebalanceDown(size_t pos) {
		while ((2*pos + 2) < m_heap.size()) {
			if ((m_heap[2*pos + 1].second > m_heap[pos].second) ^ m_minHeap 
					&& (m_heap[2*pos + 1].second > m_heap[2*pos + 2].second) ^ m_minHeap) {
				m_swap(pos, 2*pos + 1); 
				pos = 2*pos + 1;
			}
			else if ((m_heap[2*pos + 2].second > m_heap[pos].second) ^ m_minHeap) {
				m_swap(pos, 2*pos + 2); 
				pos = 2*pos + 2;
			} 
			else return;
		}
		if ((2*pos + 1) < m_heap.size() 
				&& (m_heap[2*pos + 1].second > m_heap[pos].second) ^ m_minHeap) {
			m_swap(pos, 2*pos + 1);
		}
	}

	void m_rebalanceUp(size_t pos) {
		if (!pos) {
			return;
		}
		for (; pos; pos = (pos - 1)/2) {
			if ((m_heap[(pos - 1)/2].second < m_heap[pos].second) ^ m_minHeap) {
				m_swap(pos, (pos - 1)/2);
			}
			else return;			
		}
	}

public:
	IPQ(const size_t& bcnt, const bool& minheap = true) : 
		m_size(0), m_minHeap(minheap), m_heap(Heap()), m_table(bcnt) {}

	Duo pollTop() {
		if (!m_size) {
			return Duo();
		}
		m_size--;
		Duo saved = m_heap[0];
		m_swap(0, m_heap.size() - 1);
		m_table.erase(m_heap.back().first);
		m_heap.pop_back();
		if (m_size) {
			m_rebalanceDown(0);
		}
		return saved;
	}

	void add(const Idx& idx, const Prio& prio) {
		auto it = m_table.find(idx);
		if (it == m_table.end()) {
			m_table[idx] = m_heap.size();
			m_heap.push_back({idx, prio});
			m_rebalanceUp(m_heap.size() - 1);
			m_size++; 
			if (m_table.bucket_count() <= m_size) {
				m_table.rehash(m_size*3);
			}
			return;
		} 
		Prio prev = m_heap[it->second].second;
		m_heap[it->second].second = prio;
		if ((prev > prio) ^ m_minHeap) {
			m_rebalanceDown(it->second);
		}
		else {
			m_rebalanceUp(it->second);
		}
	}

	bool addConditional(const Idx& idx, const Prio& prio) {
		auto it = m_table.find(idx);
		if (it == m_table.end()) {
			m_table[idx] = m_heap.size();
			m_heap.push_back({idx, prio});
			m_rebalanceUp(m_heap.size() - 1); 
			m_size++;
			if (m_table.bucket_count() <= m_size) {
				m_table.rehash(m_size*3);
			}
			return true;
		}
		if ((m_heap[it->second].second > prio) ^ m_minHeap) {
			return false;
		}
		m_heap[it->second].second = prio;
		m_rebalanceUp(it->second);
		return true;
	}
	
	size_t size() const {
		return m_size;
	}

};


std::vector<double> DjikstraSSSP(const OutgoingEdgesList& oel, const size_t& idx) {
	std::vector<double> ret(oel.size(), Inf);
	IPQ<size_t, double> ipq(oel.size());
	if (oel.size()) {
		ipq.add(idx, 0);
	}
	while (ipq.size()) {
		auto top = ipq.pollTop();
		ret[top.first] = top.second;
		for (const auto& pair : oel[top.first]) {
			if (ret[pair.second] != Inf) {
				continue;
			}
			ipq.addConditional(pair.second, pair.first + top.second);
		}
	} 
	return ret;
}
