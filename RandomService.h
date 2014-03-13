/// Gio Carlo Cielo Borje
/// 41894135

#ifndef RANDOM_SERVICE_H
#define RANDOM_SERVICE_H

#include <random>
#include <ctime>
#include <limits>

template <typename T>
class RandomService {
public:
	explicit RandomService(std::random_device& seed);

	T next(std::normal_distribution<double>& dist);
private:
	std::mt19937 eng;
};

template <typename T>
RandomService<T>::RandomService(std::random_device& seed) : 
	eng(static_cast<unsigned long>(time(nullptr)))
{}

template <typename T>
T RandomService<T>::next(std::normal_distribution<double>& dist) {
	double result = 0;
	while (result < 1 || result > std::numeric_limits<double>::max())
		result = dist(eng);
	return static_cast<T>(result);
}

#endif