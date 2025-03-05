#include "shortest_paths_sparse.hpp"
#include <priority_queue.hpp>

#include <cmath>

std::vector<hop_t> bellman_ford(const SparseGraph &graph, const int source,
                                bool &has_negative_cycle)
{
    const int V = static_cast<int>(graph.size());
    auto DP = std::vector<hop_t>(V, {inf, -1});
    
    DP[source] = {0, -1};
    
    has_negative_cycle = false;
    
    for (int i = 0; i < V - 1; ++i) {
        bool any_change = false;
        for (int u = 0; u < V; ++u) {
            // Skip vertices with infinite distance
            if (!std::isfinite(DP[u].weight)) continue;
            
            // Check all outgoing edges from u
            for (const auto &edge : graph[u]) {
                float new_dist = DP[u].weight + edge.weight;
                if (new_dist < DP[edge.vertex].weight) {
                    DP[edge.vertex] = {new_dist, u};
                    any_change = true;
                }
            }
        }
        
        if (!any_change) break;
    }
    
    // Check for negative cycles
    for (int u = 0; u < V; ++u) {
        if (!std::isfinite(DP[u].weight)) continue;
        for (const auto &edge : graph[u]) {
            if (DP[u].weight + edge.weight < DP[edge.vertex].weight) {
                has_negative_cycle = true;
                return DP;
            }
        }
    }
    
    return DP;
}

struct triplet_t {
    float d;
    int r;
    int v;
};

std::vector<hop_t> dijkstra(const SparseGraph &graph, const int source)
{
    assert(source >= 0);
    assert(source < (signed)graph.size());

    const int V = static_cast<int>(graph.size());
    auto DP = std::vector<hop_t>(V, {inf, -1});
    
    // Initialize source distance
    DP[source] = {0, -1};
    
    // Priority queue comparing by distance
    auto comparison = [](const triplet_t &a, const triplet_t &b) { return a.d < b.d; };
    std::vector<triplet_t> queue;
    
    // Add source to priority queue
    priority_enqueue(queue, {0, -1, source}, comparison);
    
    while (!queue.empty()) {
        // Extract vertex with minimum distance
        auto [dist, prev, u] = queue[0];
        priority_dequeue(queue, comparison);
        
        // Skip if we already found a better path
        if (dist > DP[u].weight) continue;
        
        // Explore all neighbors of u
        for (const auto &edge : graph[u]) {
            float new_dist = DP[u].weight + edge.weight;
            if (new_dist < DP[edge.vertex].weight) {
                DP[edge.vertex] = {new_dist, u};
                priority_enqueue(queue, {new_dist, u, edge.vertex}, comparison);
            }
        }
    }
    
    return DP;
}
