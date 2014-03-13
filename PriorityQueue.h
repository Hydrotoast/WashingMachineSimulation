/// Gio Carlo Cielo Borje
/// 41894135

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Debug.h"
#include "QueueEmptyException.h"
#include <vector>
#include <algorithm>

/// Sorted queue according to a priority
/// T parameter must implement both operator< and operator==
template <class T>
class PriorityQueue {
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& pq);
	PriorityQueue& operator=(const PriorityQueue& pq);

	bool empty() const;
	size_t size() const;

	T min() const;
	void push(const T& t);
	T pop();
private:
	inline size_t parent(size_t i);
	inline size_t left(size_t i);
	inline size_t right(size_t i);

	inline void bubbleUp(size_t i);
	inline void bubbleDown(size_t i);

	size_t sz;
	std::vector<T> heap;
};

template <class T>
PriorityQueue<T>::PriorityQueue() :
	sz(0)
{}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& pq) {
	this->size = pq.size;
	this->heap = pq.heap;
}

template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& pq) {
	if (this == &pq)
		return;
	heap.clear();
	this->size = pq.size();
	this->heap = pq.heap;
	return *this;
}

template <class T>
bool PriorityQueue<T>::empty() const {
	return sz == 0;
}

template <class T>
size_t PriorityQueue<T>::size() const {
	return sz;
}

template <class T>
T PriorityQueue<T>::min() const {
	if (empty())
		throw QueueEmptyException();
	return heap[0];
}

template <class T>
T PriorityQueue<T>::pop() {
	if (empty())
		throw QueueEmptyException();
	T data = heap[0];
	if (size() == 1)
		heap.pop_back();
	else
		heap[0] = heap[sz - 1];
	sz--;
	bubbleDown(0);
	heap.resize(sz);
	return data;
}

template <class T>
void PriorityQueue<T>::push(const T& data) {
	heap.push_back(data);
	sz++;
	bubbleUp(sz - 1);
}

template <class T>
inline size_t PriorityQueue<T>::parent(size_t i) {
	return static_cast<size_t>(floor((i + 1u) >> 1u)) - 1u;
}

template <class T>
inline size_t PriorityQueue<T>::left(size_t i) {
	return (i << 1u) + 1u;
}

template <class T>
inline size_t PriorityQueue<T>::right(size_t i) {
	return (i << 1u) + 2u;
}

template <class T>
inline void PriorityQueue<T>::bubbleDown(size_t i) {
	size_t l = left(i);
	size_t r = right(i);
	size_t min = i;
	if (l < sz && heap[l] < heap[i])
		min = l;
	if (r < sz && heap[r] < heap[min])
		min = r;
	if (min != i) {
		std::swap(heap[i], heap[min]);
		bubbleDown(min);
	}
}

template <class T>
inline void PriorityQueue<T>::bubbleUp(size_t i) {
	size_t p = parent(i);
	while (i > 0 && heap[i] < heap[p]) {
		std::swap(heap[i], heap[p]);
		i = p;
		p = parent(i);
	}
}

#endif