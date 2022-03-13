#pragma once
#include <initializer_list>


class AdjacencyMatrix {
public:
	class Row {
	private:
		double* m_data;
		size_t m_size;
	public:
		Row(double* data, const size_t& size) : m_data(data), m_size(size) {}
		double* begin() {return m_data;}
		double* end() {return m_data + m_size;}
		double& operator[](const size_t& idx) {return *(m_data + idx);}
		double operator[](const size_t& idx) const {return *(m_data + idx);}
	};
public:
	class Iterator {
	private:
		double* m_data;
		size_t m_size;
	public:
	    using iterator_category = std::random_access_iterator_tag;
	    using difference_type = std::ptrdiff_t;
	    using reference = Row;
	public:
		Iterator(double* data, const size_t& size) : m_data(data), m_size(size) {}
	public:
	    bool operator==(const Iterator& b) const {return m_data == b.m_data;}
	    bool operator!=(const Iterator& b) const {return !((*this) == b);};
	    Iterator& operator+=(const difference_type& mov) {m_data += mov*m_size; return (*this);}
	    Iterator& operator-=(const difference_type& mov) {m_data -= mov*m_size; return (*this);}
	    Iterator& operator++() {m_data += m_size; return (*this);}
	    Iterator& operator--() {m_data -= m_size; return (*this);}
	    Iterator operator++(int) {Iterator tmp = *this; ++(*this); return tmp;}
	    Iterator operator--(int) {Iterator tmp = *this; --(*this); return tmp;}
	    Iterator operator+(const difference_type& mov) {double* oldData = m_data; m_data += mov*m_size; Iterator tmp = *this; m_data = oldData; return tmp;}
	    Iterator operator-(const difference_type& mov) {double* oldData = m_data; m_data -= mov*m_size; Iterator tmp = *this; m_data = oldData; return tmp;}
	    Row operator*() {return Row(m_data, m_size);}
	    const Row operator*() const {return Row(m_data, m_size);}
	};
private:
	size_t m_size;
	double* m_data;
public:
	Iterator begin() {return Iterator(m_data, m_size);}
	Iterator end() {return Iterator(m_data + m_size*m_size, m_size);}
	const Iterator begin() const {return Iterator(m_data, m_size);}
	const Iterator end() const {return Iterator(m_data + m_size*m_size, m_size);}	
	Row operator[](const size_t& idx) {return Row(m_data + m_size*idx, m_size);} 
	const Row operator[](const size_t& idx) const {return Row(m_data + m_size*idx, m_size);}
	size_t size() const {return m_size;}
	AdjacencyMatrix& operator=(const AdjacencyMatrix& b) {
		m_size = b.m_size; 
		delete[] m_data; 
		m_data = new double[m_size*m_size]; 
		for (double *i = m_data, *j = b.m_data; i < m_data + m_size*m_size; ++i, ++j) {
			*i = *j;
		}
		return (*this);
	}
	~AdjacencyMatrix() {
		delete[] m_data;
	}
	AdjacencyMatrix(const size_t& size) : m_size(size) {
		m_data = new double[m_size*m_size];
	}
	AdjacencyMatrix(const AdjacencyMatrix& b) : AdjacencyMatrix(b.m_size) {
		for (double *i = m_data, *j = b.m_data; i < m_data + m_size*m_size; ++i, ++j) {
			*i = *j;
		}
	}
};


AdjacencyMatrix Floyd_WarshalAPSP(AdjacencyMatrix prev);
