/// Gio Carlo Cielo Borje
/// 41894135

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "QueueEmptyException.h"
#include <list>
#include <queue>

class ObjectPool {
public:
	ObjectPool(size_t sz);

	size_t capacity() const;
	size_t size() const;
	bool full() const;
	bool empty() const;

	bool acquire();
	void release();

	bool waiting();
	void enqueue();
	void enqueue(size_t quantity);
	void dequeue();
protected:
	size_t capacity_;
	size_t pool_;

	size_t waitingSz_;
};

#endif