#include "queue.hpp"

#include "queue.hpp"
#include <stdexcept>

Queue::Queue() : size_array(10), left(0), right(0), empty(true) {
    array = new Cell*[size_array];
}

Queue::~Queue() {
    delete[] array;
}

bool Queue::is_empty() const {
    return empty;
}

int Queue::get_size() const {
    if (empty) return 0;
    if (right >= left) return right - left;
    return size_array - left + right;
}

void Queue::grow_queue() {
    int new_size = size_array * 2;
    Cell** new_array = new Cell*[new_size];

    int j = 0;
    for (int i = left; i != right; i = (i + 1) % size_array) {
        new_array[j++] = array[i];
    }

    left = 0;
    right = j;
    size_array = new_size;

    delete[] array;
    array = new_array;
}

void Queue::enqueue(Cell* val) {
    if (!empty && left == right) {
        grow_queue();
    }

    array[right] = val;
    right = (right + 1) % size_array;
    empty = false;
}

Cell* Queue::dequeue() {
    if (is_empty()) {
        throw std::runtime_error("Attempting to dequeue from an empty queue");
    }

    Cell* val = array[left];
    left = (left + 1) % size_array;
    empty = (left == right);

    return val;
}
