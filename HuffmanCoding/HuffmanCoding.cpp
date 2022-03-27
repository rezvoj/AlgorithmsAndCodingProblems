#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "HuffmanCoding.hpp"



template <typename Value, typename Prio>
class PriorityQueue {
public:
	using Duo = std::pair<Value, Prio>;
	using Heap = std::vector<Duo>;

private:
	size_t m_size;
	const bool m_minHeap;
	Heap m_heap;

private:
	void m_swap(const size_t& posA, const size_t& posB) {
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
	PriorityQueue(const bool& minheap = true): 
		m_size(0), m_minHeap(minheap), m_heap(Heap()) {}

	Duo pollTop() {
		if (!m_size) {
			return Duo();
		}
		m_size--;
		Duo saved = m_heap[0];
		m_swap(0, m_heap.size() - 1);
		m_heap.pop_back();
		if (m_size) {
			m_rebalanceDown(0);
		}
		return saved;
	}

	void add(const Value& val, const Prio& prio) {
		m_size++;
		m_heap.push_back({val, prio});
		m_rebalanceUp(m_heap.size() - 1);
		return;
	}

	size_t size() const {
		return m_size;
	}

};


struct HuffmanNode {
	HuffmanNode *lc, *rc;
	byte content;
	HuffmanNode(const byte& b) : lc(nullptr), rc(nullptr), content(b) {}
	HuffmanNode(HuffmanNode* l, HuffmanNode* r, const byte& b) : lc(l), rc(r), content(b) {}
};


HuffMap huffmanCoding(const std::string& str) {
	std::unordered_map<byte, size_t> hmap(255);
	for (const auto& cr : str) {
		hmap[cr] = (hmap.find(cr) == hmap.end()) ? 1 : hmap[cr] + 1;
	}
	if (hmap.size() == 0) {
		return HuffMap(0);
	}
	if (hmap.size() == 1) {
		HuffMap hfr(1); 
		hfr[hmap.begin()->first] = std::vector<bool>(1, false); 
		return hfr;
	}
	size_t nodeCount = hmap.size();
	PriorityQueue<HuffmanNode*, size_t> pq;
	for (const auto& elem : hmap) {
		pq.add(new HuffmanNode(elem.first), elem.second);
	}
	while (pq.size() > 1) {
		auto low = pq.pollTop();
		auto high = pq.pollTop();
		pq.add(new HuffmanNode(low.first, high.first, 0), low.second + high.second);
	}
	HuffMap huffmap(nodeCount);
	std::vector<bool> direction;
	std::stack<HuffmanNode*> nstk; 
	nstk.push(pq.pollTop().first);
	while (!nstk.empty()) {
		while (nstk.top()->lc || nstk.top()->rc) {
			if (nstk.top()->lc) {
				direction.push_back(false); 
				nstk.push(nstk.top()->lc);	
			} 
			else {
				direction.push_back(true); 
				nstk.push(nstk.top()->rc);
			}
		} 
		huffmap[nstk.top()->content] = direction;
		auto prev = nstk.top();
		for (nstk.pop(); !nstk.empty(); prev = nstk.top(), nstk.pop()) {
			direction.pop_back();
			delete prev;
			(nstk.top()->lc == prev) ? nstk.top()->lc = nullptr : nstk.top()->rc = nullptr;
			if (nstk.top()->lc != nullptr || nstk.top()->rc != nullptr) {
				break;
			}
		} 
		if (nstk.empty()) {
			delete prev;
		}
	} 
	return huffmap;
}
