# linearized_search_trees

Short implementation to translate a sorted array to a serialized k-ary tree.
Based on the algorithm described in ["k-Ary Search On Modern Processors"](https://event.cwi.nl/damon2009/DaMoN09-KarySearch.pdf).

In contrast to a sorted array, the serialized k-ary tree is more cache-friendly for point lookups but less efficient for range scans.
