#include <iostream>
#include "linearized_search_trees.h"

int main() {
    int input_array[26] = {1, 2, 3, 4, 5, 6, 7 , 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
    int output_tree[26];

    for(int i=0; i<26; ++i) {
        output_tree[array_to_perfect_tree(26, 3, i)] = input_array[i];
    }

    for(int i=0; i<26; ++i) {
        std::cout << output_tree[i] << std::endl;
    }

    return 0;
}

