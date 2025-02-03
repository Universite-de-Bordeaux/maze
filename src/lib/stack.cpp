#include "stack.hpp"

Stack::Stack() {
    size_ = 0;
    capacity_ = 1;
    data = new void *[1];
}

Stack::~Stack() { delete[] data; }

void Stack::push(void *data) {
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

void Stack::pop() {
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
        size_--;
    }
}

void *Stack::top() { return data[size_ - 1]; }

bool Stack::empty() { return size_ == 0; }