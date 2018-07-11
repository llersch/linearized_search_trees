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

#include <cassert>
#include <cmath>

namespace lst {
    class mapper {
    public:
        /**
         * @brief Constructs object for mapping between array and tree indexes.
         * 
         * @param size number of elements in the array/tree.
         * @param K maximum number of children a tree node can have.
         */
        explicit mapper(size_t size, unsigned int K) {
              assert(size > 0 && K > 2);

              size_ = size;
              K_ = K;
              height_ = ceil_log(K_, size+1);
              const unsigned int d_size = floor_log(K_, size_);
              o_size_ = size_ - std::pow(K_, d_size);
              fringe_ = std::pow(K, height_-d_size-1) * std::floor((K*o_size_)/(K-1)+1) - 1;
        }

        /**
         * @brief Maps an index in the sorted array to an index in a linearized
         * complete K-ary search tree.
         *
         * @param array_idx index in the array.
         * @return size_t corresponding index in the search tree.
         */
        size_t array_to_tree(size_t array_idx) const noexcept {
            assert(array_idx < size_);

            unsigned int H = height_;
            if(array_idx > fringe_) {
                array_idx = array_idx - o_size_ - 1;
                H = height_ - 1;
            }

            array_idx = array_idx + 1;
            unsigned int d = 0;
            for(unsigned int i=1; i<H; ++i) {
                d += array_idx % static_cast<int>(std::pow(K_, H-i)) > 0 ? 1 : 0;
            }
            const unsigned int o = std::floor(((K_-1)*array_idx) / std::pow(K_, H-d));
            return std::pow(K_, d) + o - 1;
        }

        /**
         * @brief Maps an index in the linearized complete K-ary search tree to
         * an index in the sorted array.
         *
         * @param tree_idx index in the tree.
         * @return size_t corresponding index in the sorted array.
         */
        size_t int tree_to_array(size_t tree_idx) const noexcept {
            assert(tree_idx < size_);

            tree_idx = tree_idx + 1;
            const int d = floor_log(K_, tree_idx);
            const int o = tree_idx - std::pow(K_, d);
            int array_idx = std::pow(K_, height_-d-1) * std::floor((K_*o)/(K_-1)+1) - 1;

            if(array_idx > fringe_) {
                array_idx = std::pow(K_, (height_-1)-d-1) * std::floor((K_*o)/(K_-1)+1) - 1;
                array_idx = array_idx + o_size_ + 1;
            }
 
            return array_idx - 1;
        }

        /**
         * @brief Calculates ceil(log_(base) number) for integers.
         * 
         * @param base base of the log operation
         * @param number number of the log operation
         * @return int ceil of the log
         */
        static int ceil_log(int base, int number) {
            assert(base > 1 && number > 0);

            int curr = base;
            int cnt = 1;
            while(curr < number) {
                curr *= base;
                ++cnt;
            }
            return cnt;
        }

        /**
         * @brief Calculates floor(log_(base) number) for integers.
         * 
         * @param base base of the log operation
         * @param number number of the log operation
         * @return int floor of the log
         */
        static int floor_log(int base, int number) {
            assert(base > 1 && number > 0);

            int curr = base;
            int cnt = 0;
            while(curr <= number) {
                curr *= base;
                ++cnt;
            }
            return cnt;
        }

    private:
        /// Number of elements in the array/tree being used.
        size_t size_;

        /// Parameter K for a K-ary tree.
        unsigned int K_;

        /// Height of the K-ary tree.
        unsigned int height_;

        /// Tree offset of last array element.
        size_t o_size_;

        /// Fringe element
        size_t fringe_;
    };
}
