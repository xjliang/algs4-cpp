/******************************************************************************
 *  Compilation:  g++ weightedQuickUnionUF.cc -o weightedQuickUnionUF
 *  Execution:  ./weightedQuickUnionUF < input.txt
 *  Dependencies:
 *  Data files:   https://algs4.cs.princeton.edu/15uf/tinyUF.txt
 *                https://algs4.cs.princeton.edu/15uf/mediumUF.txt
 *                https://algs4.cs.princeton.edu/15uf/largeUF.txt
 *
 *  Weighted quick-union algorithm (without path compression).
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <stdexcept>

 /**
  * The WeightedWeightedQuickUnionUF class represents a union-find data type
  * (also known as the disjoint-sets data type).
  * It supports the classic union and find operations,
  * along with a count operation that returns the total number of sets.
  *
  * The union-find data type models a collection of sets containing n elements,
  * with each element in exactly one set.
  * The element are named 0 through n - 1.
  * Initially, there are n sets, with each element in its own set. The canonical
  * element of a set (also known as the root, identifier, leader, or set representative)
  * in one distinguished element in the set. Here is a summary of the operations:
  *
  *   - find
  *     Returns the canonical element of the set containing p. The find operation
  *     returns the same value for two elements if and only if they are int the 
  *     same set.
  *
  *   - merge
  *     Merges the set containing element p with the set containing element q.
  *     That is, if p and q are in different sets, replace these two sets with 
  *     a new set that is the union of the two.
  *     
  *   - count
  *     Returns the number of sets.
  *
  * The canonical element of a set can change only when the set
  * itself changes during a call to union; it cannot change during
  * a call to either find or count.
  *
  * This implementation uses weighted quick union by size
  * (without path compression).
  * The constructor takes theta(n) time, where n is the number of sites.
  * The find, and union operatoins take theta(log(n)) time in the worse case;
  * the count operation takes theta(1) time.
  *
  * For alternative implementations of the same API, see uf, quickUnionUF
  * and weightedWeightedQuickUnionUF.
  * For additional documentation, see https://algs4.cs.princeton.edu/15uf.
  * 
  * @author xjliang
  * @date   Fri Dec  4 15:18:43 CST 2020
  */

class WeightedQuickUnionUF {
 public:
  // Initializes an empty union-find data structure with n elements
  // 0 through n - 1. Initially, each element is in its own set.
  WeightedQuickUnionUF(int n) : count_(n) {
    parent_.reserve(n);
    size_.reserve(n);
    for (int i = 0; i < n; i++) {
      parent_.push_back(i);
      size_.push_back(1);
    }
  }

  ~WeightedQuickUnionUF() { }

  // Returns the number of sets.
  int count() const { return count_; }

  // Returns the canonical element of the set containing element p.
  int find(int p) {
    validate(p);
    while (p != parent_[p]) {
      p = parent_[p];
    }
    return p;
  }

  // Merges the set containing element p with the set containing element q.
  void merge(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) {
      return;
    }

    // make smaller root pointer to larger one
    if (size_[root_p] < size_[root_q]) {
      parent_[root_p] = parent_[root_q];
      size_[root_q] += size_[root_p];
    } else {
      parent_[root_q] = parent_[root_p];
      size_[root_p] += size_[root_q];
    }
    count_--;
  }

 private:
  // Validates tha p is a valid index.
  void validate(int p) {
    int n = parent_.size();
    if (p < 0 || p >= n) {
      char msg[80];
      sprintf(msg, "index %d is not between 0 and %d", p, n - 1);
      throw new std::out_of_range(msg);
    }
  }

 private:
  std::vector<int> parent_;   // parent_[i] = parent of i
  std::vector<int> size_;     // size_[i] = number of elements in subtree rooted in i
  int count_;                 // number of components
}; // class WeightedQuickUnionUF


// Reads an integer n and a sequence of pairs of integers
// (between 0 and n - 1 from standard input, where each integer)
// in the pair represents some element;
// if the elements are in different sets, merge the two sets
// and print the pair to standard output.
int main(int argc, char* argv[]) {
  int n;
  std::cin >> n;
  WeightedQuickUnionUF uf(n);

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
