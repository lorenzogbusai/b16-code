#ifndef __shortest_paths_decode__
#define __shortest_paths_decode__

#include "graph.hpp"
#include <algorithm>
#include <vector>

inline std::vector<int> decode(const std::vector<hop_t> &DP, int v)
{
    std::vector<int> path;

    while (v != -1) {  // Assuming -1 is the source or an unreachable node
        path.push_back(v);
        v = DP[v].vertex;  // Extract predecessor from hop_t
    }

    std::reverse(path.begin(), path.end());  // Reverse to get correct order from source to destination
    return path;
}

#endif // __shortest_paths_decode__
