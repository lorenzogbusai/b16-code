#ifndef __radix_sort__
#define __radix_sort__

#include <algorithm>
#include <limits>
#include <vector>

template <typename I>
static constexpr int num_digits_v =
    std::numeric_limits<typename std::iterator_traits<I>::value_type>::digits;

template <typename I>
void radix_sort(I begin, I end,
                int digit = num_digits_v<I>)
{
    // WRITE YOUR CODE HERE
    if(begin == end) return; // handle empty range
    
    // Create a vector from the iterator range
    std::vector<typename std::iterator_traits<I>::value_type> arr(begin, end);
    
    // Find maximum element with a simple loop
    auto max_val = *begin;
    for(auto it = begin; it != end; ++it) {
        if(*it > max_val) {
            max_val = *it;
        }
    }
    
    // Calculate number of bits (k) without using log2
    int k = 0;
    auto temp = max_val;
    while(temp > 0) {
        temp >>= 1;
        k++;
    }
    if(k == 0) k = 1; // Handle case when max_val is 0
    
    // Sort by each bit
    int mask = 1;
    for(int i = 0; i < k; i++) {
        std::vector<typename std::iterator_traits<I>::value_type> zeros;
        std::vector<typename std::iterator_traits<I>::value_type> ones;
        
        // Separate numbers based on current bit
        for(auto num : arr) {
            if(num & mask) {
                ones.push_back(num);
            } else {
                zeros.push_back(num);
            }
        }
        
        // Combine zeros and ones back into original array
        size_t index = 0;
        for(auto num : zeros) {
            arr[index++] = num;
        }
        for(auto num : ones) {
            arr[index++] = num;
        }
        
        // Move to next bit
        mask <<= 1;
    }
    
    // Copy sorted elements back to the original range
    std::copy(arr.begin(), arr.end(), begin);
}

#endif // __radix_sort__