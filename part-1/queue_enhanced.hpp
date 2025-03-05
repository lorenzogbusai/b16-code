#ifndef __queue_enhanced__
#define __queue_enhanced__

#include <cassert>
#include <vector>
#include <iostream>

#include "queue.hpp"

template <typename T> class Dequeue : public Queue<T>
{
  public:
    // Inherit the constructors of Queue<T>
    using Queue<T>::Queue;

    // Access the element at the back of the queue
    T &back()
    {
        // WRITE YOUR CODE HERE
        assert(this->_size >= 1);
        return this->_storage[_tail()];
    }

    // Const-access the element at the back of the queue
    const T &back() const
    {
        // WRITE YOUR CODE HERE
        assert(this->_size >= 1);
        return this->_storage[_tail()];
    }

    // Add a new element to the front of the queue by copying
    void enqueue_front(const T &value)
    {
        assert(this->_size < this->_storage.size());
        size_t new_head = (this->_position + this->_size + 1) % this->_storage.size();
        this->_storage[new_head] = value;
        this->_size++;
    }

    // Remove the element at the back of the queue
    void dequeue_back()
    {        
        //print the queue
        assert(this->_size > 0);
        this->_position = (this->_position + 1) % this->_storage.size();
        this->_size--;
    }

    // Remove all elements from the queue
    void clear() { 
        this->_size = 0;
        this->_position = 0;
    }

  protected:
    // Return the index of the element at the back of the queue
    size_t _tail() const
    {
        assert(this->_size >= 1);
        size_t tail = (this->_position + 1) % this->_storage.size();
        return tail;
    }
};

#endif // __queue_enhanced__