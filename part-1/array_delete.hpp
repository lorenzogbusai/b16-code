#ifndef __array_delete__
#define __array_delete__

#include <cstddef>
#include <utility>
#include <vector>

template <typename T>
void array_delete(std::vector<T> &A, std::size_t index)
{
    // Check if index is valid
    if (index < 0 || index >= A.size())
        return;  // Do nothing if index is out of bounds
    
    // Shift elements to fill the gap
    for (std::size_t i = index; i < A.size() - 1; i++)
    {
        A[i] = A[i + 1];  // Copy next element to current position
    }
    
    // Remove the last element (which is now a duplicate)
    A.pop_back();
}

#endif // __array_delete__