#include "Debug.h"
#include "ObjectPool.h"

ObjectPool::ObjectPool(size_t sz) : 
	capacity_(sz), pool_(sz), waitingSz_(0)
{}

size_t ObjectPool::capacity() const {
	return capacity_;
}

size_t ObjectPool::size() const {
	return pool_;
}

bool ObjectPool::full() const {
	return pool_ == capacity_;
}

bool ObjectPool::empty() const {
	return pool_ == 0;
}

bool ObjectPool::acquire() {
	if (empty())
		return false;
	pool_--;
	return true;
}

void ObjectPool::release() {
	pool_++;
};

bool ObjectPool::waiting() {
	return waitingSz_ != 0;
}

void ObjectPool::enqueue() {
	waitingSz_++;
}

void ObjectPool::enqueue(size_t quantity) {
	waitingSz_ += quantity;
}

void ObjectPool::dequeue() {
	waitingSz_--;
}
