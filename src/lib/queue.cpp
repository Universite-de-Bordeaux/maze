#include "queue.hpp"

#include <stdexcept>

#include "queue.hpp"

Queue::Queue() {
    size_ = 0;
    capacity_ = 1;
    data = new void *[1];
}

Queue::~Queue() { delete[] data; }

void Queue::push(void *data) {
    if (size_ == capacity_) {
        void **newData = new void *[capacity_ * 2];
        for (int i = 0; i < size_; i++) {
                newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
        capacity_ *= 2;
    }
    this->data[size_] = data;
    size_++;
}

void Queue::pop() {
    if (size_ < capacity_ / 4) {
        void **newData = new void *[capacity_ / 2];
        for (int i = 0; i < size_; i++) {
                newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
        capacity_ /= 2;
    }
    if (size_ > 0) {
        for (int i = 0; i < size_ - 1; i++) {
                data[i] = data[i + 1];
        }
        size_--;
    }
}

void *Queue::front() { return data[0]; }

bool Queue::empty() { return size_ == 0; }
