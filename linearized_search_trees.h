/*
 * MIT License
 *
 * Copyright (c) 2018 Lucas Lersch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Implementation derived from:
 * "k-Ary Search on Modern Processors", Benjamin Schlegel et al, DaMoN 2009
 */

#include <cmath>
#include <cassert>

/**
 * @brief Maps an index in a sorted array to an index in a linearized perfect 
 * K-ary search tree.
 * 
 * @param size total size of the array/tree.
 * @param K arity of the linearized search tree being converted to.
 * @param array_idx index in the sorted array to be converted to a tree index.
 * @param H height of the tree.
 * @return size_t corresponding index in a linearized perfect K-ary search tree.
 */
size_t array_to_perfect_tree(size_t size,
                             int K,
                             size_t array_idx,
                             size_t H) {
    assert(K > 1);
    assert(size > 0);
    assert(array_idx >= 0 && array_idx < size);

    const size_t idx = array_idx+1;
    size_t d = 0;
    for(int i=1; i<H; ++i) {
        d += ((idx % static_cast<size_t>(std::pow(K, H-i))) > 0) ? 1 : 0;
    }
    const size_t o = std::floor(((K-1)*idx) / std::pow(K, H-d));
    return std::pow(K, d) + o - 1;
}

/**
 * @brief Maps an index in a sorted array to an index in a linearized perfect
 * K-ary search tree.
 * 
 * @param size total size of the array/tree.
 * @param K arity of the linearized search tree being converted to.
 * @param array_idx index in the sorted array to be converted to a tree index.
 * @return size_t corresponding index in a linearized perfect K-ary search tree.
 */
size_t array_to_perfect_tree(size_t size, int k, size_t array_idx) {
    const size_t H = std::ceil(std::log(size+1) / std::log(k));
    return array_to_perfect_tree(size, k, array_idx, H);
}

/**
 * @brief Maps an index in a linearized perfect K-ary search tree to an 
 * index in a sorted array.
 * 
 * @param size total size of the array/tree.
 * @param K arity of the linearized search tree being converted from.
 * @param tree_idx index in the tree to be converted to an array index.
 * @param H height of the tree.
 * @return size_t corresponding index in the sorted array.
 */
size_t perfect_tree_to_array(size_t size, 
                             int K,
                             size_t tree_idx,
                             size_t H) {
    assert(K > 1);
    assert(size > 0);
    assert(tree_idx >= 0 && tree_idx < size);

    const size_t idx = tree_idx + 1;
    const size_t d = std::floor(std::log(idx) / std::log(K));
    const size_t o = idx - std::pow(K,d);
    return std::pow(K, H-d-1) * std::floor((K*o)/(K-1)+1);
}

/**
 * @brief Maps an index in a linearized perfect K-ary search tree to an 
 * index in a sorted array.
 * 
 * @param size total size of the array/tree.
 * @param K arity of the linearized search tree being converted from.
 * @param tree_idx index in the tree to be converted to an array index.
 * @return size_t corresponding index in the sorted array.
 */
size_t perfect_tree_to_array(size_t size, int K, size_t tree_idx) {
    const size_t H = std::ceil(std::log(size+1) / std::log(K));
    return perfect_tree_to_array(size, K, tree_idx, H);
}

/**
 * @brief Maps an index in a sorted array to an index in a linearized complete 
 * K-ary search tree.
 * 
 * @param size total size of the array/tree.
 * @param K arity of the linearized search tree being converted to.
 * @param array_idx index in the sorted array to be converted to a tree index.
 * @return size_t corresponding index in a complete linearized K-ary search tree.
 */
size_t array_to_complete_tree(size_t size, int K, size_t array_idx) {
    assert(K > 1);
    assert(size > 0);
    assert(array_idx >= 0 && array_idx < size);

    const size_t H = std::ceil(std::log(size+1) / std::log(K));
    const size_t fringe = perfect_tree_to_array(size, K, size-1, H);
    if(array_idx < fringe) {
        return array_to_perfect_tree(size, K, array_idx, H);
    }
    else {
        const size_t d = std::floor(std::log(size) / std::log(K));
        const size_t o = size - std::pow(K,d);
        return array_to_perfect_tree(size, K, array_idx-o-1, H-1);
    }
}