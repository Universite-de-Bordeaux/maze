#include "queue.hpp"

#include <stdexcept>

#include "queue.hpp"

Queue::Queue() {
    size_ = 0;
    capacity_ = 1;
    position = new Position[1];
}

Queue::~Queue() { delete[] position; }

void Queue::push(int x, int y) {
    if (size_ == capacity_) {
        Position *newPosition = new Position[capacity_ * 2];
        for (int i = 0; i < size_; i++) {
            newPosition[i] = position[i];
        }
        delete[] position;
        position = newPosition;
        capacity_ *= 2;
    }
    position[size_].x = x;
    position[size_].y = y;
    size_++;
}

void Queue::pop() {
    if (size_ < capacity_ / 4) {
        Position *newPosition = new Position[capacity_ / 2];
        for (int i = 0; i < size_; i++) {
            newPosition[i] = position[i];
        }
        delete[] position;
        position = newPosition;
        capacity_ /= 2;
    }
    if (size_ > 0) {
        for (int i = 0; i < size_ - 1; i++) {
            position[i] = position[i + 1];
        }
        size_--;
    }
}

Position Queue::front() { return position[0]; }

bool Queue::empty() { return size_ == 0; }
