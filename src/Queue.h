#ifndef QUEUE_H
#define QUEUE_H

#include <list> // Using std::list for easy enqueue/dequeue at ends
#include <stdexcept> // For std::runtime_error

template <typename T>
class Queue {
private:
    std::list<T> data;

public:
    Queue() = default; // Default constructor

    // Add an element to the back of the queue
    void enqueue(const T& item) {
        data.push_back(item);
    }

    // Remove and return the element from the front of the queue
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty, cannot dequeue.");
        }
        T frontItem = data.front();
        data.pop_front();
        return frontItem;
    }

    // Get the element at the front without removing it
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty, no front element.");
        }
        return data.front();
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get the number of elements in the queue
    size_t size() const {
        return data.size();
    }
};

#endif // QUEUE_H