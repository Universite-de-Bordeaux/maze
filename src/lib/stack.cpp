#include "stack.hpp"

Stack::Stack() {
    size_ = 0;
    capacity_ = 1;
    data = new void *[1];
}

Stack::~Stack() { delete[] data; }

void Stack::push(void *data) {
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

void Stack::pop() {
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
        size_--;
    }
}

void *Stack::pop(Rand *rand) {
    if (size_ == 0) {
        return nullptr;
    }
    const int index = rand->get(0, size_ - 1);
    void *result = data[index];
    data[index] = data[size_ - 1];
    pop();
    return result;
}

void *Stack::top() const { return data[size_ - 1]; }

bool Stack::empty() const { return size_ == 0; }