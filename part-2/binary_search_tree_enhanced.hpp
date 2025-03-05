#ifndef __binary_saerch_tree_enhanced__
#define __binary_saerch_tree_enhanced__

#include "binary_search_tree.hpp"

template <typename T> T bst_min(const T &tree)
{
    if (!tree)
        return nullptr; 
    
    if (!left(tree))
        return tree; 
    
    return bst_min(left(tree)); 
}

template <typename T> T bst_max(const T &tree)
{
    if (!tree)
        return nullptr; 
    
    if (!right(tree))
        return tree; 
    
    return bst_max(right(tree)); 
}

//Design an algorithm to traverse the nodes of a BST by non-decreasing value.
// template <typename T> void bst_inorder(const T &tree)
// {
//     if (!tree)
//         return; 
    
//     bst_inorder(left(tree), f); 
//     bst_inorder(right(tree), f); 
// }
#endif // __binary_saerch_tree_enhanced__