/// Gio Carlo Cielo Borje
/// 41894135

#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include "Debug.h"
#include "ObjectPool.h"

template <class Resource>
class ResourcePool : public ObjectPool {
public:
	ResourcePool(size_t sz);
	Resource acquire();
	void release(Resource res);
private:
	std::list<Resource> resources_;
};

template <class Resource>
ResourcePool<Resource>::ResourcePool(size_t sz) :
	ObjectPool(sz), resources_(sz)
{}

template <class Resource>
Resource ResourcePool<Resource>::acquire() {
	if (empty())
		throw QueueEmptyException();
	Resource data = resources_.front();
	resources_.pop_front();
	pool_--;
	return data;
}

template <class Resource>
void ResourcePool<Resource>::release(Resource res) {
	resources_.push_front(res);
	pool_++;
}

#endif