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
        explicit mapper(int size, int K) {
              assert(size > 0 && K > 2);

              size_ = size;
              K_ = K;
              height_ = ceil_log(K_, size+1);
              const int d_size = floor_log(K_, size_);
              o_size_ = size_ - std::pow(K_, d_size);
              fringe_ = std::pow(K, height_-d_size-1) * std::floor((K*o_size_)/(K-1)+1) - 1;
        }

        /**
         * @brief Maps an index in the sorted array to an index in a linearized
         * complete K-ary search tree.
         *
         * @param array_idx index in the array.
         * @return int corresponding index in the search tree.
         */
        int array_to_tree(int array_idx) const {
            assert(array_idx >= 0 && array_idx < size_);

            int H = height_;
            if(array_idx > fringe_) {
                array_idx = array_idx - o_size_ - 1;
                H = height_ - 1;
            }

            array_idx = array_idx + 1;
            int d = 0;
            for(int i=1; i<H; ++i) {
                d += array_idx % static_cast<int>(std::pow(K_, H-i)) > 0 ? 1 : 0;
            }
            const int o = std::floor(((K_-1)*array_idx) / std::pow(K_, H-d));
            return std::pow(K_, d) + o - 1;
        }

        /**
         * @brief Maps an index in the linearized complete K-ary search tree to
         * an index in the sorted array.
         *
         * @param tree_idx index in the tree.
         * @return int corresponding index in the sorted array.
         */
        int tree_to_array(int tree_idx) const {
            assert(tree_idx >= 0 && tree_idx < size_);

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
        int size_;

        /// Parameter K for a K-ary tree.
        int K_;

        /// Height of the K-ary tree.
        int height_;

        /// Tree offset of last array element.
        int o_size_;

        /// Fringe element
        int fringe_;
    };
}