/******************************************************************************
 *  Compilation:  g++ quickUnionPathCompressionUF.cc -o quickUnionPathCompressionUF
 *  Execution:  ./quickUnionPathCompressionUF < input.txt
 *  Dependencies:
 *  Data files:   https://algs4.cs.princeton.edu/15uf/tinyUF.txt
 *                https://algs4.cs.princeton.edu/15uf/mediumUF.txt
 *                https://algs4.cs.princeton.edu/15uf/largeUF.txt
 *
 *  Quick-union with path compression (but no weighting by size or rank).
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <stdexcept>

 /**
  * The QuickUnionUF class represents a union-find data type
  * (also known as the disjoint-sets data type).
  * It supports the classic union and find operations,
  * along with a count operation that returns the total number of sets.
  *
  * This implementation uses quick union (no weighting) with full path compression.
  * Initializing a data structure with <em>n</em> sites takes linear time.
  * Afterwards, union, find take logarithmic amortized time,
  * and the count operation takes constant time.
  *
  * For additional documentation, see https://algs4.cs.princeton.edu/15uf.
  * 
  * @author xjliang
  * @date   Fri Dec  4 15:18:43 CST 2020
  */

class QuickUnionPathCompressionUF {
 public:
  // Initializes an empty union-find data structure with n elements
  // 0 through n - 1. Initially, each element is in its own set.
  QuickUnionPathCompressionUF(int n) : count_(n) {
    parent_.reserve(n);
    for (int i = 0; i < n; i++) {
      parent_.push_back(i);
    }
  }

  ~QuickUnionPathCompressionUF() { }

  // Returns the number of sets.
  int count() const { return count_; }

  // Returns the canonical element of the set containing element p.
  int find(int p) {
    int root = p;
    while (root != parent_[root]) {
      root = parent_[root];
    }
    while (p != root) {
      int newp = parent_[p];
      parent_[p] = root;
      p = newp;
    }
    return root;
  }

  // Merges the set containing element p with the set containing element q.
  void merge(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) {
      return;
    }

    parent_[root_p] = parent_[root_q];
    count_--;
  }

 private:
  std::vector<int> parent_;   // parent_[i] = parent of i
  int count_;             // number of components
}; // class QuickUnionPathCompressionUF


// Reads an integer n and a sequence of pairs of integers
// (between 0 and n - 1 from standard input, where each integer)
// in the pair represents some element;
// if the elements are in different sets, merge the two sets
// and print the pair to standard output.
int main(int argc, char* argv[]) {
  int n;
  std::cin >> n;
  QuickUnionPathCompressionUF uf(n);

  int p;
  int q;
  try {
    while (std::cin >> p >> q) {
      if (uf.find(p) == uf.find(q)) {
        continue;
      }
      uf.merge(p, q);
      std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << " components" << std::endl;
  } catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
