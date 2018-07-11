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

#include <vector>

namespace lst {

/**
 * @brief Search for the lower bound of a given key.
 *
 * @param tree vector containing the tree in serialized format.
 * @param K maximum number of children a tree node can have.
 * @param key key to be searched for.
 */
size_t lower_bound(const std::vector<uint32_t>& tree, const unsigned int K, uint32_t key) {
    size_t low = 0;
    size_t node = 0;
    do {
        size_t child = 0;
        for(unsigned int i=0; i<K-1; ++i)    // Iterate over this node
        {
            if (tree[node+i] == key)  // We have a match on this node!
                return tree[node + i];
            else if(tree[node+i] < key)
            {
				// Key is greater, save lower bound and go to next key in this node.
                low = node + child;
                ++child;
            }
           else
                break;      // Key smaller, we have found our child!
        }

        node = (node*K) + (child+1)*(K-1);
    } while(node < tree.size());
    return tree[low];
}
}