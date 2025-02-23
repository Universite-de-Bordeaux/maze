#include "queue.hpp"

Queue::Queue() {
    size_ = 0;
    capacity_ = 1;
    data = new void *[1];
}

Queue::~Queue() { delete[] data; }

void Queue::push(void *data) {
    if (size_ == capacity_) {
        const auto newData = new void *[capacity_ * 2];
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
        const auto newData = new void *[capacity_ / 2];
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

void *Queue::pop(Rand *rand) {
    if (size_ == 0) {
        return nullptr;
    }
    const int index = rand->get(0, size_ - 1);
    void *result = data[index];
    data[index] = data[0];
    pop();
    return result;
}

void *Queue::front() const { return data[0]; }

void *Queue::get(const int index) const {
    if (index < 0 || index >= size_) {
        return nullptr;
    }
    return data[index];
}

bool Queue::empty() const { return size_ == 0; }