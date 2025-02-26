#include "rand.hpp"

Rand::Rand() : rng_(std::random_device{}()) {}

int Rand::get(const int min, const int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(rng_);
}

double Rand::get(const double min, const double max) {
    std::uniform_real_distribution<> dist(min, max);
    return dist(rng_);
}

bool Rand::get(const double probability) { return get(0.0, 1.0) < probability; }

int Rand::get() { return get(0, RAND_MAX); }