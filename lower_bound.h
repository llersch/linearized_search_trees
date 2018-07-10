#include <vector>
#include <cmath>

// TODO: generalize the method

size_t lower_bound(const std::vector<uint32_t>& tree_array, int size, int k, uint32_t key) { 
    int max_level = std::ceil(std::log(size+1)/std::log(k)) - 1;

    int low = 0;
    int level = 0;
    int node = 0;
    do {
        int child = 0;
        for(int i=0; i<k-1; ++i)    // Iterate over this node
        {
            if (tree_array[node+i] == key)  // We have a match on this node!
                return tree_array[node + i];
            else if(tree_array[node+i] < key)
            {
				// Key is greater, save lower bound and go to next key in this node.
                low = node + child;
                ++child;
            }
           else
                break;      // Key smaller, we have found our child!
        }

        node = (node*k) + (child+1)*(k-1);
        ++level;
    } while(level <= max_level);
    return tree_array[low];
}
